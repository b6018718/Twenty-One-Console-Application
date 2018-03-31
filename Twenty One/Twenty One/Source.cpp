#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#define GOAL 21

using namespace std;

int main(int argc, char* args[])
{
	void BeginGame();
	BeginGame();
	return 0;
}

void BeginGame()
{
	int ChooseStart();
	void NextRound(int& currentTurn, int& currentScore);
	int currentTurn = ChooseStart();
	int currentScore = 0;
	NextRound(currentTurn, currentScore);
	system("pause");
}

int ChooseStart()
{
	int turnOrder;
	cout << "Do you want to play 1st or 2nd?\n" << "(ENTER 1 OR 2)\n";

	while (!(cin >> turnOrder) || (turnOrder != 1 && turnOrder != 2))
	{
		cout << "Error, must enter either 1 or 2. \n";
		cin.clear();
		cin.ignore(10000,'\n');
	}

	system("CLS");
	return turnOrder;
}

void NextRound(int& currentTurn, int& currentScore)
{
	bool playersTurn = true;		//True = Player, False = CPU
	if (currentTurn % 2 == 0)		//Even currentTurn = CPU's turn, odd currentTurn = player's turn
		playersTurn = false;

	void DisplayOptions(vector <int> options);
	void GenerateOptions(vector <int>& vector, int currentScore);
	vector <int> options;
	GenerateOptions(options, currentScore);

	if (playersTurn == true)	//PLAYER
	{
		int choice;
		cout << "It's your turn! The current number is " << currentScore << "\nYou can either choose \n";
		DisplayOptions(options);
		while (!(cin >> choice) || (find(options.begin(), options.end(), choice) == options.end()))	//Check if the choice is a valid option
		{
			cout << "Error, you can only enter ";
			DisplayOptions(options);
			cin.clear();
			cin.ignore(10000, '\n');
		}
		currentScore = choice;
		if (currentScore == GOAL)   //Lose State
		{
			char playAgain;
			cout << "\nYou have reached " << GOAL << ". The CPU has beaten you, try again?\n(ENTER Y OR N)\n";
			while (!(cin >> playAgain) || (toupper(playAgain) != 'Y' && toupper(playAgain) != 'N'))
			{
				cout << "Error, must enter either Y or N. \n";
				cin.clear();
				cin.ignore(10000, '\n');
			}

			if (toupper(playAgain) == 'Y')	//Start game over
			{
				system("CLS");
				BeginGame();
			}
		}
		else
		{
			currentTurn++;			//Next turn
			system("CLS");
			NextRound(currentTurn, currentScore);
		}
	}
	else              //CPU
	{
		int evaluateOptionAI(int currentPosition, int option);
		int bestScore = -1;
		int bestOption;
		int score;

		for (size_t i = 0; i < options.size(); i++)
		{
			score = evaluateOptionAI(currentScore, options[i]);
			if (score > bestScore)
			{
				bestScore = score;
				bestOption = options[i];
			}
		}
		
		cout << "It's the CPU's turn! The current number is " << currentScore << "\nIt can either choose \n";
		DisplayOptions(options);
		cout << "\nIt chose " << bestOption << "!\n\n";
		currentScore = bestOption;
		if (currentScore == GOAL)   //Lose State
		{
			char playAgain;
			cout << "\nThe CPU has reached " << GOAL << ". You have beaten the CPU, play again?\n(ENTER Y OR N)\n";
			while (!(cin >> playAgain) || (toupper(playAgain) != 'Y' && toupper(playAgain) != 'N'))
			{
				cout << "Error, must enter either Y or N. \n";
				cin.clear();
				cin.ignore(10000, '\n');
			}

			if (toupper(playAgain) == 'Y')	//Start game over
			{
				system("CLS");
				BeginGame();
			}
		}
		else
		{
			currentTurn++;			//Next turn
			system("pause");
			system("CLS");
			NextRound(currentTurn, currentScore);
		}
	}
}

int evaluateOptionAI(int currentPosition, int option)
{
	int optionViabilityScore = 0;
	//To win at 21 the CPU must make up whatever you input to the nearest multiple of 4, unless it reaches the end
	if (currentPosition - option == 1)
		optionViabilityScore += 1;				//Weight = 1/6
	if (option % 4 == 0)
		optionViabilityScore += 2;				//Weight = 2/6
	if (option + 1 == GOAL)
		optionViabilityScore += 3;				//Weight = 3/6
	return optionViabilityScore;
}

void GenerateOptions(vector <int>& options, int currentScore)
{
	options.clear();
	int i = 0;
	while (i < 3 && i + currentScore != GOAL)
	{
		i++;
		options.push_back(i + currentScore);
	}

}

void DisplayOptions(vector <int> options)
{
	for (unsigned int i = 0; i < options.size(); i++)
	{
		cout << options[i];
		if (i != options.size() - 1)
			cout << ", ";
	}
	cout << "\n";
}