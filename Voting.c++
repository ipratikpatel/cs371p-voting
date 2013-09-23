// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert> // assert
#include <iostream> // endl, istream, ostream

#include "Collatz.h"

// ------------
// collatz_read
// ------------

bool collatz_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}

// ------------
// collatz_eval
// ------------

const unsigned int sizearr = 100001;
 int cache[sizearr] ;

int collatz_eval_help (unsigned long long i){
	assert(i > 0);
    int x = 1;

	if( i == 1)
	return 1;

	if((i < sizearr) && (cache[i]))
		return cache[i];
	 else{  
		if ((i % 2) == 0)
		{
			if(i < sizearr)
			{
			cache[i] = 1 + collatz_eval_help(i >> 1);
			x = cache[i];
			}
			else
				x = 1 + collatz_eval_help(i >> 1);
	
		}
		else
		{
			 if(i <sizearr){
				 cache[i] = 2 + collatz_eval_help( (3 * i + 1) >> 1);
				 x = cache[i];
			 }
			 else
				 x = 2 + collatz_eval_help((3 * i + 1) >> 1);
		}
     
		assert(x > 0);
		return x;
	 }
}



/*int collatz_eval_help (int i){
	assert(i > 0);
	unsigned long long ans = (unsigned long long) i;
    int x = 1;
    while (ans != 1) 
    {
        if ((ans % 2) == 0){
            ans = (ans / 2);
	x++;
	}
        else{
            ans = (3 * ans) + 1;
	    ans = ans /2;
	x += 2;
	}
     }
    assert(x > 0);
    return x;
}*/

int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);
	int m;
	int n;
	int temp;
	
	if(i > j){
	m = j;
	n = i;
	}
	else{
	m = i;
	n = j;
		}
	assert(n >= m);	
	
	int ans = 1;
        int half = n / 2;
	if(half > m){
	temp = half;}
	else
	 temp = m;
	int max = 1;
	while(temp <= n){
		ans = collatz_eval_help((unsigned long long) temp);
		if(ans > max)
			max = ans;
		++temp;
	}
    // <your code>
   // int v = 1;
    assert(max > 0);
    return max;}


// -------------
// collatz_print
// -------------

void collatz_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}
	}

