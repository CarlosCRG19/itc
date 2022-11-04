#include <bits/stdc++.h>

using namespace std;

struct Point {
  double x;
  double y;
};

pair<double, bool> getSlope(Point p, Point q) {
  if (q.x == p.x)
    return make_pair(0, false);

  double slope = (q.y - p.y) / (q.x - p.x);

  return make_pair(slope, true);
}

bool doIntersect(Point a1, Point a2, Point b1, Point b2) {
  // Overlap in X
  if (a2.x < b1.x || b2.x < a1.x)
    return false;

  // Overlap in Y
  if (max(a1.y, a2.y) < min(b1.y, b2.y) || min(a1.y, a2.y) < max(b1.y, b2.y))
    return false;

  pair<double, bool> mA = getSlope(a1, a2);
  pair<double, bool> mB = getSlope(b1, b2);

  double bA = a1.y - mA.first*a1.x;
  double bB = b1.y - mB.first*b1.x;

  if (mA.first == mB.first)
    return bA == bB;

  double X = (bB - bA) / (mA.first - mB.first);

  double low = max(a1.x, b1.x);
  double high = min(a2.x, b2.x);

  return X <= high && X >= low;
}

int main() {
  int n;
  cin >> n;

  for (int i=0 ; i < (n/8) ; i++) {
    double a1x; cin >> a1x;
    double a1y; cin >> a1y;
    double a2x; cin >> a2x;
    double a2y; cin >> a2y;

    double b1x; cin >> b1x;
    double b1y; cin >> b1y;
    double b2x; cin >> b2x;
    double b2y; cin >> b2y;

    struct Point a1 = { a1x, a1y };
    struct Point a2 = { a2x, a2y };
    struct Point b1 = { b1x, b1y };
    struct Point b2 = { b2x, b2y };

    cout << doIntersect(a1, a2, b1, b2) << '\n';
  }

  return 0;
}
