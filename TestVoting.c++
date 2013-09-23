// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// --------------------------------

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

% g++ -pedantic -std=c++0x -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lpthread -lgtest_main

% valgrind TestCollatz > TestCollatz.out
*/

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream> // istringtstream, ostringstream
#include <string> // ==

#include "gtest/gtest.h"

#include "Collatz.h"

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

    TEST(Collatz, read) {
        std::istringstream r("1 10\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        ASSERT_TRUE(b == true);
        ASSERT_TRUE(i == 1);
        ASSERT_TRUE(j == 10);}


    TEST(Collatz, read_2) {
        std::istringstream r("250 50\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        ASSERT_TRUE(b == true);
        ASSERT_TRUE(i == 250);
        ASSERT_TRUE(j == 50);}

    TEST(Collatz, read_3) {
        std::istringstream r("1 1000000\n");
        int i;
        int j;
        const bool b = collatz_read(r, i, j);
        ASSERT_TRUE(b == true);
        ASSERT_TRUE(i == 1);
        ASSERT_TRUE(j == 1000000);}

// ----
// collatz_eval_help
// ----
    TEST(Collatz, test_collatz_eval_help_1) {
        int i = collatz_eval_help(1);
        ASSERT_TRUE(i == 1);}
        
        
    TEST(Collatz, test_collatz_eval_help_2) {
        int i = collatz_eval_help(5);
        ASSERT_TRUE(i == 6);}
    
    
    TEST(Collatz, test_collatz_eval_help_3) {
        int i = collatz_eval_help(10);
        ASSERT_TRUE(i == 7);}
        
        
    TEST(Collatz, test_collatz_eval_help_4) {
        int i = collatz_eval_help(20);
        ASSERT_TRUE(i == 8);}
        
        
    // ----
    // eval
    // ----


    TEST(Collatz, eval_1) {
        const int v = collatz_eval(1, 10);
        ASSERT_TRUE(v == 20);}

    TEST(Collatz, eval_2) {
        const int v = collatz_eval(100, 200);
        ASSERT_TRUE(v == 125);}

    TEST(Collatz, eval_3) {
        const int v = collatz_eval(201, 210);
        ASSERT_TRUE(v == 89);}

    TEST(Collatz, eval_4) {
        const int v = collatz_eval(900, 1000);
        ASSERT_TRUE(v == 174);}

    TEST(Collatz, eval_5){
        const int v = collatz_eval(2570, 3486);
        ASSERT_TRUE(v == 217);}

    TEST(Collatz, eval_6){
        const int v = collatz_eval(3225, 11789);
        ASSERT_TRUE(v == 268);}

// -----
// print
// -----

    TEST(Collatz, print) {
        std::ostringstream w;
        collatz_print(w, 1, 10, 20);
        ASSERT_TRUE(w.str() == "1 10 20\n");}

    TEST(Collatz, print_2) {
        std::ostringstream w;
        collatz_print(w, 100, 10000, 12345);
        ASSERT_TRUE(w.str() == "100 10000 12345\n");}

    TEST(Collatz, print_3){
        std::ostringstream w;
        collatz_print(w, 3225, 11789, 268);
        ASSERT_TRUE(w.str() == "3225 11789 268\n");
        }

    // -----
// solve
// -----

    TEST(Collatz, solve) {
        std::istringstream r("1 10\n100 200\n201 210\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n900 1000 174\n");}

    TEST(Collatz, solve_2) {
        std::istringstream r("1 10\n3571 2658\n19931 23385\n5653 23687\n");
        std::ostringstream w;
        collatz_solve(r, w);
        ASSERT_TRUE(w.str() == "1 10 20\n3571 2658 217\n19931 23385 269\n5653 23687 282\n");}

    TEST(Collatz, solve_3) {
        std::istringstream r("1 10\n100 200\n201 210\n6701 4832\n900 1000\n");
        std::ostringstream w;
        collatz_solve(r, w);
        ASSERT_TRUE(w.str() == "1 10 20\n100 200 125\n201 210 89\n6701 4832 262\n900 1000 174\n");}

