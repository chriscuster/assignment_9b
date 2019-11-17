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
//void getPlayerRolls(int[], int&)
//{
//
//}



//function to store bowling data from file
bool readPlayerRolls(int[], int&, string filename);

int main()
{
	string a = "Hello, world!!!!!";
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




			//open file for input using the bool function
			cout << "Enter file name: ";
			cin >> filename;

			while (readPlayerRolls(userRolls, ttlRolls, filename) == false)
			{
				std::cout << "Could not open " << filename << ", reenter file name: " << endl;
				cin >> filename;
			}
			generateScoreText(userRolls, ttlRolls, score);
			cout << score;



			break;
		case 'i':
		case 'I':
			cout << "input roll values" << endl;
			cin >> testData;
			pos = 0;
			while ((pos = testData.find(" ")) != string::npos)
			{
				userRolls[ttlRolls] = stoi(testData.substr(0, pos));
				testData.erase(0, pos + 1);
				ttlRolls++;
			}
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

bool readPlayerRolls(int userRolls[], int& ttlRolls, string filename)
{
	ifstream fin;
	fin.open(filename.c_str());

	if (!fin.is_open())
	{
		return false;
	}


	string scores = "";
	while (!fin.eof())
	{
		fin >> scores;
		userRolls[ttlRolls] = stoi(scores);
		ttlRolls++;
	}
	return true;
	fin.close();
}

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


