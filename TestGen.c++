#include <cassert> // assert
#include <iostream> // endl, istream, ostream
#include <vector>
#include <algorithm>
#include <string.h>
#include <cstdlib>
#include <string>

int main()
{
	using namespace std;
	int num_cases;
	cin >> num_cases;
	cout << num_cases << "\n" << endl;
	string names[21] = {"NULL", "Gisela Newlin", "Sanjuana Plumley",
    "Suzi Carreira",
    "Takisha Macleod",
    "Cassaundra Melrose",
    "Renata Kinslow",
    "Moriah Ikeda",
    "Marquitta Balke",
    "Arden Crege",
    "Malena Ordonez",
    "Serina Ohanlon",
    "Lillie Kiernan",
    "Ha Hymes",
    "Amelia Storch",
    "Adelia Klahn",
    "Elia Loe",
    "Demarcus Nightingal",
    "Mollie Tiner",
    "Hyun Desmond",
    "Letisha Rideout"};  

	int rand_cand;
	int rand_names;
	int rand_ball;
	int rand_vote;
	int printed[21] = {0};
	int N = 20;
	int M = 1;
	int N2;

	while(num_cases-- > 0 )
	{

		for (int temp = 0; temp < 21; ++temp)
		{
			printed[temp] = 0;
		}
		
		rand_cand = M + rand() / (RAND_MAX / (N - M + 1) + 1);
		cout << rand_cand << endl;
		for (int i = 0; i < rand_cand; ++i)
		{
			rand_names = M + rand() / (RAND_MAX / (N - M + 1) + 1);
			if(printed[rand_names] == 1)
				--i;
			else
			{
				printed[rand_names] = 1;
				cout << names[rand_names] << endl;			
			}
		}

		for (int temp = 0; temp < 21; ++temp)
		{
			printed[temp] = 0;
		}

		rand_ball = rand() % 200 + 1;
		N2 = rand_cand;

		for (int i = 0; i < rand_ball; ++i)
		{
			for (int temp = 0; temp < 21; ++temp)
			{
				printed[temp] = 0;
			}

			for (int j = 0; j <= rand_cand-1; ++j)
			{
				rand_vote = M + rand() / (RAND_MAX / (N2 - M + 1) + 1);
				if(printed[rand_vote] == 1)
					--j;
				else
				{
					printed[rand_vote] = 1;
					cout << rand_vote << " ";
				}
			}
			for (int k = 1; k < rand_cand; ++k)
			{
				if (!printed[k])
					cout << k;
			}
			cout << endl;
		}

		cout << endl;

	}

}