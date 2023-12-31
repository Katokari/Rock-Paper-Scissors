#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

enum enPlayerType { Player1 = 1, Computer = 2 };
enum enChoices { Stone = 1, Paper = 2, Scissors = 3 };
enum enGameWinner { WPlayer1 = 3, WComputer = 4, WDraw = 5 };

struct stGameResults
{
    short TotalRounds = 0;
    short PlayerWonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    enGameWinner GamerResults;
};

struct stRoundStatus
{
    short CurrentRound = 0;
    enGameWinner GameResults;
    enChoices Player1Choice;
    enChoices ComputerChoice;
};

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum; 
}

enChoices GetChoice(enPlayerType PlayerType)
{
    short Choice;
    if (PlayerType == enPlayerType::Player1)
    {  
        do
        {
            cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
            cin >> Choice;
        } while (Choice < 1 || Choice > 3);
        return (enChoices) Choice;
    }
    else
    {
        Choice = RandomNumber(1, 3);
        return (enChoices) Choice;
    }
}

enGameWinner CheckWinner(enChoices Player1Choice ,enChoices ComputerChoice)
{
    if (Player1Choice == enChoices::Stone)
    {
        switch (ComputerChoice)
        {
            case enChoices::Scissors:
                return enGameWinner::WPlayer1;
            case enChoices::Paper:
                return enGameWinner::WComputer;
        }
    }
    else if (Player1Choice == enChoices::Paper)
    {
        switch (ComputerChoice)
        {
            case enChoices::Stone:
                return enGameWinner::WPlayer1;
            case enChoices::Scissors:
                return enGameWinner::WComputer;
        }
    }
    else if (Player1Choice == enChoices::Scissors)
    {
        switch (ComputerChoice)
        {
            case enChoices::Paper:
                return enGameWinner::WPlayer1;
            case enChoices::Stone:
                return enGameWinner::WComputer;
        }
    }   
    
    return enGameWinner::WDraw; 
}

string ChoicesToString(enChoices Choice)
{
    switch(Choice)
    {
        case enChoices::Stone:
            return "Stone";
        case enChoices::Paper:
            return "Paper";
        case enChoices::Scissors:
            return "Scissors";
    }
}  

string GamerWinnerToString(enGameWinner Winner)
{
    switch(Winner)
    {
        case enGameWinner::WPlayer1:
            return "Player1";
        case enGameWinner::WComputer:
            return "Computer";
        case enGameWinner::WDraw:
            return "Draw";
    }
}  

void ChangeScreen(enGameWinner GameWinner)
{
    if (GameWinner == enGameWinner::WPlayer1)
        system("color 2");
    else if (GameWinner == enGameWinner::WComputer)
        system("color 4");
    else if (GameWinner == enGameWinner::WDraw)
        system("color 6");
}

void RoundSummary(stRoundStatus RoundStatus)
{
    ChangeScreen(RoundStatus.GameResults);
    cout << "\n____________Round[" << RoundStatus.CurrentRound << "] ____________";
    cout << "\n\nPlayer1  Choice: " << ChoicesToString(RoundStatus.Player1Choice);
    cout << "\nComputer Choice: " << ChoicesToString(RoundStatus.ComputerChoice);
    cout << "\nRound Winner   : [" << GamerWinnerToString(RoundStatus.GameResults) << "]";
    cout << "\n_________________________________" << endl;
}

stRoundStatus StartRound(short CurrentRound)
{   
    stRoundStatus RoundStatus;

    cout << "\n\nRound [" << CurrentRound << "] begins:\n";

    RoundStatus.Player1Choice = GetChoice(enPlayerType::Player1);
    RoundStatus.ComputerChoice = GetChoice(enPlayerType::Computer);
    RoundStatus.GameResults = CheckWinner(RoundStatus.Player1Choice, RoundStatus.ComputerChoice);
    RoundStatus.CurrentRound = CurrentRound;

    RoundSummary(RoundStatus);
    return RoundStatus;
}

short ReadHomManyRounds()
{
    short Rounds;
    do
    {
        cout << "How Many Rounds 1 to 10 ?\n";
        cin >> Rounds;
    } while (Rounds < 1 || Rounds > 10);
    return Rounds;
}

enGameWinner GetWinner(stGameResults GameResults)
{
    if (GameResults.PlayerWonTimes > GameResults.ComputerWonTimes)
        return enGameWinner::WPlayer1;
    else if (GameResults.ComputerWonTimes > GameResults.PlayerWonTimes)
        return enGameWinner::WComputer;
    return enGameWinner::WDraw;
}

stGameResults GetGameResults(stRoundStatus RoundsStatus[], short TotalRounds)
{
    stGameResults GameResults;
    GameResults.TotalRounds = TotalRounds;
    GameResults.ComputerWonTimes = 0, GameResults.DrawTimes = 0, GameResults.PlayerWonTimes = 0;

    for (int i = 0; i < TotalRounds; i++)
    {
        switch (RoundsStatus[i].GameResults)
        {
            case enGameWinner::WPlayer1:
                GameResults.PlayerWonTimes++;
                break;
            case enGameWinner::WComputer:
                GameResults.ComputerWonTimes++;
                break;
            case enGameWinner::WDraw:
                GameResults.DrawTimes++;
                break;
        }
    }

    GameResults.GamerResults = GetWinner(GameResults);
    return GameResults;
}

void PrintGameSummary(stRoundStatus RoundsStatus[], short TotalRounds)
{
    stGameResults GameResults = GetGameResults(RoundsStatus, TotalRounds);
    ChangeScreen(GameResults.GamerResults);
    cout << "\n\n\t\t__________________________________________________________________";
    cout << "\n\n\t\t\t\t     +++ G a m e  O v e r ++++";
    cout << "\n\t\t__________________________________________________________________";
    cout << "\n\n\t\t_________________________ [Game Results ]_________________________";
    cout << "\n\n\t\tGame Rounds         :  " << GameResults.TotalRounds;
    cout << "\n\t\tPlayer1 won times   :  " << GameResults.PlayerWonTimes;
    cout << "\n\t\tComputer won times  :  " << GameResults.ComputerWonTimes;
    cout << "\n\t\tDraw times          :  " << GameResults.DrawTimes;
    cout << "\n\t\tFinal Winner        :  " << GamerWinnerToString(GameResults.GamerResults);
    cout << "\n\t\t__________________________________________________________________";
    
}

void StartGame()
{
    bool Continue = true;
    char NewGame;

    do
    {
        stRoundStatus RoundsStatus[10];
        short TotalRounds = 0;

        TotalRounds = ReadHomManyRounds();
        
        for (int CurrentRound = 0; CurrentRound < TotalRounds; CurrentRound++)
        {
            RoundsStatus[CurrentRound] = StartRound(CurrentRound + 1);
        }

        PrintGameSummary(RoundsStatus, TotalRounds);
        
        cout << "\n\n\t\tDo you want to play again? Y/N? ";
        cin >> NewGame;

        if (toupper(NewGame) != 'Y')
            break;
        
        system("CLS"); 
        system("color 7");
        
    } while (Continue);
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
