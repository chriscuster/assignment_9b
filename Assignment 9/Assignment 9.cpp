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

	string filename = "";
	string testData = "";
	fstream fin;


	//loop to ensure user data is good
	do
	{
		int userRolls[21] = {};
		//bowling menu
		cout << "[R]ead roll data from a file" << endl;
		cout << "[I]nput roll data manually" << endl;
		cout << "[Q]uit Program" << endl;
		cout << "Enter selection: ";
		cin >> menuOption;

		int ttlRolls = 0;

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
	fin.close();
	return true;
}


void generateScoreText(int arr[], int ttlRolls, string& score)
{
	// make ttlRolls 0 based to match array
	ttlRolls--;
	int roll = 0;
	bool isFirstRoll = true;
	int ttlScore = 0;
	// for 10 frames 1-10
	int frames[11] = { };
	int frameIdx = 1;
	bool isGameFinished = false;

	score = "Frame #1 \r\n-Roll 1: ";

	while (roll <= ttlRolls && !isGameFinished)
	{
		// if last roll
		//if (roll == ttlRolls)
		//{
		//	frames[frameIdx] += arr[roll];
		//}
		// if first roll
		if (isFirstRoll)
		{
			frames[frameIdx] += arr[roll];

			// if strike
			if (arr[roll] == 10)
			{
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
							rollValue = to_string(arr[roll + 2]);
						score += "\r\n-Roll 3: " + rollValue;

						isGameFinished = true;
					}
					frames[frameIdx] += arr[roll + 1] + arr[roll + 2];

				}
				// if only one roll left (non complete game)
				else if (roll + 1 <= ttlRolls)
				{
					frames[frameIdx] += arr[roll + 1];
					if (frameIdx == 10)
					{
						score += "\r\n-Roll 2: " + to_string(arr[roll + 1]);
						roll++;
					}

				}


				ttlScore += frames[frameIdx];
				if (frameIdx < 10)
				{
					score += "\r\n-Score: " + to_string(ttlScore);
					frameIdx++;
					if (roll < ttlRolls)
					{
						score += "\r\n\r\nFrame #" + to_string(frameIdx) + "\r\n-Roll 1: ";
					}
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
				if (roll + 1 <= ttlRolls)
					frames[frameIdx] += arr[roll + 1];

				if (frameIdx == 10 && roll + 1 == ttlRolls)
				{
					string roll3val = arr[roll + 1] == 10 ? "strike" : to_string(arr[roll + 1]);
					score += "\r\n-Roll 3: " + roll3val;
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
		score += "\r\n\r\nTotal Score: " + to_string(ttlScore) + "\r\n\r\n";
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

void getPlayerRolls(int userRolls[], int& ttlRolls)
{

	int roll = 1;
	// for 10 frames 1-10
	int	frameIdx = 1;
	bool isStrikeIn10 = false;
	int value1 = 0;
	int value2 = 0;
	int currentValue = 0;
	int value3 = 0;
	int checkTtlVal = 10;
	do
	{
		//error checking for good player data
		do
		{
			if (roll == 1)
			{
				value1 = 0;
				value2 = 0;
				value3 = 0;
				currentValue = 0;
				cout << "Frame " << frameIdx << endl << "-roll " << roll << ": ";
				cin >> value1;
				if (value1 > 10 || value1 < -1)
				{
					cout << "Error Inalid input." << endl;
				}
				if (value1 == -1)
				{
					break;
				}
				currentValue = value1;
			}
			else if (roll == 2)
			{
				value2 = 0;
				value3 = 0;
				if (frameIdx <= 10)
				{
					cout << "-roll " << roll << ": ";
					cin >> value2;
				}

				checkTtlVal = isStrikeIn10 ? 20 : 10;
				if (value2 == -1)
				{
					break;
				}
				else if (value2 + value1 > checkTtlVal || value2 < -1)
				{
					cout << "Error Inalid input." << endl;

				}
				else
				{
					currentValue = value2;
				}
			}
			else
			{
				value3 = 0;
				cout << "-roll " << roll << ": ";
				cin >> value3;

				checkTtlVal = isStrikeIn10 && value2 == 10 ? 30 : 20;

				if (value3 == -1)
				{
					break;
				}

				if (value3 > 10 || value3 < -1
					|| (value1 == 10 && value2 < 10 && value3 + value2>10))
				{
					cout << "Error Inalid input." << endl;
				}

				currentValue = value3;
			}

		} while (value1 + value2 + value3 > checkTtlVal || currentValue < -1 || currentValue>10);

		if (value1 == -1 || value2 == -1 || value3 == -1)
		{
			break;
		}

		userRolls[ttlRolls] = currentValue;
		// if first roll, 
		if (roll == 1 && frameIdx < 11)
		{
			if (currentValue == 10 && frameIdx < 10) {
				frameIdx++;
			}
			else if (currentValue == 10 && frameIdx == 10)
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
			if (roll < 3 && ((frameIdx == 10 && roll == 2 && userRolls[ttlRolls] + userRolls[ttlRolls - 1] == 10)
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
	} while (frameIdx < 11);

}