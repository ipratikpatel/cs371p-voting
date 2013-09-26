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
* Parses a test case and put all necessary information into variables as follows
* @param r 						a std::istream
* @param num_cand 				an int by reference to store number of candidates
* @param num_ballots 			an int by reference to store total number of ballots
* @param ballots 				a 2D int array to store actual ballot info
* @param names 					a 2D char array to store candidate names
* @param running_tally 			a vector of vector int by reference to separate ballots into candidate buckets
*/
void voting_read (std::istream&, int&, int& , int[][20], char[][81], std::vector< std::vector<int> >&);

// ------------
// voting_eval
// ------------

/**
* Evaluates the ballots to find the winner of an Australian vote. All the logic is performed here
* @param num_cand	 			an int by reference with number of candidates
* @param num_ballots			an int by reference with total number of ballots
* @param ballots  				a 2D int array with actual ballot info
* @param running_tally 			a vecotr of vector int by reference with candidate buckets info
* @param tally 					an int array to keep total tally of votes for each candidate
* @return the winning candidate's tally number
*/
int voting_eval (int& , int& , int [][20], std::vector< std::vector<int> >& , int*);

// -------------
// voting_print
// -------------

/**
* Prints the winning candidate name(s)
* @param w 						a std::ostream
* @param num_cand 				an int by reference with number of candidates
* @param names 					a 2D char array with candidates' names
* @param tally 					an int array with the candidates' total tally
* @param winning_tally 			an int by reference with the winning tally number
*/
void voting_print (std::ostream& , int& , char [][81] , int* , int& );

// -------------
// voting_solve
// -------------

/**
* Main function that calls voting_read, voting_eval, and voting_print to solve the Australian voting problem
* @param r 						a std::istream
* @param w 						a std::ostream
*/
void voting_solve (std::istream&, std::ostream&);

#endif // Voting_h