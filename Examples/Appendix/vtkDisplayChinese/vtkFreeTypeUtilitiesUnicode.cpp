/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkFreeTypeUtilitiesUnicode.cpp

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

/**********************************************************************

  文件名: vtkFreeTypeUtilitiesUnicode.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#include "vtkFreeTypeUtilitiesUnicode.h"
#include "vtkTextUnicodeProperty.h"

#include "vtkObjectFactory.h"
#include "vtkMath.h"
#include "vtkImageData.h"
#include "vtkTransform.h"

// FTGL
#include "ftgl/vtkftglConfig.h"
#include "ftgl/src/FTLibrary.h"
#include "ftgl/src/FTGLPixmapFont.h"

// The embedded fonts
#include "fonts/vtkEmbeddedFonts.h"

#include <sys/stat.h>

// Print debug info

#define VTK_FTFC_DEBUG 0
#define VTK_FTFC_DEBUG_CD 0

//----------------------------------------------------------------------------
vtkInstantiatorNewMacro(vtkFreeTypeUtilitiesUnicode);

//----------------------------------------------------------------------------
// The singleton, and the singleton cleanup
vtkFreeTypeUtilitiesUnicode* vtkFreeTypeUtilitiesUnicode::Instance = NULL;
vtkFreeTypeUtilitiesUnicodeCleanup vtkFreeTypeUtilitiesUnicode::Cleanup;

//----------------------------------------------------------------------------
// The embedded fonts
// Create a lookup table between the text mapper attributes 
// and the font buffers.
struct EmbeddedFontStruct
{
	size_t length;
	unsigned char *ptr;
};

//----------------------------------------------------------------------------
// This callback will be called by the FTGLibrary singleton cleanup destructor
// if it happens to be destroyed before our singleton (this order is not 
// deterministic). It will destroy our singleton, if needed.
void vtkFreeTypeUtilitiesUnicodeCleanupCallback ()
{
#if VTK_FTFC_DEBUG_CD
	printf("vtkFreeTypeUtilitiesUnicodeCleanupCallback\n");
#endif
	vtkFreeTypeUtilitiesUnicode::SetInstance(NULL);
}

//----------------------------------------------------------------------------
// Create the singleton cleanup
// Register our singleton cleanup callback against the FTLibrary so that
// it might be called before the FTLibrary singleton is destroyed.
vtkFreeTypeUtilitiesUnicodeCleanup::vtkFreeTypeUtilitiesUnicodeCleanup()
{
#if VTK_FTFC_DEBUG_CD
	printf("vtkFreeTypeUtilitiesUnicodeCleanup::vtkFreeTypeUtilitiesUnicodeCleanup\n");
#endif
	ftgl::FTLibraryCleanup::AddDependency(&vtkFreeTypeUtilitiesUnicodeCleanupCallback);
}

//----------------------------------------------------------------------------
// Delete the singleton cleanup 
// The callback called here might have been called by the FTLibrary singleton
// cleanup first (depending on the destruction order), but in case ours is
// destroyed first, let's call it too.
vtkFreeTypeUtilitiesUnicodeCleanup::~vtkFreeTypeUtilitiesUnicodeCleanup()
{
#if VTK_FTFC_DEBUG_CD
	printf("vtkFreeTypeUtilitiesUnicodeCleanup::~vtkFreeTypeUtilitiesUnicodeCleanup\n");
#endif
	vtkFreeTypeUtilitiesUnicodeCleanupCallback();
}

//----------------------------------------------------------------------------
vtkFreeTypeUtilitiesUnicode* vtkFreeTypeUtilitiesUnicode::GetInstance()
{
	if (!vtkFreeTypeUtilitiesUnicode::Instance)
	{
		vtkFreeTypeUtilitiesUnicode::Instance = static_cast<vtkFreeTypeUtilitiesUnicode *>(
			vtkObjectFactory::CreateInstance("vtkFreeTypeUtilitiesUnicode"));
		if (!vtkFreeTypeUtilitiesUnicode::Instance)
		{
			vtkFreeTypeUtilitiesUnicode::Instance = new vtkFreeTypeUtilitiesUnicode;
		}
	}
	return vtkFreeTypeUtilitiesUnicode::Instance;
}

//----------------------------------------------------------------------------
void vtkFreeTypeUtilitiesUnicode::SetInstance(vtkFreeTypeUtilitiesUnicode* instance)
{
	if (vtkFreeTypeUtilitiesUnicode::Instance == instance)
	{
		return;
	}

	if (vtkFreeTypeUtilitiesUnicode::Instance)
	{
		vtkFreeTypeUtilitiesUnicode::Instance->Delete();
	}

	vtkFreeTypeUtilitiesUnicode::Instance = instance;

	// User will call ->Delete() after setting instance

	if (instance)
	{
		instance->Register(NULL);
	}
}

//----------------------------------------------------------------------------
vtkFreeTypeUtilitiesUnicode* vtkFreeTypeUtilitiesUnicode::New()
{
	vtkFreeTypeUtilitiesUnicode* ret = vtkFreeTypeUtilitiesUnicode::GetInstance();
	ret->Register(NULL);
	return ret;
}

//----------------------------------------------------------------------------
vtkFreeTypeUtilitiesUnicode::vtkFreeTypeUtilitiesUnicode()
{
#if VTK_FTFC_DEBUG_CD
	printf("vtkFreeTypeUtilitiesUnicode::vtkFreeTypeUtilitiesUnicode\n");
#endif

	this->NumberOfEntries = 0;
	this->InitializeCache();

}

//----------------------------------------------------------------------------
vtkFreeTypeUtilitiesUnicode::~vtkFreeTypeUtilitiesUnicode()
{
#if VTK_FTFC_DEBUG_CD
	printf("vtkFreeTypeUtilitiesUnicode::~vtkFreeTypeUtilitiesUnicode\n");
#endif

	this->ReleaseCache();

}

//----------------------------------------------------------------------------
void vtkFreeTypeUtilitiesUnicode::PrintSelf(ostream& os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os,indent);
}

//----------------------------------------------------------------------------
// Print entry
void vtkFreeTypeUtilitiesUnicode::PrintEntry(int i, char *msg)
{
	if (!this->Entries[i])
	{
		return;
	}

	printf("%s: [%2d] =", msg, i);

	vtkTextUnicodeProperty *tprop = this->Entries[i]->TextProperty;
	if (tprop)
	{
		printf(" [S: %2d]", tprop->GetFontSize());

		double *color = tprop->GetColor();
		if (color)
		{
			printf(" [RGBA: %.2f/%.2f/%.2f (%.2f)]", 
				color[0], color[1], color[2], tprop->GetOpacity());
		}

		/*
		if (tprop->GetFontFileName())
		{
		printf(" [F: %s]", tprop->GetFontFileName());
		}
		else
		*/
		{
			printf(" [F: %d] [I: %d] [B: %d]", 
				tprop->GetFontFamily(), tprop->GetItalic(), tprop->GetBold());
		}
	}

	if (this->Entries[i]->Font)
	{
		printf(" [F: %p]", static_cast<void *>(this->Entries[i]->Font));
		printf("\n                                                [f: %p]", 
			static_cast<void*>(*(this->Entries[i]->Font->Face()->Face())));
	}

	printf("\n");
	fflush(stdout);
}

//----------------------------------------------------------------------------
// Release entry
void vtkFreeTypeUtilitiesUnicode::ReleaseEntry(int i)
{
	if (!this->Entries[i])
	{
		return;
	}

#if VTK_FTFC_DEBUG
	this->PrintEntry(this->NumberOfEntries, "Rl");
#endif

	if (this->Entries[i]->TextProperty)
	{
		this->Entries[i]->TextProperty->Delete();
		this->Entries[i]->TextProperty = NULL;
	}

	if (this->Entries[i]->Font)
	{
		delete this->Entries[i]->Font;
		this->Entries[i]->Font = NULL;
	}

	delete this->Entries[i];
	this->Entries[i] = NULL;
}

//----------------------------------------------------------------------------
// Initialize cache
void vtkFreeTypeUtilitiesUnicode::InitializeCache()
{
#if VTK_FTFC_DEBUG_CD
	printf("vtkFreeTypeUtilitiesUnicode::InitializeCache()\n");
#endif  
	this->ReleaseCache();

	int i;
	for (i = 0; i < VTK_FTFC_CACHE_CAPACITY; i++)
	{
		this->Entries[i] = NULL;
	}
}

//----------------------------------------------------------------------------
// Release cache
void vtkFreeTypeUtilitiesUnicode::ReleaseCache()
{
#if VTK_FTFC_DEBUG_CD
	printf("vtkFreeTypeUtilitiesUnicode::ReleaseCache()\n");
#endif  

	int i;
	for (i = 0; i < this->NumberOfEntries; i++)
	{
#if VTK_FTFC_DEBUG
		this->PrintEntry(i, "Rl");
#endif
		this->ReleaseEntry(i);
	}

	this->NumberOfEntries = 0;
}

//----------------------------------------------------------------------------
// Get a font from the cache given the text property. If no font is
// found in the cache, one is created and stored with the given color
// parameters. If override_color is true, then red, green, blue are used as
// text color instead of the colors found in the vtkTextUnicodeProperty.
vtkFreeTypeUtilitiesUnicode::Entry*
vtkFreeTypeUtilitiesUnicode::GetFont(vtkTextUnicodeProperty *tprop,	double override_color[3])
{
	int i,j;

	// Get the requested color and opacity
	vtkTextUnicodeProperty* tpropU=dynamic_cast<vtkTextUnicodeProperty*>(tprop);
	if (!tpropU) return 0;

	double tprop_color[3];
	for (i = 0; i < 3; i++)
	{
		tprop_color[i] = override_color ? override_color[i] : tprop->GetColor()[i];
		if (tprop_color[i] < 0.0)
		{
			tprop_color[i] = 0.0;
		}
	}

	float tprop_opacity = 
		(tprop->GetOpacity() < 0.0) ? 1.0 : tprop->GetOpacity();

	// Has the font been cached ?
	for (i = 0; i < this->NumberOfEntries; i++)
	{
		vtkTextUnicodeProperty *entry_tprop = dynamic_cast<vtkTextUnicodeProperty* >(this->Entries[i]->TextProperty);
		double *entry_tprop_color = entry_tprop->GetColor();

		if (
			// If a face file name has been specified, it overrides the 
			// font family as well as italic and bold attributes

			(
			entry_tprop->GetFontFileName() && tpropU->GetFontFileName() &&
			!strcmp(entry_tprop->GetFontFileName(), tpropU->GetFontFileName())
			)

			&& (entry_tprop_color[0]      == tprop_color[0] &&
			entry_tprop_color[1]      == tprop_color[1] &&
			entry_tprop_color[2]      == tprop_color[2] &&
			entry_tprop->GetOpacity() == tprop_opacity)

			&& entry_tprop->GetFontSize() == tprop->GetFontSize())
		{
			// Make this the most recently used
			if (i != 0)
			{
				vtkFreeTypeUtilitiesUnicode::Entry *tmp = this->Entries[i];
				for (j = i - 1; j >= 0; j--)
				{
					this->Entries[j+1] = this->Entries[j];
				}
				this->Entries[0] = tmp;
			}

			return this->Entries[0];
		}
	}
	//vtkErrorWithObjectMacro(
	//	tprop,
	//	<< "not Chached");
	// OK the font is not cached, try to create one

	ftgl::FTFont *font = new ftgl::FTGLPixmapFont;
	const char* fontFileName=tpropU->GetFontFileName();
	if (!font->Open(fontFileName,false))
	{
		vtkErrorWithObjectMacro(
			tprop,
			<< "!!!!!!!!!!!!Unable to create font !"
			<< fontFileName);
		delete font;
		return 0;
	}

	// Set face size

	font->FaceSize(tprop->GetFontSize());

	// We need to make room for a new font
	if (this->NumberOfEntries == VTK_FTFC_CACHE_CAPACITY)
	{
#if VTK_FTFC_DEBUG
		printf("Cache is full, deleting last!\n");
#endif
		this->NumberOfEntries--;
	}

	// Add the new font

	if (this->Entries[this->NumberOfEntries])
	{

		this->ReleaseEntry(this->NumberOfEntries);
	}
	this->Entries[this->NumberOfEntries] = new vtkFreeTypeUtilitiesUnicode::Entry;

	this->Entries[this->NumberOfEntries]->TextProperty = vtkTextUnicodeProperty::New();

	vtkTextUnicodeProperty *entry_tprop =
		dynamic_cast<vtkTextUnicodeProperty* > (this->Entries[this->NumberOfEntries]->TextProperty);
	// Set the other info

	entry_tprop->ShallowCopy(tprop);
	entry_tprop->SetOpacity(tprop_opacity);
	entry_tprop->SetColor(tprop_color);

	this->Entries[this->NumberOfEntries]->Font = font;

	this->Entries[this->NumberOfEntries]->LargestAscender  =
		this->Entries[this->NumberOfEntries]->LargestDescender = -1;


#if VTK_FTFC_DEBUG
	this->PrintEntry(this->NumberOfEntries, "Cr");
#endif

	vtkFreeTypeUtilitiesUnicode::Entry *tmp = this->Entries[this->NumberOfEntries];

	this->NumberOfEntries++;
	return tmp;
}
