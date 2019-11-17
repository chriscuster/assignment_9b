/*
Christopher Custer
Assignment 9
Program Description: Utilize functions with arrays to create a bowling game calculator


*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;


//function to generate the score of the game
void generateScoreText(int[], int, string&);



//function to read in user input for bowling data
void getPlayerRolls(int[], int&);
//function to store bowling data from file
bool readPlayerRolls(int[], int&, string filename);

int main()
{
	string score = "";
	char menuOption = ' ';
	//bowling menu
	cout << "[R]ead roll data from a file" << endl;
	cout << "[I]nput roll data manually" << endl;
	cout << "[Q]uit Program" << endl;

	int userRolls[21] = {};
	int ttlRolls = 0;
	string filename = "";
	string testData = "";
	fstream fin;
	int pos = 0;
	//loop to ensure user data is good
	while (true)
	{
		cout << "Enter selection: ";
		cin >> menuOption;

		switch (menuOption)
		{
		case 'R':
		case 'r':
			//open file for input using the bool function.
			cout << "Enter file name: ";
			cin >> filename;

			while (readPlayerRolls(userRolls, ttlRolls, filename) == false)
			{
				cout << "Could not open " << filename << ", reenter file name: " << endl;
				cin >> filename;
			}
			generateScoreText(userRolls, ttlRolls, score);
			cout << score;
			break;
		case 'i':
		case 'I':
			getPlayerRolls(userRolls, ttlRolls);
			generateScoreText(userRolls, ttlRolls, score);
			cout << score;

			break;
		case 'q':
		case 'Q':
			cout << "quitting..." << endl;
			break;
		default:
			cout << "Incorrect input please select option from bracketed characters []." << endl;
			continue;
		}
		break;
	}



}

//TODO: ensure that frame 10 works with same logic as inputplayer
bool readPlayerRolls(int userRolls[], int& ttlRolls, string filename)
{
	ifstream fin;
	fin.open(filename.c_str());

	if (!fin.is_open())
	{
		return false;
	}


	string score = "";
	fin >> score;
	do
	{
		userRolls[ttlRolls] = stoi(score);
		ttlRolls++;
		fin >> score;
	} while (!fin.eof());
	return true;
	fin.close();
}


//TODO: check 10s through 9, then 5, 5, 5
void generateScoreText(int arr[], int ttlRolls, string& score)
{
	bool isFirstRoll = true;
	int strikeRollNumber = 0;
	int ttlScore = 0;
	int frameScore = 0;
	// for 10 frames 1-10
	int frames[11] = { };
	int frameIdx = 1;
	bool isSpare = false;
	bool isGameFinished = false;

	for (int roll = 0; roll < ttlRolls; roll++)
	{
		if (frameIdx == 10 && arr[roll] == 10)
		{
			frames[frameIdx] += arr[roll] + arr[roll + 1] + arr[roll + 2];
			break;
		}

		// if last roll
		if (roll == ttlRolls)
		{
			frames[frameIdx] += arr[roll];
		}
		// if first roll
		else if (isFirstRoll)
		{

			frames[frameIdx] += arr[roll];

			// if strike
			if (arr[roll] == 10)
			{
				// account for next two rolls
				if (roll + 2 <= ttlRolls)
				{
					frames[frameIdx] += arr[roll + 1] + arr[roll + 2];
				}
				else if (roll + 1 == ttlRolls)
				{
					frames[frameIdx] += arr[roll + 1];
				}

				frameIdx++;
			}
			else
			{
				isFirstRoll = false;
			}

			// check for spare
			if (isSpare)
			{
				frames[frameIdx - 1] += arr[roll];
				isSpare = false;
			}
		}
		else // not first roll
		{
			// add prev with this
			frames[frameIdx] += arr[roll];
			// check for spare
			if (frames[frameIdx] == 10)
			{
				isSpare = true;
			}
			if (frameIdx < 10)
			{
				frameIdx++;
				isFirstRoll = true;
			}
		}
	}

	//adding frame total
	for (int i = 1; i <= frameIdx; i++)
	{
		ttlScore += frames[i];
	}
	score = to_string(ttlScore);
}

void getPlayerRolls(int scores[], int& ttlRolls)
{
	int roll = 1;
	int strikeRollNumber = 0;
	int ttlScore = 0;
	int frameScore = 0;
	// for 10 frames 1-10
	int	frameIdx = 1;
	bool isSpare = false;
	bool isGameFinished = false;
	bool isStrikeIn10 = false;

	int value = 0;
	do
	{
		cout << "Frame " << frameIdx << endl << "-roll " << roll << ": ";

		cin >> value;
		scores[ttlRolls] = value;
		// if first roll, 
		if (roll == 1 && frameIdx < 11)
		{
			if (value == 10 && frameIdx < 10) {
				frameIdx++;
			}
			else if (value == 10 && frameIdx == 10)
			{
				isStrikeIn10 = true;
				roll = 2;
			}
			else
			{
				roll = 2;
			}
		}
		else // roll 2, or in 10th the third roll
		{
			// check for spare if second roll, gain 1 extra roll
			// or if strike need to have two extra rolls
			if (roll < 3 && ((frameIdx == 10 && roll == 2 && scores[ttlRolls] + scores[ttlRolls - 1] == 10)
				|| isStrikeIn10))
			{
				roll = 3;
			}

			else
			{
				frameIdx++;
				roll = 1;
			}
		}
		ttlRolls++;
	} while (value >= 0 && frameIdx < 11);

}