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
 *	KIND, EXPRESS OR IMPIED, INCLUDING BUT NOT LIMITED TO THE
 *	WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
 *	OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *	OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 *	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 *	SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _BLT_GR_AXIS_H
#define _BLT_GR_AXIS_H

#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

extern "C" {
#include "bltGraph.h"
}

typedef struct {
  int axis;
  int t1;
  int t2;
  int label;
} AxisInfo;

typedef struct {
  const char *name;
  ClassId classId;
  int margin, invertMargin;
} AxisName;

extern AxisName axisNames[];

typedef struct {
  Blt_Dashes dashes;
  int lineWidth;
  XColor* color;
  GC gc;
  Segment2d *segments;
  int nUsed;
  int nAllocated;
} Grid;

typedef struct {
  double min;
  double max;
  double range;
  double scale;
} AxisRange;

typedef struct {
  Point2d anchorPos;
  unsigned int width;
  unsigned int height;
  char string[1];
} TickLabel;

typedef struct {
  int nTicks;
  double values[1];
} Ticks;

typedef struct {
  double initial;
  double step;
  int nSteps;
} TickSweep;

typedef struct {
  const char** tags;
  int checkLimits;
  int exterior;
  int showGrid;
  int showGridMinor;
  int hide;
  int showTicks;

  // Fields specific to axes

  double windowSize;
  const char *formatCmd;
  int descending;
  int labelOffset;
  TextStyle limitsTextStyle;
  const char *limitsFormat;
  int lineWidth;
  int logScale;
  int looseMin;
  int looseMax;
  Ticks* t1UPtr;
  Ticks* t2UPtr;
  double reqMin;
  double reqMax;
  Tcl_Obj *scrollCmdObjPtr;
  int scrollUnits;
  double reqScrollMin;
  double reqScrollMax;
  double shiftBy;
  double reqStep;
  int reqNumMajorTicks;
  int reqNumMinorTicks;
  int tickLength;
  const char *title;
  int titleAlternate;

  // The following fields are specific to logical axes

  XColor* activeFgColor;
  int activeRelief;
  Tk_3DBorder normalBg;
  int borderWidth;
  XColor* tickColor;
  Grid major;
  Grid minor;
  Tk_Justify titleJustify;
  int relief;
  double tickAngle;	
  Tk_Anchor reqTickAnchor;
  Tk_Font tickFont;
  Tk_Font titleFont;
  XColor* titleColor;

} AxisOptions;

class Axis {
 public:
  Graph* graphPtr_;
  ClassId classId_;
  const char* name_;
  const char* className_;
  Tk_OptionTable optionTable_;
  void* ops_;

  int use_;
  Tcl_HashEntry* hashPtr_;
  unsigned int flags;		

  // Fields specific to axes

  const char *detail_;
  int refCount_;
  Point2d titlePos_;
  unsigned short int titleWidth_;
  unsigned short int titleHeight_;	
  double min_;
  double max_;
  double scrollMin_;
  double scrollMax_;
  AxisRange valueRange_;
  AxisRange axisRange_;
  double prevMin_;
  double prevMax_;
  Ticks* t1Ptr_;
  Ticks* t2Ptr_;
  TickSweep minorSweep_;
  TickSweep majorSweep_;

  // The following fields are specific to logical axes

  int margin_;
  Blt_ChainLink link;
  Blt_Chain chain;
  Segment2d *segments_;
  int nSegments_;
  Blt_Chain tickLabels_;
  short int left_;
  short int right_;
  short int top_;
  short int bottom_;
  short int width_;
  short int height_;
  short int maxTickWidth_;
  short int maxTickHeight_; 
  Tk_Anchor tickAnchor_;
  GC tickGC_;
  GC activeTickGC_;
  double titleAngle_;	
  Tk_Anchor titleAnchor_;
  double screenScale_;
  int screenMin_;
  int screenRange_;

 protected:
  double niceNum(double, int);
  void setRange(AxisRange*, double, double);
  void makeGridLine(double, Segment2d*);
  void makeSegments(AxisInfo*);
  void resetTextStyles();
  void makeLine(int, Segment2d*);
  void makeTick(double, int, int, Segment2d*);
  void offsets(int, int, AxisInfo*);

 public:
  Axis(Graph*, const char*, int);
  virtual ~Axis();

  ClassId classId() {return classId_;}
  const char* name() {return name_;}
  const char* className() {return className_;}
  Tk_OptionTable optionTable() {return optionTable_;}
  void* ops() {return ops_;}

  int configure();
  void map(int, int);
  void draw(Drawable);
  void print(Blt_Ps);

  void mapStacked(int, int);
  void mapGridlines();
  void setClass(ClassId);
  void logScale(double, double);
  void linearScale(double, double);
  void fixRange();
  int isHorizontal();
  void freeTickLabels();
  TickLabel* makeLabel(double);
  void getDataLimits(double, double);
  Ticks* generateTicks(TickSweep*);
  int inRange(double, AxisRange*);

  double invHMap(double x);
  double invVMap(double y);
  double hMap(double x);
  double vMap(double y);
};

#endif
