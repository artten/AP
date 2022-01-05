#include "minCircle.h"
#include <cmath>

// return 1 if point is inside the circle, 0 otherwise
int isInsideCircle(Circle c, Point p) {
  if (distanceBetween2Points(c.center, p) > c.radius) {
       return 0;
     }
     return 1;
}

// return 1 if point is inside the circle, 0 otherwise
int isInsideCircle(Circle c, float x, float y) {
  return isInsideCircle(c, Point(x, y));
}

// returns the distance Between 2 Points
float distanceBetween2Points(Point p1, Point p2) {
  return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

Point centerbetween2Points(Point p1, Point p2) {
  Point p = Point();
  p.x = (p1.x + p2.x) / 2;
  p.y = (p1.y + p2.y) / 2;
  return p;
}

Circle findCirclefrom1Point(Point p) {
  Circle c = Circle();
  c.radius = 0;
  c.center = p;
  return c;
}

Circle findCirclefrom2Points(Point p1, Point p2) {
  Circle c = Circle();
  c.radius = distanceBetween2Points(p1, p2) / 2.0;
  c.center = centerbetween2Points(p1, p2);
  return c;
}


// create a circle from 3 point using 3 equation.
Circle findCirclefrom3Points(Point p1, Point p2, Point p3) {
  float resultX, resultY, resultR;
  float factorX1, factorY1, factorX2, factorY2;
  float cons1, cons2;
  factorX1 = (p1.x * 2.0) - (p2.x * 2.0);
  if (factorY1 != 0.0) {
    factorY1 = (p1.y * 2.0) - (p2.y * 2.0);
    factorX2 = (p3.x * 2.0) - (p2.x * 2.0);
    factorY2 = (p3.y * 2.0) - (p2.y * 2.0);
    cons1 = std::pow(p1.x, 2) - std::pow(p2.x, 2) + std::pow(p1.y,2) - std::pow(p2.y, 2);
    cons2 = std::pow(p3.x, 2) - std::pow(p2.x, 2) + std::pow(p3.y,2) - std::pow(p2.y, 2);
  }
  else {
    factorX1 = (p3.x * 2.0) - (p2.x * 2.0);
    factorY1 = (p3.y * 2.0) - (p2.y * 2.0);
    factorX2 = (p1.x * 2.0) - (p2.x * 2.0);
    factorY2 = (p1.y * 2.0) - (p2.y * 2.0);
    cons1 = std::pow(p3.x, 2) - std::pow(p2.x, 2) + std::pow(p3.y,2) - std::pow(p2.y, 2);
    cons2 = std::pow(p1.x, 2) - std::pow(p2.x, 2) + std::pow(p1.y,2) - std::pow(p2.y, 2);
  }
/*
  if (factorY1 == 0.0) {
    resultX = cons1 / factorX1;
    resultY
  }
  else {
  */
  resultX = ((cons1 * (factorY2 / factorY1)) - cons2) /
   ((factorX1 * (factorY2 / factorY1)) - factorX2);
  resultY = (cons1 - (resultX * factorX1)) / (factorY1);
//  }
  resultR = std::sqrt(std::pow(p1.x - resultX, 2) + std::pow(p1.y - resultY, 2));
  Circle c = Circle();
  c.center.x = resultX;
  c.center.y = resultY;
  c.radius = resultR;
  return c;
}

Circle findMinCircle(Point** points,size_t size) {
  std::vector<Point> r;
  return (welzlMinCircle(points, size, r));
}

Circle calcCircle(vector<Point> r) {
  if (r.empty()) {
    Circle c = Circle();
    return c;
  }
  if (r.size() >= 3) {
    return findCirclefrom3Points(r[0], r[1], r[2]);
  }
  if (r.size() == 2) {
    return findCirclefrom2Points(r[0], r[1]);
  }
  if (r.size() == 1) {
    return findCirclefrom1Point(r[0]);
  }
  return Circle();
}

Circle welzlMinCircle(Point** points, size_t index, vector<Point> r) {
  Circle c = Circle();
  //if (points.empty() || r.size() >= 3)
  if (index <= 0 || r.size() >= 3) {
    c = calcCircle(r);
    r.pop_back();
    return c;
    //return calcCircle(r);
  }
  c = welzlMinCircle(points, index - 1, r);
  if (isInsideCircle(c, *points[index - 1])) {
    return c;
  }
  r.push_back(*points[index - 1]);
  return welzlMinCircle(points, index - 1, r);
}