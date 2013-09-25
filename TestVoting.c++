// ----------------------------
// /cs371p-voting/TestVoting.c++
// Copyright (C) 2013
// CS371p Fall 2013
// Kevin Tran
// Pratik Patel
// ----------------------------

/*
To test the program:
% ls -al /usr/include/gtest/
...
gtest.h
...

% locate libgtest.a
/usr/lib/libgtest.a

% locate libpthread.a
/usr/lib/x86_64-linux-gnu/libpthread.a
/usr/lib32/libpthread.a

% locate libgtest_main.a
/usr/lib/libgtest_main.a

% g++ -pedantic -std=c++0x -Wall Voting.c++ TestVoting.c++ -o TestVoting -lgtest -lpthread -lgtest_main

% valgrind TestVoting > TestVoting.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==
#include <vector>

#include "gtest/gtest.h"

#include "Voting.h"


// -----------
// voting_read
// -----------

    TEST(Voting, read_1) 
    {
        std::istringstream r("3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2");
        int num_cand;
        int num_ballots;
        int ballots[6][20];
        char names[4][81];
        int tally[21];
        std::vector< std::vector<int> > running_tally(21);


        const bool b = voting_read(r, num_cand, num_ballots, ballots, names, running_tally);
        int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);
        voting_print(std::cout, num_cand, names, tally, winning_tally);


        ASSERT_TRUE(b == true);
        ASSERT_TRUE(num_cand == 3);
        ASSERT_TRUE(num_ballots == 5);
        ASSERT_TRUE(strcmp(names[1], "John Doe") == 0);
        ASSERT_TRUE(strcmp(names[2], "Jane Smith") == 0);
        ASSERT_TRUE(strcmp(names[3], "Sirhan Sirhan") == 0);

    }


    TEST(Voting, read_2) 
    {
        std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
        int num_cand;
        int num_ballots;
        int ballots[6][20];
        char names[4][81];
        int tally[21];
        std::vector< std::vector<int> > running_tally(21);


        const bool b = voting_read(r, num_cand, num_ballots, ballots, names, running_tally);
        int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);
        voting_print(std::cout, num_cand, names, tally, winning_tally);

        ASSERT_TRUE(b == true);
        ASSERT_TRUE(num_cand == 3);
        ASSERT_TRUE(num_ballots == 5);
        ASSERT_TRUE(strcmp(names[1], "John Doe") == 0);
        ASSERT_TRUE(strcmp(names[2], "Jane Smith") == 0);
        ASSERT_TRUE(strcmp(names[3], "Sirhan Sirhan") == 0);

    }


    // TEST(Voting, read_3) 
    // {
    //       std::istringstream r("4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
    //     int num_cand;
    //     int num_ballots;
    //     int ballots[6][20];
    //     char names[4][81];
    //     int tally[21];
    //     std::vector< std::vector<int> > running_tally(21);


    //     const bool b = voting_read(r, num_cand, num_ballots, ballots, names, running_tally);
    //     int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);
    //     voting_print(std::cout, num_cand, names, tally, winning_tally);

    //     ASSERT_TRUE(b == true);
    //     ASSERT_TRUE(num_cand == 3);
    //     ASSERT_TRUE(num_ballots == 5);
    //     ASSERT_TRUE(strcmp(names[1], "John Doe") == 0);
    //     ASSERT_TRUE(strcmp(names[2], "Jane Smith") == 0);
    //     ASSERT_TRUE(strcmp(names[3], "Sirhan Sirhan") == 0);

    // }

  
// -----------
// voting_eval
// -----------


    // TEST(Voting, eval_1) 
    // {
    //     const int v = Voting_eval(1, 10);
    //     ASSERT_TRUE(v == 20);
    // }

    // TEST(Voting, eval_2) 
    // {
    //     const int v = Voting_eval(100, 200);
    //     ASSERT_TRUE(v == 125);
    // }

    // TEST(Voting, eval_3) 
    // {
    //     const int v = Voting_eval(201, 210);
    //     ASSERT_TRUE(v == 89);
    // }


// ------------
// voting_print
// ------------

    // TEST(Voting, print_1) 
    // {
    //     std::ostringstream w;
    //     Voting_print(w, 1, 10, 20);
    //     ASSERT_TRUE(w.str() == "1 10 20\n");
    // }

    // TEST(Voting, print_2) 
    // {
    //     std::ostringstream w;
    //     Voting_print(w, 100, 10000, 12345);
    //     ASSERT_TRUE(w.str() == "100 10000 12345\n");
    // }

    // TEST(Voting, print_3)
    // {
    //     std::ostringstream w;
    //     Voting_print(w, 3225, 11789, 268);
    //     ASSERT_TRUE(w.str() == "3225 11789 268\n");
    // }

// -------------
// voting_solve
// -------------

    TEST(Voting, solve_1) 
    {
        std::istringstream r("2 3\nJohn Doe\nJane Smith\nSirhan Sirhan\n1 2 3\n2 1 3\n2 3 1\n1 2 3\n3 1 2\n\n4\nRed\nGreen\nBlue\nOrange\n1 2 3 4\n2 1 3 4\n2 3 1 4\n1 2 3 4\n3 4 1 2\n4 3 2 1");
        std::ostringstream w;
        voting_solve(r, w);
        std::cout << w.str() << std::endl;
        ASSERT_TRUE(w.str() == "John Doe\n\nRed\nGreen");
    }

    // TEST(Voting, solve_2) 
    // {
    //     std::istringstream r("1 10\n3571 2658\n19931 23385\n5653 23687\n");
    //     std::ostringstream w;
    //     Voting_solve(r, w);
    //     ASSERT_TRUE(w.str() == "1 10 20\n3571 2658 217\n19931 23385 269\n5653 23687 282\n");
    // }

    // TEST(Voting, solve_3) 
    // {
    //     std::istringstream r("1 10\n100 200\n201 210\n6701 4832\n900 1000\n");
    //     std::ostringstream w;
    //     Voting_solve(r, w);
    //     ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n6701 4832 262\n900 1000 174\n");
    // }

