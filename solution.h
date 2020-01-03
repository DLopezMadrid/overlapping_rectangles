#ifndef SOLUTION_H_
#define SOLUTION_H_

#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <memory>
#include "interval_tree/interval_tree.hpp"
#include "line_item.h"
#include "rectangle.h"

using namespace std;
using namespace lib_interval_tree;


class solution {
 public:
  vector<pair<string, string>> simpleSol();
  void loadCSV(string fname);
  void lineScan();
  vector<pair<string, string>> sweepSol();

 private:
  void parseRec(vector<string> csvColumn);
  void readCSV(istream &input);
  vector<rectangle> rectangles;
  vector<vector<float>> overlaps;
  vector<vector<float>> intervals_x;
  vector<vector<float>> intervals_y;
  vector<pair<string, string>> ret;
  priority_queue<lineItem> scan_line;
  interval_tree_t <float, lib_interval_tree::closed> tree;
};


#endif