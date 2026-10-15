
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

int playerScore = 0;
int computerScore = 0;

enum Choice
{
    PAPER = 1,
    ROCK = 2,
    SCISSORS = 3
};

void SetColor(int color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE), color
    );
}

string GetChoiceName(int choice)
{
    switch (choice)
    {
    case PAPER:
        return "Paper";
    case ROCK:
        return "Rock";
    case SCISSORS:
        return "Scissors";
    default:
        return "Invalid";
    }
}

int GetPlayerChoice()
{
    int choice;

    cout << "\nChoose your choice:\n";
    cout << "1 - Paper\n";
    cout << "2 - Rock\n";
    cout << "3 - Scissors\n";
    cout << "Enter your choice: ";

    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        return 0;
    }

    return choice;
}

int GetComputerChoice()
{
    return rand() % 3 + 1;
}

void DisplayScore()
{
    cout << "\n========== SCORE ==========\n";

    SetColor(10);
    cout << "Your score: " << playerScore << '\n';

    SetColor(12);
    cout << "Computer score: " << computerScore << '\n';

    SetColor(7);
    cout << "===========================\n";
}

void DetermineWinner(int player, int computer)
{
    cout << "\nYour choice: " << GetChoiceName(player) << '\n';
    cout << "Computer choice: " << GetChoiceName(computer) << '\n';

    if (player == computer)
    {
        SetColor(14);
        cout << "\nIt's a DRAW!\n";
    }
    else if (
        (player == PAPER && computer == ROCK) ||
        (player == ROCK && computer == SCISSORS) ||
        (player == SCISSORS && computer == PAPER))
    {
        SetColor(10);
        cout << "\nYOU WIN THIS ROUND!\n";
        playerScore++;
    }
    else
    {
        SetColor(12);
        cout << "\nCOMPUTER WINS THIS ROUND!\n";
        computerScore++;
    }

    SetColor(7);
}

bool PlayAgain()
{
    char answer;

    cout << "\nDo you want to continue? (y/n): ";
    cin >> answer;

    return tolower(answer) == 'y';
}

void DisplayFinalResult()
{
    cout << "\n\n========== FINAL RESULT ==========\n";

    DisplayScore();

    if (playerScore > computerScore)
    {
        SetColor(10);
        cout << "\nCONGRATULATIONS! YOU WON THE GAME!\n";
    }
    else if (computerScore > playerScore)
    {
        SetColor(12);
        cout << "\nCOMPUTER WON THE GAME!\n";
    }
    else
    {
        SetColor(14);
        cout << "\nTHE GAME ENDED IN A DRAW!\n";
    }

    SetColor(7);
    cout << "==================================\n";
}

void PlayGame()
{
    do
    {
        int playerChoice = GetPlayerChoice();

        if (playerChoice < 1 || playerChoice > 3)
        {
            SetColor(12);
            cout << "\nInvalid choice! Enter 1, 2, or 3.\n";
            SetColor(7);

            if (!PlayAgain())
                break;

            continue;
        }

        int computerChoice = GetComputerChoice();

        DetermineWinner(playerChoice, computerChoice);
        DisplayScore();

    } while (PlayAgain());

    DisplayFinalResult();
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    PlayGame();

    return 0;
}