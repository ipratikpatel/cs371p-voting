// ----------------------------
// /cs371p-voting/Voting.h
// Copyright (C) 2013
// CS371p Fall 2013
// Kevin Tran
// Pratik Patel
// ----------------------------

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <vector>

// ------------
// voting_read
// ------------

/**
* reads two ints into i and j
* @param r a std::istream
* @param i an int by reference
* @param j an int by reference
* @return true if that succeeds, false otherwise
*/
void voting_read (std::istream&, int&, int& , int[][20], char[][81], std::vector< std::vector<int> >&);

// ------------
// voting_eval
// ------------

/*
* @param i is the value whose cycle length this function computes
* @return the cycle length of i
*/
// int voting_eval_help(unsigned long long);

/**
* @param i the beginning of the range, inclusive
* @param j the end of the range, inclusive
* @return the max cycle length in the range [i, j]
*/
int voting_eval (int , int , int [][20], std::vector< std::vector<int> >& , int*);

// -------------
// voting_print
// -------------

/**
* prints the values of i, j, and v
* @param w a std::ostream
* @param i the beginning of the range, inclusive
* @param j the end of the range, inclusive
* @param v the max cycle length
*/
void voting_print (std::ostream& , int& , char [][81] , int* , int& );

// -------------
// voting_solve
// -------------

/**
* read, eval, print loop
* @param r a std::istream
* @param w a std::ostream
*/
void voting_solve (std::istream&, std::ostream&);

#endif // Voting_h