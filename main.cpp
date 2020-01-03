#include <iostream>
#include <vector>
#include "solution.h"

using namespace std;

int main() {
  // I have coded two different solutions to the problem
  // the first solution is a simples sorted interval search in the X dimension that if it finds a X overlap it then checks for Y overlap
  // it is more efficient that the simple brute force solution but it still has a O(n^2) time complexity
  solution sol_sorted_simple;
  // we assume that there is a header line in the csv file and that the format is correct
  sol_sorted_simple.loadCSV("rectangles.csv");
  auto ret_sorted_simple = sol_sorted_simple.simpleSol();

  // I have also assumed that the rectangles are valid rectangles (no negative dimensions), that rectangles with 0 length or width are valid and that if two rectangles touch it counts as an overlap.
  cout << "SOLUTIONS SIMPLE:" << endl;
  for (auto result : ret_sorted_simple){
    cout << result.first << " " << result.second <<endl;
  }

  // the second solution is more complicated but also more efficient
  // it is inspired by the VLSI design rule check algorithms as described in this notes 
  // https://www.cs.princeton.edu/courses/archive/spr04/cos226/lectures/geometry2.4up.pdf
  // and it is implemented using a line sweep algorithm and a interval tree
  // The interval tree library is from https://github.com/5cript/interval-tree
  // It is implemented over a red-black tree for self balancing
  // I have modified to add a uid string attribute to each interval
  // The sweep line algorithm checks each rectangle in order from left to right once and then it runs a search on the interval tree to check for overlaps
  // Therefore the time complexity of this solution is O(n log(n) + R log(n)) where R is the number of intersections
  // The algorithm takes O(n log(n)) for the priority queue and the insertion and deletion of the intervals and O(n log(n) + R log(n)) to search for all the intersections
  // The line sweep algorithm reduces the problem to 1D and allows to operate in high numbers of rectangles

  solution sol_line_sweep;
  // we assume that there is a header line in the csv file and that the format is correct
  sol_line_sweep.loadCSV("rectangles.csv");
  sol_line_sweep.lineScan();
  auto ret_sweep = sol_line_sweep.sweepSol();

  // I have also assumed that the rectangles are valid rectangles (no negative dimensions), that rectangles with 0 length or width are valid and that if two rectangles touch it counts as an overlap.
  cout << "SOLUTIONS SWEEP LINE:" << endl;
  for (auto result : ret_sweep){
    cout << result.first << " " << result.second <<endl;
  }

  return 0;
}