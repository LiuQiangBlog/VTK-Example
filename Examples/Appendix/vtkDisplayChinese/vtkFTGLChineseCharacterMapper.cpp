/*=========================================================================

Program:   Visualization Toolkit
Module:    vtkFTGLChineseCharacterMapper.cpp

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
All rights reserved.
See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

/**********************************************************************

  文件名: vtkFTGLChineseCharacterMapper.cpp
  Copyright (c) 张晓东, 罗火灵. All rights reserved.
  更多信息请访问: 
    http://www.vtkchina.org (VTK中国)
	http://blog.csdn.net/www_doling_net (东灵工作室) 

**********************************************************************/

#ifdef WIN32
#include <Windows.h>
#endif

#include "vtkFTGLChineseCharacterMapper.h"
#include "vtkFreeTypeUtilitiesUnicode.h"
#include "vtkTextProperty.h"

#include "vtkActor2D.h"
#include "vtkObjectFactory.h"
#include "vtkProperty2D.h"
#include "vtkViewport.h"
#include "vtkWindow.h"
#include "vtkToolkits.h"  // for VTK_USE_GL2PS
#include "vtkgluPickMatrix.h"

#ifdef VTK_USE_GL2PS
#include "gl2ps.h"
#endif // VTK_USE_GL2PS
//ftgl///////////////////
#include "ftgl/vtkftglConfig.h"
#include "ftgl/src/FTLibrary.h"
#include "ftgl/src/FTGLPixmapFont.h"
#include "ftgl/src/FTFont.h"
//----------------------------------------------------------------------------
// Print debug info

#define VTK_FTTM_DEBUG 0
#define VTK_FTTM_DEBUG_CD 0

//----------------------------------------------------------------------------
// GL2PS related internal helper functions.
#ifdef VTK_USE_GL2PS
static void
vtkFTGLChineseCharacterMapper_GetGL2PSFontName(vtkTextUnicodeProperty *tprop,
											   char *ps_font)
{
	// For speed we use ARIAL == 0, COURIER == 1, TIMES == 2
	static char const *family[] = {"Helvetica", "Courier", "Times"};
	static char const *italic[] = {"Oblique", "Oblique", "Italic"};
	static char const *base[] = {"", "", "-Roman"};

	int font = tprop->GetFontFamily();

	if (font > 2)
	{
		sprintf(ps_font, "%s", tprop->GetFontFamilyAsString());
		if (tprop->GetBold())
		{
			sprintf(ps_font, "%s%s", ps_font, "Bold");
		}
		if (tprop->GetItalic())
		{
			sprintf(ps_font, "%s%s", ps_font, "Italic");
		}
		return;
	}

	if (tprop->GetBold())
	{
		sprintf(ps_font, "%s-%s", family[font], "Bold");
		if (tprop->GetItalic())
		{
			sprintf(ps_font, "%s%s", ps_font, italic[font]);
		}
	}
	else if (tprop->GetItalic())
	{
		sprintf(ps_font, "%s-%s", family[font], italic[font]);
	}
	else
	{
		sprintf(ps_font, "%s%s", family[font], base[font]);
	}
}
#endif

//----------------------------------------------------------------------------
#ifndef VTK_IMPLEMENT_MESA_CXX
vtkStandardNewMacro(vtkFTGLChineseCharacterMapper);
#endif

//----------------------------------------------------------------------------
vtkFTGLChineseCharacterMapper::vtkFTGLChineseCharacterMapper()
{
	this->LastSize[0] = 0;
	this->LastSize[1] = 0;

	m_TextLines = NULL;
	
	// consistent Register/unregister
	this->m_TextUnicodeProperty = NULL;
}

//----------------------------------------------------------------------------
vtkFTGLChineseCharacterMapper::~vtkFTGLChineseCharacterMapper()
{
	if (this->LastWindow)
	{
		this->ReleaseGraphicsResources(this->LastWindow);
	} 

	this->SetTextProperty(NULL);
}

//----------------------------------------------------------------------------
void vtkFTGLChineseCharacterMapper::ReleaseGraphicsResources(vtkWindow *vtkNotUsed(win))
{
#if VTK_FTTM_DEBUG
	printf("vtkFTGLChineseCharacterMapper::ReleaseGraphicsResources\n");
#endif

	this->LastWindow = NULL;

	// Very important
	// the release of graphics resources indicates that significant changes have
	// occurred. Old fonts, cached sizes etc are all no longer valid, so we send
	// ourselves a general modified message.

	// this->Modified();
}

//----------------------------------------------------------------------------
// Get the size of a multi-line text string
void vtkFTGLChineseCharacterMapper::GetMultiLineSize(vtkViewport* viewport, int size[2])
{
	int i;
	int lineSize[2];

	vtkTextUnicodeProperty *tprop = this->GetTextProperty();
	if (!tprop) 
	{
		vtkErrorMacro(<<"Need text property to get multiline size of mapper");
		size[0] = size[1] = 0;
		return;
	}

	lineSize[0] = lineSize[1] = size[0] = size[1] = 0;
	for ( i=0; i < this->NumberOfLines; i++ )
	{
		this->m_TextLines[i]->SetTextProperty( tprop );
		this->m_TextLines[i]->GetSize(viewport, lineSize);
		size[0] = (lineSize[0] > size[0] ? lineSize[0] : size[0]);
		size[1] = (lineSize[1] > size[1] ? lineSize[1] : size[1]);
	}

	// add in the line spacing
	this->LineSize = size[1];
	size[1] = static_cast<int>(
		size[1] * (1.0 + (this->NumberOfLines - 1) * tprop->GetLineSpacing()));
}

//----------------------------------------------------------------------------
void vtkFTGLChineseCharacterMapper::GetSize(vtkViewport* viewport, int *size)
{
	// Check for multiline
	if (this->NumberOfLines > 1)
	{
		this->GetMultiLineSize(viewport, size);
		return;
	}

	// Check for input
	if (this->Input == NULL || this->Input[0] == '\0') 
	{
		size[0] = size[1] = 0;
		return;
	}

	vtkTextUnicodeProperty *tprop = this->GetTextProperty();
	if (!tprop)
	{
		vtkErrorMacro(<< "Need a text property to get size");
		size[0] = size[1] = 0;
		return;
	}

	// Check to see whether we have to rebuild anything
	if (this->GetMTime() < this->SizeBuildTime &&
		tprop->GetMTime() < this->SizeBuildTime)
	{
#if VTK_FTTM_DEBUG
		printf("vtkFTGLChineseCharacterMapper::GetSize: In cache!\n");
#endif

		size[0] = this->LastSize[0];
		size[1] = this->LastSize[1];
		return;
	}

	// Check for font and try to set the size
	vtkFreeTypeUtilitiesUnicode::Entry *entry = vtkFreeTypeUtilitiesUnicode::GetInstance()->GetFont(tprop);
	ftgl::FTFont *font = entry ? entry->Font : NULL;
	if (!font) 
	{
		vtkErrorMacro(<< "Render - No font");
		size[0] = size[1] = 0;
		return;
	}

	// The font global ascender and descender might just be too high
	// for given a face. Let's get a compromise by computing these values
	// from some usual ascii chars.
	if (entry->LargestAscender < 0 || entry->LargestDescender < 0)
	{
		float llx, lly, llz, urx, ury, urz;
		font->BBox("_/7Agfy", llx, lly, llz, urx, ury, urz);
		entry->LargestAscender = ury;
		entry->LargestDescender = lly;
	}

#ifdef WIN32
	char utf8s[256];
	WCHAR s2[256];      
	MultiByteToWideChar( 936, 0, this->Input,strlen(this->Input)+1, s2, sizeof(s2)/sizeof(s2[0]));
	WideCharToMultiByte( CP_UTF8, 0, s2, -1, utf8s, 256, NULL, NULL );
	this->LastSize[0] = size[0] = static_cast<int>(font->Advance(s2));
#else
	wchar_t   wsz[2000] ;  
	setlocale(LC_ALL, "zh_CN.UTF-8");
	mbstowcs(wsz,this->Input, 2000);
	this->LastSize[0] = size[0] = static_cast<int>(font->Advance(wsz));
#endif

	//this->LastSize[0] = size[0] = static_cast<int>(font->Advance(wsz));
	this->LastSize[1] = size[1] =
		static_cast<int>(entry->LargestAscender - entry->LargestDescender);
	this->LastLargestDescender = static_cast<int>(entry->LargestDescender);

	this->SizeBuildTime.Modified();
}

//----------------------------------------------------------------------------
void vtkFTGLChineseCharacterMapper::RenderOverlayMultipleLines(vtkViewport *viewport, 
											   vtkActor2D *actor)    
{
	float offset = 0.0f;
	int size[2];
	// make sure LineSize is up to date 
	this->GetMultiLineSize(viewport,size);

	vtkTextUnicodeProperty *tprop = this->GetTextProperty();
	if (!tprop)
	{
		vtkErrorMacro(<<"Need text property to render multiple lines of mapper");
		return;
	}

	switch (tprop->GetVerticalJustification())
	{
	case VTK_TEXT_TOP:
		offset = 0.0f;
		break;
	case VTK_TEXT_CENTERED:
		offset = (-this->NumberOfLines + 1.0f) / 2.0f;
		break;
	case VTK_TEXT_BOTTOM:
		offset = -this->NumberOfLines + 1.0f;
		break;
	}

	for (int lineNum=0; lineNum < this->NumberOfLines; lineNum++)
	{
		double lineOffset = /*tprop->GetLineOffset() +*/ static_cast<int>(this->LineSize * (lineNum + offset) * tprop->GetLineSpacing());

		this->m_TextLines[lineNum]->GetTextProperty()->ShallowCopy(tprop);
		this->m_TextLines[lineNum]->GetTextProperty()->SetLineOffset(lineOffset);
		this->m_TextLines[lineNum]->RenderOverlay(viewport,actor);
	}
}

//----------------------------------------------------------------------------
// Get the next \n delimited line. Returns a string that
// must be freed by the calling function.
char *vtkFTGLChineseCharacterMapper::NextLine(const char *input, int lineNum)
{
	const char *ptr, *ptrEnd;
	int strLen;
	char *line;

	ptr = input;
	for (int i=0; i != lineNum; i++)
	{
		ptr = strstr(ptr,"\n");
		ptr++;
	}
	ptrEnd = strstr(ptr,"\n");
	if ( ptrEnd == NULL )
	{
		ptrEnd = strchr(ptr, '\0');
	}

	strLen = ptrEnd - ptr;
	line = new char[strLen+1];
	strncpy(line, ptr, strLen);
	line[strLen] = '\0';

	return line;
}

void vtkFTGLChineseCharacterMapper::SetTextProperty(vtkTextUnicodeProperty *p)
{
	Superclass::SetTextProperty(p);
	m_TextUnicodeProperty = p;
}

vtkTextUnicodeProperty* vtkFTGLChineseCharacterMapper::GetTextProperty()
{
	return m_TextUnicodeProperty;
}

//----------------------------------------------------------------------------
// Shallow copy of an actor.
void vtkFTGLChineseCharacterMapper::ShallowCopy(vtkFTGLChineseCharacterMapper *m)
{
	if ( !m )
	{
		return;
	}
	
	this->SetInput(m->GetInput());
	this->SetTextProperty(m->GetTextProperty());
	this->SetClippingPlanes(m->GetClippingPlanes());

	Superclass::ShallowCopy(m);
}

//----------------------------------------------------------------------------
// Parse the input and create multiple text mappers if multiple lines
// (delimited by \n) are specified.
void vtkFTGLChineseCharacterMapper::SetInput(const char *input)
{
	if ( this->Input && input && (!strcmp(this->Input,input))) 
	{
		return;
	}
	if (this->Input) 
	{ 
		delete [] this->Input; 
	}  
	if (input)
	{
		this->Input = new char[strlen(input)+1];
		strcpy(this->Input,input);
	}
	else
	{
		this->Input = NULL;
	}
	this->Modified();

	int numLines = this->GetNumberOfLines(input);

	if ( numLines <= 1) // a line with no "\n"
	{
		this->NumberOfLines = numLines;
	}

	else //multiple lines
	{
		char *line;
		int i;

		if ( numLines > this->NumberOfLinesAllocated )
		{
			// delete old stuff
			if ( this->m_TextLines )
			{
				for (i=0; i < this->NumberOfLinesAllocated; i++)
				{
					this->m_TextLines[i]->Delete();
				}
				delete [] this->m_TextLines;
			}

			// allocate new text mappers
			this->NumberOfLinesAllocated = numLines;
			this->m_TextLines = new vtkFTGLChineseCharacterMapper *[numLines];
			for (i=0; i < numLines; i++)
			{
				this->m_TextLines[i] = vtkFTGLChineseCharacterMapper::New();
			}
		} //if we need to reallocate

		// set the input strings
		this->NumberOfLines = numLines;
		for (i=0; i < this->NumberOfLines; i++)
		{
			line = this->NextLine(input, i);
			this->m_TextLines[i]->SetInput( line );
			delete [] line;
		}
	}
}

//----------------------------------------------------------------------------
void vtkFTGLChineseCharacterMapper::RenderOverlay(vtkViewport* viewport, vtkActor2D* actor)
{
	vtkDebugMacro (<< "RenderOverlay");

	// Check for input
	if (this->Input == NULL || this->Input[0] == '\0') 
	{
		return;
	}

	// Check for multi-lines
	if (this->NumberOfLines > 1)
	{
		this->RenderOverlayMultipleLines(viewport, actor);
		return;
	}

	// Get text property
	vtkTextUnicodeProperty *tprop = this->GetTextProperty();
	if (!tprop)
	{
		vtkErrorMacro(<< "Need a text property to render mapper");
		return;
	}

	// Get the window information for display
	vtkWindow* window = viewport->GetVTKWindow();
	if (this->LastWindow && this->LastWindow != window)
	{
		this->ReleaseGraphicsResources(this->LastWindow);
	}
	this->LastWindow = window;

	// Get size of text
	int size[2];
	this->GetSize(viewport, size);

	// Get the position of the text actor
	int* actorPos;
	actorPos= 
		actor->GetActualPositionCoordinate()->GetComputedViewportValue(viewport);

	// Define bounding rectangle
	int pos[2];
	pos[0] = actorPos[0];
	pos[1] =  static_cast<int>(actorPos[1] - tprop->GetLineOffset());

	switch (tprop->GetJustification())
	{
	case VTK_TEXT_LEFT: 
		break;
	case VTK_TEXT_CENTERED:
		pos[0] = pos[0] - size[0] / 2;
		break;
	case VTK_TEXT_RIGHT: 
		pos[0] = pos[0] - size[0];
		break;
	}

	switch (tprop->GetVerticalJustification())
	{
	case VTK_TEXT_TOP: 
		pos[1] = pos[1] - size[1] - this->LastLargestDescender;
		break;
	case VTK_TEXT_CENTERED:
		pos[1] = pos[1] - size[1] / 2 - this->LastLargestDescender / 2;
		break;
	case VTK_TEXT_BOTTOM: 
		pos[1] = pos[1]  - this->LastLargestDescender;
		break;
	}

	// Push a 2D matrix on the stack
	int *vsize = viewport->GetSize();
	double *vport = viewport->GetViewport();
	double *tileViewport = viewport->GetVTKWindow()->GetTileViewport();
	double visVP[4];

	visVP[0] = (vport[0] >= tileViewport[0]) ? vport[0] : tileViewport[0];
	visVP[1] = (vport[1] >= tileViewport[1]) ? vport[1] : tileViewport[1];
	visVP[2] = (vport[2] <= tileViewport[2]) ? vport[2] : tileViewport[2];
	visVP[3] = (vport[3] <= tileViewport[3]) ? vport[3] : tileViewport[3];

	if (visVP[0] == visVP[2] || visVP[1] == visVP[3])
	{
		return;
	}

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	if(viewport->GetIsPicking())
	{
		vtkgluPickMatrix(viewport->GetPickX(), viewport->GetPickY(),
			viewport->GetPickWidth(),
			viewport->GetPickHeight(),
			viewport->GetOrigin(), viewport->GetSize());
	}

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDepthFunc(GL_ALWAYS);

	if (actor->GetProperty()->GetDisplayLocation() == VTK_FOREGROUND_LOCATION)
	{
		glOrtho(0, vsize[0] - 1, 0, vsize[1] - 1, 0, 1);
	}
	else
	{
		glOrtho(0, vsize[0] - 1, 0, vsize[1] - 1, -1, 0);
	}

	int *winSize = viewport->GetVTKWindow()->GetSize();

	int xoff = static_cast<int>(pos[0] - winSize[0] * (visVP[0] - vport[0]));
	int yoff = static_cast<int>(pos[1] - winSize[1] * (visVP[1] - vport[1]));

	// When picking draw the bounds of the text as a rectangle,
	// as text only picks when the pick point is exactly on the
	// origin of the text 
	if(viewport->GetIsPicking())
	{
		float x1 = (2.0 * actorPos[0]) / vsize[0] - 1.0;
		float y1 = 2.0 * (actorPos[1] - tprop->GetLineOffset())/vsize[1] - 1.0;
		float width = (2.0 * size[0]) / vsize[0];
		float height = (2.0 * size[1]) / vsize[1];
		glRectf(x1, y1, x1 + width, y1 + height);

		// Clean up and return after drawing the rectangle
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glEnable(GL_LIGHTING);
		glDepthFunc(GL_LEQUAL);

		return;
	}

	double* tprop_color = tprop->GetColor();
	double tprop_opacity = tprop->GetOpacity();

	// Get the font
	vtkFreeTypeUtilitiesUnicode::Entry *entry =vtkFreeTypeUtilitiesUnicode::GetInstance()->GetFont(tprop, tprop_color);
	ftgl::FTFont *font = entry ? entry->Font : NULL;
	if (!font) 
	{
		vtkErrorMacro(<< "Render - No font");
		return;
	}

	struct FTGLRenderContext *ftgl_context = 0;

#ifdef VTK_IMPLEMENT_MESA_CXX
	// If we support Mangle Mesa, VTK_IMPLEMENT_MESA_CXX will be defined to
	// compile this unit as a Mesa text mapper. In that case, provide a
	// context to FTGL to switch dynamically to Mangle Mesa rendering.
	struct FTGLRenderContext ftgl_context_mesa;
	ftgl_context_mesa.UseMangleMesa = 1;
	ftgl_context = &ftgl_context_mesa;
#endif

	// Setup the fonts for GL2PS output.
#ifdef VTK_USE_GL2PS
	char ps_font[64];
	vtkFTGLChineseCharacterMapper_GetGL2PSFontName(tprop, ps_font);
#endif // VTK_USE_GL2PS

	// Set up the shadow color
	if (tprop->GetShadow())
	{
		double shadow_color[3], rgb;
		rgb = ((tprop_color[0] + tprop_color[1] + tprop_color[2]) / 3.0 > 0.5)
			? 0.0 : 1.0;
		shadow_color[0] = shadow_color[1] = shadow_color[2] = rgb; 

		// Get the shadow font
		vtkFreeTypeUtilitiesUnicode::Entry *shadow_entry =vtkFreeTypeUtilitiesUnicode::GetInstance()->GetFont(tprop, shadow_color);
		ftgl::FTFont *shadow_font = shadow_entry ? shadow_entry->Font : NULL;
		if (!shadow_font) 
		{
			vtkErrorMacro(<< "Render - No shadow font");
			return;
		}

		// Set the color here since load/render glyphs is done
		// on demand and this color has to be consistent for a given font entry.
		glColor4ub(static_cast<unsigned char>(shadow_color[0] * 255.0),
			static_cast<unsigned char>(shadow_color[1] * 255.0), 
			static_cast<unsigned char>(shadow_color[2] * 255.0), 
			static_cast<unsigned char>(tprop_opacity * 255.0));

		// Required for clipping to work correctly
		glRasterPos2i(0, 0);
		glBitmap(0, 0, 0, 0, 
			xoff + tprop->GetShadowOffset()[0], 
			yoff + tprop->GetShadowOffset()[1], NULL);

		// Draw the shadow text
#ifdef WIN32
		char utf8s[256];
		WCHAR s2[256];      
		MultiByteToWideChar( 936, 0, this->Input,strlen(this->Input)+1, s2, sizeof(s2)/sizeof(s2[0]));
		WideCharToMultiByte( CP_UTF8, 0, s2, -1, utf8s, 256, NULL, NULL );
		shadow_font->render(s2,ftgl_context);
#else
		wchar_t   wsz[2000] ;  
		setlocale(LC_ALL, "zh_CN.UTF-8");
		mbstowcs(wsz,this->Input, 2000);
		shadow_font->render(wsz,ftgl_context);
#endif

		// vtkErrorMacro(<<wsz[0]
		//              <<"  "
		//             <<tprop_opacity);
		// Get the font again, Duh, since it may have been freed from the 
		// cache by the shadow font

		font = vtkFreeTypeUtilitiesUnicode::GetInstance()->GetFont(tprop, tprop_color)->Font;
		if (!font) 
		{
			vtkErrorMacro(<< "Render - No font");
			return;
		}

		// Shadow text for GL2PS.
#ifdef VTK_USE_GL2PS
		glRasterPos2i(xoff + tprop->GetShadowOffset()[0], 
			yoff + tprop->GetShadowOffset()[1]);
		gl2psText(this->Input, ps_font, tprop->GetFontSize());
#endif // VTK_USE_GL2PS
	}

	// Set the color here since load/render glyphs is done
	// on demand and this color has to be consistent for a given font entry.
	glColor4ub(static_cast<unsigned char>(tprop_color[0] * 255.0),
		static_cast<unsigned char>(tprop_color[1] * 255.0), 
		static_cast<unsigned char>(tprop_color[2] * 255.0), 
		static_cast<unsigned char>(tprop_opacity * 255.0));

	// Required for clipping to work correctly
	glRasterPos2i(0, 0);
	glBitmap(0, 0, 0, 0, xoff, yoff, NULL);

	// Display a string
#ifdef WIN32
	char utf8s[256];
	WCHAR s2[256];      
	MultiByteToWideChar( 936, 0, this->Input,strlen(this->Input)+1, s2, sizeof(s2)/sizeof(s2[0]));
	WideCharToMultiByte( CP_UTF8, 0, s2, -1, utf8s, 256, NULL, NULL );
	font->render(s2,ftgl_context);

	//WCHAR* sResult = NULL;
	//int textlen = MultiByteToWideChar(936, 0, this->Input, -1, NULL, 0);
	//sResult = (WCHAR*) malloc((textlen + 1) * sizeof(WCHAR));
	//memset(sResult, 0, (textlen + 1) * sizeof(WCHAR));
	//MultiByteToWideChar(936, 0, this->Input, -1, sResult, textlen);
	//font->render(sResult,ftgl_context);
	//if(sResult)
	//	delete sResult;
#else
	wchar_t   wsz[2000] ;  
	setlocale(LC_ALL, "zh_CN.UTF-8");
	mbstowcs(wsz,this->Input, 2000);
	font->render(wsz,ftgl_context);
#endif

	glFlush();

	// Normal text for GL2PS.
#ifdef VTK_USE_GL2PS
	glRasterPos2i(xoff, yoff);
	gl2psText(this->Input, ps_font, tprop->GetFontSize());
#endif // VTK_USE_GL2PS

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LEQUAL);
}

void vtkFTGLChineseCharacterMapper::PrintSelf(ostream& os, vtkIndent indent)
{
	this->Superclass::PrintSelf(os,indent);
}
