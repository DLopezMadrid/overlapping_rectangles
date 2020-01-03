#include "line_item.h"

bool lineItem::operator<(const lineItem rhs) const{
  if (pos == rhs.pos){
    return in_out <= rhs.in_out; // to cope with width 0 rectangles and have them always inserted before being removed from the queue
  }
  return pos > rhs.pos;
}

lineItem::lineItem(bool n_in_out, shared_ptr<rectangle> n_r){
  in_out = n_in_out;
  r = n_r;
  if (in_out){
    pos = r->x_lim.first;
  }
  else{
    pos = r->x_lim.second;
  }
}