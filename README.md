# Overlapping Rectangles Line Scan Algorithm
### Overview
Given a number of rectangles, this algorithm finds which rectangles overlap with other rectangles.  
It is inspired by the VLSI design rule check algorithms as described in [these notes](https://www.cs.princeton.edu/courses/archive/spr04/cos226/lectures/geometry2.4up.pdf).  
It is implemented using a line sweep algorithm and a interval tree using [this library](https://github.com/5cript/interval-tree) which uses a red-black tree for self balancing.  
The interval tree library has been modified to add a uid string attribute to each interval.  

### Time complexity
The sweep line algorithm checks each rectangle in order from left to right once and then it runs a search on the interval tree to check for overlaps.  
Therefore the time complexity of this solution is O(n log(n) + R log(n)) where R is the number of intersections.  
The algorithm takes O(n log(n)) for the priority queue and the insertion and deletion of the intervals and O(n log(n) + R log(n)) to search for all the intersections.  
The line sweep algorithm reduces the problem to 1D and allows to operate in high numbers of rectangles
