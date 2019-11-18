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
	int userRolls[21] = {};
	int ttlRolls = 0;
	string filename = "";
	string testData = "";
	fstream fin;
	int pos = 0;

	
		

		//loop to ensure user data is good
		do
		{
			//bowling menu
			cout << "[R]ead roll data from a file" << endl;
			cout << "[I]nput roll data manually" << endl;
			cout << "[Q]uit Program" << endl;
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
				continue;
			case 'i':
			case 'I':
				getPlayerRolls(userRolls, ttlRolls);
				generateScoreText(userRolls, ttlRolls, score);
				cout << score;

				continue;
			case 'q':
			case 'Q':
				cout << "quitting..." << endl;
				break;
			default:
				cout << "Incorrect input please select option from bracketed characters []." << endl;
				continue;
			}
			break;
		} while (true);
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
	int currentTtlScore = 0;
	// for 10 frames 1-10
	int frames[11] = { };
	int frameIdx = 1;
	bool isSpare = false;
	bool isGameFinished = false;
	bool isStrike = false;

	score = "Frame #1 \r\n-Roll 1: ";
	int roll = 0;
	while (roll < ttlRolls && !isGameFinished)
	{
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
				isStrike = true;
				score += "strike";
				// account for next two rolls
				if (roll + 2 <= ttlRolls)
				{
					if (frameIdx == 10)
					{
						string rollValue = "strike";
						if (arr[roll + 1] < 10)
							rollValue = to_string(arr[roll + 1]);

						score += "\r\n-Roll 2: " + rollValue;

						rollValue = "strike";
						if (arr[roll + 2] < 10)
							rollValue = to_string(arr[roll + 1]);
						score += "\r\n-Roll 3: " + rollValue;

						isGameFinished = true;
					}
					frames[frameIdx] += arr[roll + 1] + arr[roll + 2];

				}
				else if (roll + 1 == ttlRolls)
				{
					if (frameIdx == 10)
					{
						score += "\r\n-Roll 2: " + to_string(arr[roll + 1]);
					}
					frames[frameIdx] += arr[roll + 1];
				}


				ttlScore += frames[frameIdx];
				if (frameIdx < 10)
				{
					score += "\r\n-Score: " + to_string(ttlScore);
					frameIdx++;
					score += "\r\n\r\nFrame #" + to_string(frameIdx) + "\r\n-Roll 1: ";
				}
				else
				{
					score += "\r\n-Score: " + to_string(ttlScore);
				}

			}
			else
			{
				isFirstRoll = false;
				score += to_string(arr[roll]);
			}
		}
		else // not first roll
		{
			score += "\r\n-Roll 2: ";
			// add prev with this
			frames[frameIdx] += arr[roll];
			// check for spare
			if (frames[frameIdx] == 10)
			{
				score += "spare";
				if (roll + 1 < ttlRolls)
					frames[frameIdx] += arr[roll + 1];
				isSpare = true;
				if (frameIdx == 10 && roll + 2 == ttlRolls)
				{
					score += "\r\n-Roll 3: " + to_string(arr[roll + 1]);
					isGameFinished = true;
				}
			}
			else
			{
				score += to_string(arr[roll]);
				if (frameIdx == 10)
				{
					isGameFinished = true;
				}
			}

			ttlScore += frames[frameIdx];
			if (frameIdx < 10)
			{
				score += "\r\n-Score: " + to_string(ttlScore);
				frameIdx++;
				isFirstRoll = true;

				score += "\r\n\r\nFrame #" + to_string(frameIdx) + "\r\n-Roll 1: ";
			}
			else
			{
				score += "\r\n-Score: " + to_string(ttlScore);
			}

		}
		roll++;
	}


	if (isGameFinished)
	{
		score += "\r\n\r\nTotal Score: " + to_string(ttlScore);
	}
	else
	{
		score += "\r\n\r\n-Game in Progress-\r\n\r\n";
	}

	ofstream fout;
	string filename = "";
	char answer = ' ';
	do
	{
		cout << "Would you like to save game to a file? [y/n] ";
		cin >> answer;

		if (answer == 'y')
		{
			cout << "Enter filename to save bowling game: ";
			cin >> filename;
			cout << endl;
			fout.open(filename.c_str());
			fout << score;
		}
		fout.close();
	} while (answer != 'y' && answer != 'n');

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