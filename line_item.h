#ifndef LINE_ITEM_H_
#define LINE_ITEM_H_

#include <memory>
#include "rectangle.h"

using namespace std;

struct lineItem{
  float pos;
  bool in_out;
  shared_ptr<rectangle> r;
  bool operator<(const lineItem rhs) const;
  lineItem(bool n_in_out, shared_ptr<rectangle> n_r);
  lineItem(){}
};

#endif