#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

enum enChoice { Rock = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stGameResults
{
    short TotalRounds = 0;
    short PlayerWonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

struct stRoundInfo
{
    short RoundNumber;
    enChoice Player1Choice;
    enChoice ComputerChoice;
    enWinner RoundWinner;
    string WinnerName;
};

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum; 
}

enWinner WhoWonTheRound(enChoice Player1Choice ,enChoice ComputerChoice)
{
    if (Player1Choice == ComputerChoice)
        return enWinner::Draw;
    
    switch (Player1Choice)
    {
    case enChoice::Paper:
        if (ComputerChoice == enChoice::Scissors)
            return enWinner::Computer;
    case enChoice::Rock:
        if (ComputerChoice == enChoice::Paper)
            return enWinner::Computer;
    case enChoice::Scissors:
        if (ComputerChoice == enChoice::Rock)
            return enWinner::Computer;
    }
    
    return enWinner::Player1;
}

string ChoiceName(enChoice Choice)
{
    string arrChoices[3] = {"Rock", "Paper", "Scissors"};
    return arrChoices[Choice - 1];
}  

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = {"Player1", "Computer", "Draw"};
    return arrWinnerName[Winner - 1];
}  

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << '\a';
        break;
    default:
        system("color 6F");
        break;
    }
}

void PrintRoundResults(stRoundInfo RoundInfo) 
{ 
    cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n"; 
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl; 
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl; 
    cout << "Round Winner : [" << RoundInfo.WinnerName << "] \n"; 
    cout << "__________________________________\n" << endl; 
    SetWinnerScreenColor(RoundInfo.RoundWinner); 
} 

enChoice ReadPlayerChoice()
{
    short Choice = 1; 
    do
    { 
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? "; 
        cin >> Choice; 
    } while (Choice < 1 || Choice >3); 

    return (enChoice) Choice; 
}

enChoice GetComputerChoice()
{
    return (enChoice) RandomNumber(1, 3);
}

enWinner WhoWonTheGame(short ComputerWonTimes, short PlayerWonTimes, short DrawTimes)
{
    if (ComputerWonTimes > PlayerWonTimes)
        return enWinner::Computer;
    else if (PlayerWonTimes > ComputerWonTimes)
        return enWinner::Player1;
    return enWinner::Draw;
}

stGameResults FillGameResults(short TotalRounds, short ComputerWonTimes, short PlayerWonTimes, short DrawTimes)
{
    stGameResults GameResults;
    GameResults.ComputerWonTimes = ComputerWonTimes;
    GameResults.PlayerWonTimes = PlayerWonTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.TotalRounds = TotalRounds;
    GameResults.GameWinner = WhoWonTheGame(ComputerWonTimes, PlayerWonTimes, DrawTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}

stGameResults PlayGame(short TotalRounds)
{   
    stRoundInfo RoundInfo;
    short ComputerWonTimes = 0, PlayerWonTimes = 0, DrawTimes = 0;

    for (int i = 1; i <= TotalRounds; i++)
    {
        cout << "\nRound [" << i << "] begins:\n";
        RoundInfo.RoundNumber = i;
        RoundInfo.Player1Choice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo.Player1Choice, RoundInfo.ComputerChoice);
        RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);

        if (RoundInfo.RoundWinner == enWinner::Player1)
            PlayerWonTimes++;
        else if (RoundInfo.RoundWinner == enWinner::Computer)
            ComputerWonTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }


    return FillGameResults(TotalRounds, ComputerWonTimes, PlayerWonTimes, DrawTimes);
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

void ResetScreen()
{
    system("CLS"); 
    system("color 0f");
}

string Tabs(short TabsCount)
{
    string TotalTabs = "";
    for (int i = 0; i <= TabsCount; i++)
    {
        TotalTabs += "\t";
    }
    return TotalTabs;
}

void ShowGameOverScreen() 
{ 
    cout << Tabs(2) << "__________________________________________________________\n\n"; 
    cout << Tabs(2) << " +++ G a m e O v e r +++\n"; 
    cout << Tabs(2) << "__________________________________________________________\n\n"; 
} 

void ShowFinalGameResults(stGameResults GameResults) 
{ 
    cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n"; 
    cout << Tabs(2) << "Game Rounds : " << GameResults.TotalRounds << endl; 
    cout << Tabs(2) << "Player1 won times : " << GameResults.PlayerWonTimes << endl; 
    cout << Tabs(2) << "Computer won times : " << GameResults.ComputerWonTimes << endl; 
    cout << Tabs(2) << "Draw times : " << GameResults.DrawTimes << endl; 
    cout << Tabs(2) << "Final Winner : " << GameResults.WinnerName << endl; 
    cout << Tabs(2) << "___________________________________________________________\n"; 
    SetWinnerScreenColor(GameResults.GameWinner); 
} 

void StartGame()
{
    char PlayAgain;

    do
    {
        ResetScreen();

        stGameResults GameResults = PlayGame(ReadHomManyRounds());

        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;        
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
