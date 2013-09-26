// ----------------------------
// /cs371p-voting/UVaVoting.c++
// Copyright (C) 2013
// CS371p Fall 2013
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
#include <string.h>

#define DB 0
#define DB2 0

// ------------
// voting_read
// ------------

void voting_read (std::istream& r, int& num_cand, int& num_ballots , int ballots[][20], char names[][81], std::vector< std::vector<int> >& running_tally) {
	int row = 0;
    int col;
 	char line[256];
 	char check;
 	bool good_state = true;
 	char *tok, *saved;

 	//gets candidate number
    r >> num_cand;
    if(DB2) std::cout << "Number of candidates " << num_cand << std::endl;

    // eats the new line after the num_cand
    r.getline(line, 256);

    //read all the candidate names
    for (int i = 1; i <= num_cand; ++i)
    {
    	r.getline(names[i], 81);
    	if(DB2) std::cout << names[i] << std::endl;
    }


    //read all the ballots
    while(good_state)
    {
    	r.getline(line, 256);

    	//reads each ballot line and save to correct array
		col = 0;
		for (tok = strtok_r(line, " ", &saved); tok ; tok = strtok_r(NULL, " ", &saved))
		{
		    ballots[row][col] = atoi(tok);
		    if(DB2) std::cout << ballots[row][col] << " ";
		    ++col;
		}

		if(DB2) std::cout << std::endl;

		//increment ballot count
    	running_tally[ballots[row][0]].push_back(row);
    	++row;
    	assert(row <= 1000);

    	//checks if reached EOF or a blank line
    	r.get(check);
    	if(r.eof() || check == '\n')
    		break;
    	else
    		r.unget();						// valid input, putting back in istream
    }

	num_ballots = row;
    assert(num_cand > 0);
}


int voting_eval (int num_cand, int num_ballots, int ballots[][20], std::vector< std::vector<int> >& running_tally, int tally[21]) 
{
	std::vector<int> losers;

	//counts first-place votes
	for (int i = 1; i <= num_cand; ++i){
		if (running_tally[i].size() == 0)
		{
			tally[i] = -1;
		}
		else
		tally[i] = running_tally[i].size();
	}

	int min_tally;
	int max_tally;
	
    // Loop through until winner is found
	while(1)
	{
		min_tally = num_ballots;
		max_tally = 0;		
		
		if(DB) std::cout << std::endl;

		//find max and min number of votes
		for (int i = 1; i <= num_cand; ++i)
		{
			if(DB) std::cout << "tally at " << i << " is " << tally[i] << std::endl;
			if(tally[i] > num_ballots / 2)
				return tally[i];
			else
			{
				max_tally = std::max(tally[i], max_tally);
				if (tally[i] > 0)
					min_tally = std::min(tally[i], min_tally);
			}
		}

	    if(DB) std::cout << std::endl;

		//check if all tie
		if (max_tally == min_tally)
			return max_tally;

		//no clear winner, vote re-distribution
		//first loop adds loser to a list
		losers.clear();
		for (int i = 1; i <= num_cand; ++i)
		{
		   	if(DB)  std::cout << "min_tally #: " << min_tally << std::endl;

			if(tally[i] == min_tally)
			{
				losers.push_back(i);
				tally[i] = -1;
				if(DB) std::cout << "losers # " << i << std::endl;
			}
		}

		//second loop re-distributes vote
		for (unsigned int i = 0; i < losers.size(); ++i)
		{
			if(DB) std::cout << "currently in loser #: " << losers[i] << std::endl;
			if(DB) std::cout << "loser's vector size: " << running_tally[ losers[i] ].size() << std::endl;
			//loops through losers' ballots
			for (int j = running_tally[ losers[i] ].size() - 1; j >= 0; --j)
			{
				if(DB) std::cout << "loser #: " << losers[i] << " at ballot pos: " << running_tally[ losers[i] ][j] << std::endl;
				//loops through new candidates to check if new candidate is also a looser
				for (int k = 1; k < num_cand; ++k)
				{
					if(DB) std::cout << "currently looking at candidate # " << k << " in ballot" << std::endl;
					bool found = true;
					//check if new vote is in losers list
					for (unsigned int l = 0; l < losers.size(); ++l)
					{
						if(DB) std::cout << "new winner in ballot is " << ballots[ running_tally[ losers[i] ][j] ][k] << " and loser list have cand: " << losers[l] << std::endl;
						if (ballots[ running_tally[ losers[i] ][j] ][k] == losers[l] || tally[ ballots[ running_tally[ losers[i] ][j] ][k] ] == -1)
						{
							found = false;
							break;
						}
					}
					if (found)
					{
						if(DB) std::cout << "Loser cand #: " << losers[i] << std::endl;
						if(DB) std::cout << "New cand winner #: " << ballots[ running_tally[ losers[i] ][j] ][k] << " ballot #: " << running_tally[ losers[i] ][j] << std::endl;
						running_tally[ ballots[ running_tally[ losers[i] ][j] ][k] ].push_back( running_tally[ losers[i] ][j] );
						running_tally[ losers[i] ].pop_back();
						++tally[ ballots[ running_tally[ losers[i] ][j] ][k] ];
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

void voting_print (std::ostream& w, int& num_cand, char names[][81] , int* tally, int& winning_tally) 
{
	bool isFirst = true;
    for (int i = 1; i <= num_cand; ++i)
    {
        if (tally[i] == winning_tally)
        {
        	//print format for first case
        	if (isFirst)
        	{
        		w << names[i];
        		isFirst = false;
        	}
        	else		//print format for every case after that
        		w << std::endl << names[i];
        }
    }
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

    bool isFirstCase = true;
    while ((num_test--) > 0)
    {
    	if (!isFirstCase)
    	{
    		//clear vector
    		std::vector< std::vector<int> > new_tally(21);
    		running_tally.swap(new_tally);
    		new_tally.clear();
			w << "\n" << std::endl;
    	}

    	//loops through calling main functions
    	voting_read(r, num_cand, num_ballots, ballots, names, running_tally);   
    	int winning_tally = voting_eval(num_cand, num_ballots, ballots, running_tally, tally);
    	voting_print(w, num_cand, names, tally, winning_tally);

    	isFirstCase = false;
    }

    // prints last newline
    w << std::endl;
}


int main()
{
    using namespace std;
    voting_solve(cin, cout);
    return 0;
}
