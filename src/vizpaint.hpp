#ifndef VIZPAINT_H_INCLUDED
#define VIZPAINT_H_INCLUDED

#include "vizdef.hpp"
#include "vizparam.hpp"

namespace smashpp {
struct RgbColor {
  u8 r, g, b;
};

struct HsvColor {
  u8 h, s, v;
  HsvColor () = default;
  explicit HsvColor (u8 hue) : h(hue), s(PAINT_LVL_SATUR), v(PAINT_LVL_VAL) {}
};

struct Point {
  double x, y;
  Point       () = default;
  Point       (double x_, double y_) { config(x_,y_); }
  void config (double x_, double y_) { x=x_;  y=y_; }
};

class Text {
 public:
  Text        () = default;
  Text        (Point, const string&);
  void config (Point, const string&);
  void plot   (ofstream&) const;

 private:
  Point  origin;
  string label;
};

class Line {
 public:
  Line        () = default;
  Line        (Point, Point, double, const string&);
  void config (Point, Point, double, const string&);
  void plot   (ofstream&) const;

 private:
  Point  beg, end;
  double width;
  string color;
};

class Rectangle {
 public:
  Rectangle            () = default;
  Rectangle            (Point, double, double, const string&);
  void config          (Point, double, double, const string&);
  void plot            (ofstream&) const;
  void plot_ir         (ofstream&) const;
  void plot_oval       (ofstream&) const;
  void plot_oval_ir    (ofstream&) const;
  void plot_chromosome (ofstream&) const;

 private:
  Point  origin;
  double width, height;
  string color;
};

class Polygon {
 public:
  Polygon     () = default;
  Polygon     (Point, Point, Point, Point, const string&, const string&);
  void config (Point, Point, Point, Point, const string&, const string&);
  void plot   (ofstream&) const;

 private:
  Point  one, two, three, four;
  string lineColor, fillColor;
};

class Circle {
 public:
  Circle      () = default;
  Circle      (Point, double, const string&);
  void config (Point, double, const string&);
  void plot   (ofstream&) const;

 private:
  Point  origin;
  double radius;
  string fillColor;
};

class VizPaint {
 public:
  double cx, cy;
  double tx, ty;
  string backColor;
  double width;
  double space;
  double refSize, tarSize, maxSize;

  VizPaint() : cx(PAINT_CX), cy(PAINT_CY), tx(PAINT_TX), ty(PAINT_TY),
               backColor(PAINT_BGCOLOR), width(0.0), space(0.0), refSize(0.0),
               tarSize(0.0), maxSize(0.0), ratio(1) {}
  void print_plot (VizParam&);

 private:
  u32 ratio;

  void     config     (double, double, u64, u64);
  RgbColor hsv_to_rgb (const HsvColor&)           const;
  HsvColor rgb_to_hsv (const RgbColor&)           const;
  string   rgb_color  (u8)                        const;
  void     print_head (ofstream&, double, double) const;
  void     print_tail (ofstream&)                 const;
  template <typename Value>
  double   get_point  (Value)                     const;
};
}

#endif