/************************************************************************
*
*  lap.h
   version 1.0 - 21 june 1996
   author  Roy Jonker, MagicLogic Optimization Inc.

   header file for LAP
*
      pyLAPJV by Harold Cooper (hbc@mit.edu)
      2004-08-13:
          -- fixed Jonker's function declarations to actually use row, col,
             and cost types
          -- row, col, and cost now based on basic types
*
**************************************************************************/

/*************** CONSTANTS  *******************/

#define BIG 1.79769e+308 // max value for double

/*************** TYPES      *******************/

typedef int row;
typedef int col;
typedef double cost;

/*************** FUNCTIONS  *******************/

extern cost lap(int dim, cost **assigncost, col *rowsol, row *colsol, cost *u, cost *v);
