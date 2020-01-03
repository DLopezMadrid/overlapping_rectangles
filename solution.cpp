#include "solution.h"

// creates a single rectangle from csv data and adds it to the rectangle vector
void solution::parseRec(vector<string> csvColumn){
  string s_uid {csvColumn[0]};
  //fint
  float x_centre {stof(csvColumn[1])};
  float y_centre {stof(csvColumn[2])};
  float x_dim {stof(csvColumn[3])};
  float y_dim {stof(csvColumn[4])};
  rectangles.emplace_back(s_uid, x_centre, y_centre, x_dim, y_dim); // more efficent than creating the object and then push it back
}

// from https://stackoverflow.com/a/9580763
void solution::readCSV(istream &input){
  int linecount {0};
  string csvLine;
  // read every line from the stream
  while(getline(input, csvLine) ){
    istringstream csvStream(csvLine);
    vector<string> csvColumn;
    string csvElement;
    // read every element from the line that is seperated by commas
    // and put it into the vector or strings
    while( getline(csvStream, csvElement, ',') ){
      csvColumn.push_back(csvElement);
    }
    linecount++;
    //skip the header line
    if (linecount > 1){
      parseRec(csvColumn);    //create rectangle with the data from the current line
    }
  }
}


void solution::loadCSV(std::string fname){
  try{
    //open file
    ifstream file("rectangles.csv");
    if(!file.is_open()){
      throw 1;
    }
    readCSV(file);
  }
  catch (int e){
    cout << "Error opening " << fname << " file" << endl;
  }
}

vector<pair<string, string>> solution::simpleSol(){
  if (rectangles.size() < 2){
    return ret;
  }

  // sort in X to reduce the number of comparisons
  sort(rectangles.begin(), rectangles.end(), [](rectangle r1, rectangle r2){return r1.x_lim.first < r2.x_lim.first;});

  for (size_t rec1{0}; rec1<rectangles.size()-1; ++rec1){
    for (size_t rec2{rec1+1}; rec2<rectangles.size(); ++rec2){
      // if the right-most part of the first rectangle is greater or equal than the left-most part of the second rectangle, then we have an overlapping in X, so we need to check for overlap in Y
      if (rectangles[rec1].x_lim.second >= rectangles[rec2].x_lim.first){
        // if there is an overlap in both X and Y, then the rectangles overlap
        if(rectangles[rec1].overlapY(rectangles[rec2])){
          ret.emplace_back(make_pair(rectangles[rec1].s_uid, rectangles[rec2].s_uid));
        }
      }
      else{
        // because the rectangles are sorted in the X dimension, if the current rec2 rectangle does not overlap with the rec1 rectangle, then the following rectangles will not do it either
        break;
      }
    }
  }

  return ret;
}

void solution::lineScan(){

  //creates the line scan by adding the start and end point of the different rectangles
  for(auto &r : rectangles){
    scan_line.push(lineItem(true, make_shared<rectangle>(r)));
    scan_line.push(lineItem(false, make_shared<rectangle>(r)));
  }
}


//line sweep solution as explained on https://www.cs.princeton.edu/courses/archive/spr04/cos226/lectures/geometry2.4up.pdf
vector<pair<string, string>> solution::sweepSol(){
  //corner case
  if (rectangles.size() < 2){
    return ret;
  }

  lineItem item;

  while(!scan_line.empty()){
    
    item = scan_line.top();
    scan_line.pop();

    // if we find a new rectangle 
    if(item.in_out == true){
      auto it_find = tree.begin();
      //check if there is any overlaps already in the tree
      it_find = tree.overlap_find({(item.r)->y_lim.first, (item.r)->y_lim.second}, false);

      // if an overlap is found we store the overlap and
      // then we search for additional overlaps.
      // Since the overlap_find function only returns the first result
      // we create a tree copy and delete the found items from it
      // until we find the end of the tree
      // There is an overlap_find_next function but the lack of documentation prevented me from being able to implemement it correctly
      if (it_find!=tree.end()){
        //store the overlap
        ret.push_back({(*it_find).uid,(item.r)->s_uid});
        auto tree_copy = tree;
        auto it_find_copy = tree_copy.overlap_find({(item.r)->y_lim.first, (item.r)->y_lim.second}, false);
        //use the copy tree and iterator to remove the found results and keep looking for additional overlaps
        while (it_find_copy != tree_copy.end()){
          tree_copy.erase(it_find_copy);
          it_find_copy = tree_copy.overlap_find({(item.r)->y_lim.first, (item.r)->y_lim.second}, false);
          //if there is an overlap store it in ret
          if (it_find_copy != tree_copy.end()){
            ret.push_back({(*it_find_copy).uid,(item.r)->s_uid});
          }
        }
      }

      //create the new interval and insert it into the tree
      lib_interval_tree::interval<float, lib_interval_tree::closed> new_interval ({(item.r)->y_lim.first, (item.r)->y_lim.second});
      new_interval.uid = (item.r)->s_uid;
      tree.insert(new_interval);
    }
    else{
      // if the next line item is the end of a rectangle, remove that rectangle from the tree
      auto it_delete {tree.find({(item.r)->y_lim.first, (item.r)->y_lim.second})};
      if (it_delete != tree.end()){
        tree.erase(it_delete);
      }
    }
  }

  return ret;
};