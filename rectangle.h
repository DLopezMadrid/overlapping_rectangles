#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <iostream>
#include <string>

using namespace std;

struct rectangle{
 public:
  string s_uid;
  float x_centre;
  float y_centre;
  float x_dim;
  float y_dim;
  pair<float, float> x_lim;
  pair<float, float> y_lim;

  rectangle(string n_s_uid, float n_x_centre, float n_y_centre, float n_x_dim, float n_y_dim);
  //overload < and == operator to use STL algos on the class instances
  bool operator<(rectangle &rhs);
  bool operator==(rectangle &rhs);
  //helper function for overlapY
  bool valueOverlaps(float value, float min, float max);
  bool overlapY(rectangle &rec);
  void display();
};


#endif