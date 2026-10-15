#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <limits>
using namespace std;

int bestScore = -1;

int GetIntegerInput()
{
    int number;

    while (!(cin >> number))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number: ";
    }

    return number;
}

void LoadBestScore()
{
    ifstream file("bestscore.txt");

    if (file >> bestScore)
        return;

    bestScore = -1;
}

void SaveBestScore()
{
    ofstream file("bestscore.txt");
    file << bestScore;
    file.close();
}

void ChooseDifficulty(int& maximumNumber, int& maximumAttempts)
{
    int choice;

    do
    {
        cout << "\n=== Choose Difficulty ===\n";
        cout << "1. Easy (1-50, 10 attempts)\n";
        cout << "2. Medium (1-100, 7 attempts)\n";
        cout << "3. Hard (1-200, 5 attempts)\n";
        cout << "Enter your choice: ";

        choice = GetIntegerInput();

        if (choice == 1)
        {
            maximumNumber = 50;
            maximumAttempts = 10;
        }
        else if (choice == 2)
        {
            maximumNumber = 100;
            maximumAttempts = 7;
        }
        else if (choice == 3)
        {
            maximumNumber = 200;
            maximumAttempts = 5;
        }
        else
        {
            cout << "Invalid difficulty. Try again.\n";
        }

    } while (choice < 1 || choice > 3);
}

int GenerateRandomNumber(int maximumNumber)
{
    return rand() % maximumNumber + 1;
}

bool CheckGuess(int guess, int secretNumber)
{
    if (guess == secretNumber)
    {
        cout << "Correct! You guessed the number.\n";
        return true;
    }

    if (guess < secretNumber)
        cout << "Too low!\n";
    else
        cout << "Too high!\n";

    return false;
}

void UpdateBestScore(int attempts)
{
    if (bestScore == -1 || attempts < bestScore)
    {
        bestScore = attempts;
        SaveBestScore();

        cout << "Congratulations! New best score.\n";
    }
}

void DisplayBestScore()
{
    if (bestScore != -1)
        cout << "Best score: " << bestScore << " attempts\n";
    else
        cout << "No best score yet.\n";
}

void PlayRound()
{
    int maximumNumber;
    int maximumAttempts;

    ChooseDifficulty(maximumNumber, maximumAttempts);

    int secretNumber = GenerateRandomNumber(maximumNumber);
    int attempts = 0;
    bool guessedCorrectly = false;

    cout << "\nGuess a number between 1 and "
        << maximumNumber << ".\n";

    while (attempts < maximumAttempts)
    {
        cout << "Attempt " << attempts + 1
            << "/" << maximumAttempts << ": ";

        int guess = GetIntegerInput();

        if (guess < 1 || guess > maximumNumber)
        {
            cout << "Enter a number within the allowed range.\n";
            continue;
        }

        attempts++;

        if (CheckGuess(guess, secretNumber))
        {
            guessedCorrectly = true;
            break;
        }
    }

    if (guessedCorrectly)
    {
        cout << "Attempts used: " << attempts << endl;
        UpdateBestScore(attempts);
    }
    else
    {
        cout << "You lost! The number was "
            << secretNumber << ".\n";
    }

    DisplayBestScore();
}

bool PlayAgain()
{
    char answer;

    cout << "\nPlay again? (y/n): ";
    cin >> answer;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return tolower(answer) == 'y';
}

void RunGame()
{
    do
    {
        PlayRound();

    } while (PlayAgain());

    cout << "Thanks for playing!\n";
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    LoadBestScore();

    RunGame();

    return 0;
}