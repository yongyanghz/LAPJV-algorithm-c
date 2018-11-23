# LAPJV-algorithm-c

version 1.0 - 4 September 1996
   author: Roy Jonker @ MagicLogic Optimization Inc.
   e-mail: roy_jonker@magiclogic.com

   Code for Linear Assignment Problem, according to 
   
   "A Shortest Augmenting Path Algorithm for Dense and Sparse Linear   
    Assignment Problems," Computing 38, 325-340, 1987
   
   by
   
   R. Jonker and A. Volgenant, University of Amsterdam.
   

   CHANGED 2016-05-13 by Yong Yang(yongyanglink@gmail.com) in column reduction part according to 
   matlab version of LAPJV algorithm(Copyright (c) 2010, Yi Cao All rights reserved)--
  


## Additional information:

The original code is download from  python wrapper for C++ code on github https://github.com/hrldcpr/pyLAPJV.
LAPJV comes from the paper:

R. Jonker and A. Volgenant, "A Shortest Augmenting Path Algorithm for Dense and Sparse Linear Assignment Problems," Computing, vol. 38, pp. 325-340, 1987.

According to that paper, it is notably faster than the Hungarian algorithm (a.k.a. Munkres' algorithm) and several other linear assignment algorithms.

The C++ source comes from: http://www.magiclogic.com/assignment.html

If any of those links are broken then try them in the Wayback Machine! For example the original C++ source zip can be obtained at: https://web.archive.org/web/*/http://www.magiclogic.com/assignment/lap_cpp.zip

The matlab code of lap JV algorithm comes from:  https://www.mathworks.com/matlabcentral/fileexchange/26836-lapjv-jonker-volgenant-algorithm-for-linear-assignment-problem-v3-0:


## Usage Example

```   
    // Notice that col, row, cost these types are typedef-ed in lap.h
    int dim = 10;        // Set the dimension of matrix to 10, dim is the problem size
    int** costMatrix;    // A matrix to store all the costs from vertex i to vertex j
    col *rowsol;         // A array to store row solution, 0 means not selected, 1 means selected 
    row *colsol;         // A array to store column solution, 0 means not selected, 1 means selected 
    cost *u;             // u          - dual variables, row reduction numbers
    cost *v;             // v          - dual variables, column reduction numbers
    rowsol = new col[dim];
    colsol = new row[dim];
    u = new cost[dim];
    v = new cost[dim];
    costMatrix = new int*[dim];
    for(int i=0;i<dim;i++){
        costMatrix[i]  =  new int[dim];
    }
    // Assign costs to the costMatrix
    for(int i=0; i<dim; ++i)
        for(int j=0; j<dim; ++j)
            costMatrix[i][j]  =  rand();
            
    cost totalCost = lap(dim, costMatrix, rowsol, colsol, u, v);  // Use lap algorithm to calculate the minimum total cost
```
