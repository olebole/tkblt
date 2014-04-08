/*
 * Smithsonian Astrophysical Observatory, Cambridge, MA, USA
 * This code has been modified under the terms listed below and is made
 * available under the same terms.
 */

/*
 *	Copyright 1993-2004 George A Howlett.
 *
 *	Permission is hereby granted, free of charge, to any person
 *	obtaining a copy of this software and associated documentation
 *	files (the "Software"), to deal in the Software without
 *	restriction, including without limitation the rights to use,
 *	copy, modify, merge, publish, distribute, sublicense, and/or
 *	sell copies of the Software, and to permit persons to whom the
 *	Software is furnished to do so, subject to the following
 *	conditions:
 *
 *	The above copyright notice and this permission notice shall be
 *	included in all copies or substantial portions of the
 *	Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 *	KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *	WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 *	OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *	OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 *	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __BltGrLegend_h__
#define __BltGrLegend_h__

#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

extern "C" {
#include "bltGraph.h"
};

#define LEGEND_RIGHT	(1<<0)	/* Right margin */
#define LEGEND_LEFT	(1<<1)	/* Left margin */
#define LEGEND_BOTTOM	(1<<2)	/* Bottom margin */
#define LEGEND_TOP	(1<<3)	/* Top margin, below the graph title. */
#define LEGEND_PLOT	(1<<4)	/* Plot area */
#define LEGEND_XY	(1<<5)	/* Screen coordinates in the plotting 
				 * area. */
#define LEGEND_WINDOW	(1<<6)	/* External window. */
#define LEGEND_MARGIN_MASK \
	(LEGEND_RIGHT | LEGEND_LEFT | LEGEND_BOTTOM | LEGEND_TOP)
#define LEGEND_PLOTAREA_MASK  (LEGEND_PLOT | LEGEND_XY)

typedef enum {
  SELECT_MODE_SINGLE, SELECT_MODE_MULTIPLE
} SelectMode;

struct _Legend {
  Tk_OptionTable optionTable;
  unsigned int flags;
  ClassId classId;
  int nEntries;
  int nColumns, nRows;
  int width;
  int height;
  int entryWidth, entryHeight;
  int site;
  int xReq;
  int yReq;
  Tk_Anchor anchor;
  int x;
  int y;
  Graph* graphPtr;
  Tcl_Command cmdToken;
  int reqColumns;
  int reqRows;
  int ixPad;
  int iyPad;
  int xPad;
  int yPad;
  Tk_Window tkwin;
  TextStyle style;
  int maxSymSize;
  XColor* fgColor;
  Tk_3DBorder activeBg;
  XColor* activeFgColor;
  int activeRelief;
  int entryBW;
  Tk_3DBorder normalBg;
  int borderWidth;
  int relief;
  Blt_BindTable bindTable;
  int selRelief;
  int selBW;
  XColor* selInFocusFgColor;
  XColor* selOutFocusFgColor;
  Tk_3DBorder selInFocusBg;
  Tk_3DBorder selOutFocusBg;
  XColor* focusColor;
  Blt_Dashes focusDashes;
  GC focusGC;
  const char *takeFocus;
  int focus;
  int cursorX;
  int cursorY;
  short int cursorWidth;
  short int cursorHeight;
  Element *focusPtr;
  Element *selAnchorPtr;
  Element *selMarkPtr;
  Element *selFirstPtr;
  Element *selLastPtr;
  int hide;
  int raised;
  int exportSelection;
  int active;
  int cursorOn;
  int onTime;
  int offTime;
  Tcl_TimerToken timerToken;
  const char *selectCmd;
  SelectMode selectMode;
  Tcl_HashTable selectTable;
  Blt_Chain selected;
  const char *title;
  unsigned int titleWidth;
  unsigned int titleHeight;
  TextStyle titleStyle;
};

extern int Blt_CreateLegend(Graph *graphPtr);
extern void Blt_DestroyLegend(Graph *graphPtr);

extern void Blt_DrawLegend(Graph *graphPtr, Drawable drawable);
extern void Blt_MapLegend(Graph *graphPtr, int width, int height);
extern int Blt_LegendOp(Graph *graphPtr, Tcl_Interp* interp, int objc, 
	Tcl_Obj* const objv[]);
extern int Blt_Legend_Site(Graph *graphPtr);
extern int Blt_Legend_Width(Graph *graphPtr);
extern int Blt_Legend_Height(Graph *graphPtr);
extern int Blt_Legend_IsHidden(Graph *graphPtr);
extern int Blt_Legend_IsRaised(Graph *graphPtr);
extern int Blt_Legend_X(Graph *graphPtr);
extern int Blt_Legend_Y(Graph *graphPtr);
extern void Blt_Legend_RemoveElement(Graph *graphPtr, Element *elemPtr);
extern void Blt_Legend_EventuallyRedraw(Graph *graphPtr);

#endif
