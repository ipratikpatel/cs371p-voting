// ----------------------------
// projects/voting/Voting.c++
// Copyright (C) 2013
// Kevin Tran
// Pratik Patel
// ----------------------------

// --------
// includes
// --------

#include <cassert> // assert
#include <iostream> // endl, istream, ostream
#include <vector>
#include <algorithm>

#include "Voting.h"

#define DB 0

// ------------
// voting_read
// ------------

bool voting_read (std::istream& r, int& num_cand, int& num_ballots , int ballots[][20], char names[][81], std::vector< std::vector<int> >& running_tally) {
    r >> num_cand;
    if(DB) printf("Number of candidates %d\n", num_cand );
    assert(num_cand > 0);
    // eats the new line after the num_cand
    r.get();
    for (int i = 1; i <= num_cand; ++i)
    {
    	r.getline(names[i], 80);
    	if(DB) printf("%s\n", names[i] );
    }

    int row = 0;
    int col;
 
    while((r.peek() != '\n') )
    {
    	for (col = 0; col < num_cand; ++col)
    	{
    		r >> ballots[row][col];
    		if(DB) printf("%d ", ballots[row][col] );
    	}
    	if(DB) printf("\n");

    	//Eat the new line char from each row
    	r.get();

    	running_tally[ballots[row][0]].push_back(row);
    	++row;

    	// checks if you reached the EOF
    	if(!r)
    		break;
    	

    }
    	num_ballots = row;
    return true;}

// ------------
// voting_eval_help
// ------------

// void voting_eval_help (int& num_cand, std::vector< vector<int> >& running_tally, std::vector<int>& losers, int tally[21])
// {

	 
// }



/*int voting_eval_help (int i){
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

int voting_eval (int num_cand, int num_ballots, int ballots[][20], std::vector< std::vector<int> >& running_tally, int tally[21]) 
{
	std::vector<int> losers;


	std::cout << "running_tally at 0 " << running_tally[0].size() << std::endl;
	std::cout << "running_tally at 1 " << running_tally[1].size() << std::endl;
	std::cout << "running_tally at 2 " << running_tally[2].size() << std::endl;
	std::cout << "running_tally at 3 " << running_tally[3].size() << std::endl;
	std::cout << "running_tally at 4 " << running_tally[4].size() << std::endl;


	//counts first-place votes
	for (int i = 1; i <= num_cand; ++i)
	{
		tally[i] = running_tally[i].size();

		std::cout << "tally #s: " << tally[i] << std::endl;
	}

	// std::cout << "in voting eval" << std::endl;

	while(1)
	{
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		int max_tally = tally[1];
		int min_tally = tally[1];
		int temp_min = 0;

		//find max and min number of votes
		for (int i = 1; i <= num_cand; ++i)
		{
			std::cout << "tally at " << i << " is " << tally[i] << std::endl;
			if(tally[i] > num_ballots / 2)
				return tally[i];
			else
			{
				max_tally = std::max(tally[i], max_tally);
				temp_min = std::min(tally[i], min_tally);
				if (temp_min > 0)
					min_tally = temp_min;

				std::cout << "temp_min: " << temp_min << " min_tally: " << min_tally << std::endl;

			}
		}

		std::cout << "max_tally: " << max_tally << " min_tally " << min_tally << std::endl;

		//check if all tie
		if (max_tally == min_tally)
			return max_tally;

		//no clear winner, vote re-distribution
		//first loop adds loser to a list
		losers.clear();
		for (int i = 0; i <= num_cand; ++i)
		{
			if(tally[i] == min_tally)
			{
				losers.push_back(i);
				std::cout << "losers # " << i << std::endl;
			}
		}

		//second loop re-distributes vote
		for (unsigned int i = 0; i < losers.size(); ++i)
		{
			std::cout << "currently in loser #: " << losers[i] << std::endl;
			std::cout << "loser's vector size: " << running_tally[ losers[i] ].size() << std::endl;
			//loops through losers' ballots
			for (int j = running_tally[ losers[i] ].size() - 1; j >= 0; --j)
			{
				std::cout << "loser #: " << losers[i] << " at ballot pos: " << running_tally[ losers[i] ][j] << std::endl;
				//loops through new candidates
				for (int k = 1; k <= num_cand; ++k)
				{
					std::cout << "currently looking at candidate # " << k << " in ballot" << std::endl;
					bool found = true;
					//check if new vote is in losers list
					for (unsigned int l = 0; l < losers.size(); ++l)
					{
						std::cout << "new winner in ballot is " << ballots[ running_tally[ losers[i] ][j] ][k] << " and loser list have cand: " << losers[l] << std::endl;
						if (ballots[ running_tally[ losers[i] ][j] ][k] == losers[l])
						{
							found = false;
							break;
						}
					}
					if (found)
					{
						std::cout << "Loser cand #: " << losers[i] << std::endl;
						std::cout << "New cand winner #: " << ballots[ running_tally[ losers[i] ][j] ][k] << " ballot #: " << running_tally[ losers[i] ][j] << std::endl;
						running_tally[ ballots[ running_tally[ losers[i] ][j] ][k] ].push_back( running_tally[ losers[i] ][j] );
						running_tally[ losers[i] ].pop_back();
						std::cout << " tally at pos " << ballots[ running_tally[ losers[i] ][j] ][k] << " before is " << tally[ ballots[ running_tally[ losers[i] ][j] ][k] ] << std::endl;
						++tally[ ballots[ running_tally[ losers[i] ][j] ][k] ];
						std::cout << "just incremented tally at pos " << ballots[ running_tally[ losers[i] ][j] ][k] << std::endl;
						tally[ losers[i] ] = -1;
						break;
					}					
				}

			}
		}


    }

}


// -------------
// voting_print
// -------------

void voting_print (std::ostream& w, int i, int j, int v) 
{
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;
}

// -------------
// voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w) 
{
    int num_test;
    r >> num_test;
    int num_cand;
    int num_ballots;
    int ballots[1000][20];
    char names[21][81];
    int tally[21];
    std::vector< std::vector<int> > running_tally(21);

    while ((num_test--) > 0) {
    	voting_read(r, num_cand, num_ballots, ballots, names, running_tally);   
    	int winner = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);

    	printf("%d\n", winner );
    }
	
}

