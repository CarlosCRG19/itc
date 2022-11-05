/* IMPLEMENTACIÓN POLÍGONOS CONVEXOS APLICANDO GEOMETRÍA COMPUTACIONAL
 *
 * - José Antonio Chaires Monroy      A01640114
 * - Carlos César Rodríguez García    A00344666
 * */

#include <bits/stdc++.h>

using namespace std;

struct Point {
  double x;
  double y;
};

// Checks if point r belongs to an specific segment.
// Time complexity: O(1).
bool isOnSegment(Point p, Point q, Point r)
{
  if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
    q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
    return true;

  return false;
}

// Calculates geometric orientation of three points.
// Time complexity: O(1).
int findOrientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
  
    // 0 -> collinear 
    if (val == 0) return 0; 
  
    // 1 -> clock wise
    // 2 -> counter-clock wise
    return (val > 0) ? 1 : 2; 
}

// Detects intersection between two segments, points p1 and p2 correspond to the beginning of each segment.
// Time complexity: O(1).
bool hasIntersection(Point p1, Point q1, Point p2, Point q2) {
    int o1 = findOrientation(p1, q1, p2);
    int o2 = findOrientation(p1, q1, q2);
    int o3 = findOrientation(p2, q2, p1);
    int o4 = findOrientation(p2, q2, q1);
  
    if (o1 != o2 && o3 != o4)
      return true;
  
    if (o1 == 0 && isOnSegment(p1, p2, q1)) 
      return true;
  
    if (o2 == 0 && isOnSegment(p1, q2, q1)) 
      return true;
  
    if (o3 == 0 && isOnSegment(p2, p1, q2)) 
      return true;
  
    if (o4 == 0 && isOnSegment(p2, q1, q2)) 
      return true;
  
    return false;
}

int main() {
  int n;
  cin >> n;

  for (int i=0 ; i < (n/8) ; i++) {
    double a1x; cin >> a1x;
    double a1y; cin >> a1y;
    double a2x; cin >> a2x;
    double a2y; cin >> a2y;

    Point p1 = {a1x, a1y};
    Point p2 = {a2x, a2y};

    double b1x; cin >> b1x;
    double b1y; cin >> b1y;
    double b2x; cin >> b2x;
    double b2y; cin >> b2y;

    Point q1 = { b1x, b1y };
    Point q2 = { b2x, b2y };

    cout << hasIntersection(p1, p2, q1, q2) << '\n';
  }

  return 0;
}
