#include "rectangle.h"

//fint
rectangle::rectangle(string n_s_uid, float n_x_centre, float n_y_centre, float n_x_dim, float n_y_dim): s_uid {n_s_uid}, x_centre {n_x_centre},y_centre {n_y_centre}, x_dim{n_x_dim}, y_dim{n_y_dim}{
    x_lim = make_pair(x_centre, x_centre + x_dim);
    y_lim = make_pair(y_centre - y_dim, y_centre);
  }

bool rectangle::operator<(rectangle &rhs){
    return x_dim < rhs.x_dim;
}

bool rectangle::operator==(rectangle &rhs){
    return s_uid==rhs.s_uid;
}

bool rectangle::valueOverlaps(float value, float min, float max){
  return (value >= min) && (value <= max); 
};

bool rectangle::overlapY(rectangle &rec){
  bool overlap = valueOverlaps(this->y_lim.first, rec.y_lim.first, rec.y_lim.second) || valueOverlaps(rec.y_lim.first, this->y_lim.first, this->y_lim.second);
  return overlap;
};

void rectangle::display(){
  cout << "Rectangle id=" << s_uid << " x_centre=" << x_centre << " y_centre=" << y_centre << " x_dim=" << x_dim << " y_dim="<< y_dim << endl;
};