#include <iostream>
#include<cstdlib>
using namespace std;
enum enGameChoice { stone = 1, paper = 2, scissor = 3 };
enum enWinner { Player1 = 1, computer = 2, Draw = 3 };
struct StRoundInfo {
    short GameRound;
    enGameChoice Player1Choice;
    enGameChoice computerChoice;
    enWinner Winner;
    string WinnerName;
};
struct StGameResults {
    short GameRounds;
    short Player1WinTimes;
    short Computer2WinTimes;
    short DrawTimes;
    enWinner GameWinner;
    string WinnerName = "";
};
string WinnerName(enWinner Winner) {
    string arrWinner[3] = { "Player1", "computer", "No Winner" };
    return arrWinner[Winner - 1];
}
string ChoiceName(enGameChoice choice) {
    string arrGameChoice[3] = { "stone", "paper", "scissor" };
    return arrGameChoice[choice - 1];
}
int RandomNumber(int From, int To) {
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}
enWinner WhoWonTheRound(StRoundInfo RoundInfo) {
    if (RoundInfo.Player1Choice == RoundInfo.computerChoice)
    {
        return enWinner::Draw;
    }
    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::stone:
        if (RoundInfo.computerChoice == enGameChoice::paper)
        {
            return enWinner::computer;
        }
        break;
    case enGameChoice::paper:
        if (RoundInfo.computerChoice == enGameChoice::scissor)
        {
            return enWinner::computer;
        }
        break;
    case enGameChoice::scissor:
        if (RoundInfo.computerChoice == enGameChoice::stone)
        {
            return enWinner::computer;
        }
        break;

    }
    return enWinner::Player1;
}
void SetWinnerscreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F"); //green
        break;
    case enWinner::computer:
        system("color 4F"); //red and music
        cout << "\a";
        break;
    default:
        system("color 6F"); //yellow
        break;
    }
}
void PrintRoundResult(StRoundInfo RoundInfo) {
    cout << "__________Round[ " << RoundInfo.GameRound << " ]__________" << endl;
    cout << "Player Choice   : " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice : " << ChoiceName(RoundInfo.computerChoice) << endl;
    cout << "Round Winner    : " << RoundInfo.WinnerName << endl;
    cout << "________________________________________" << endl;
    SetWinnerscreenColor(RoundInfo.Winner);
}
enGameChoice PlayerChoice() {
    short Choice = 1;
    do {
        cout << "Your Choice : [1] = stone, [2] = paper, [3] = scissor? " << endl;
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice() {
    return (enGameChoice)RandomNumber(1, 3);
}
enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes) {

    if (Player1WinTimes > ComputerWinTimes)
    {
        return enWinner::Player1;
    }

    else if (Player1WinTimes < ComputerWinTimes)
    {
        return enWinner::computer;
    }
    else
    {
        return enWinner::Draw;
    }
}
StGameResults FillGameResults(int GameRound, short Player1WinTimes, short ComputerWinTimes,
    short DrawTimes)
{
    StGameResults GameResults;
    GameResults.GameRounds = GameRound;
    GameResults.Player1WinTimes = Player1WinTimes;
    GameResults.Computer2WinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}
StGameResults PlayGame(short HowManyRound) {
    StRoundInfo RoundInfo;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;

    for (short i = 1; i <= HowManyRound; i++) {
        cout << "\nRound [ " << i << " ] begins" << endl;
        RoundInfo.GameRound = i;
        RoundInfo.Player1Choice = PlayerChoice();
        RoundInfo.computerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
        PrintRoundResult(RoundInfo);
        if (RoundInfo.Winner == enWinner::Player1)
        {
            Player1WinTimes++;
        }
        else if (RoundInfo.Winner == enWinner::computer)
        {
            ComputerWinTimes++;
        }
        else
        {
            DrawTimes++;
        }
    }
    return FillGameResults(HowManyRound, Player1WinTimes, ComputerWinTimes, DrawTimes);
}
short HowManyRound()
{
    short choice = 1;
    do {
        cout << "How many round 1 To 10?" << endl;
        cin >> choice;
    } while (choice < 1 || choice > 10);
    return choice;
}
string Taps(short NumberOfTaps) {
    string t = "\t";
    for (int i = 1; i < NumberOfTaps; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}
void ReturnScreen()
{
    system("cls");
    system("color 0F");
}
void ShowGameOver() {
    cout << "\n\n\n\n";
    cout << Taps(3) << "_______________________________" << endl;
    cout << Taps(3) << "    +++ Game Over +++     " << endl;
    cout << Taps(3) << "_______________________________" << endl;
}
void ShowFinalGameResults(StGameResults GameResults)
{
    cout << Taps(3) << "__________[Game Results]________" << endl;
    cout << Taps(3) << "Game round       : " << GameResults.GameRounds << endl;
    cout << Taps(3) << "Player1WinTimes  : " << GameResults.Player1WinTimes << endl;
    cout << Taps(3) << "ComputerWinTimes : " << GameResults.Computer2WinTimes << endl;
    cout << Taps(3) << "DrawTimes        : " << GameResults.DrawTimes << endl;
    cout << Taps(3) << "Final Winner     : " << GameResults.WinnerName << endl;
    SetWinnerscreenColor(GameResults.GameWinner);
    cout << Taps(3) << "____________________________" << endl;

}
void starGame()
{
    char PlayAgain = 'Y';
    do {
        ReturnScreen();
        StGameResults GameResults = PlayGame(HowManyRound());
        ShowGameOver();
        ShowFinalGameResults(GameResults);
        cout << endl << "Do you want to PlayAgain? y / n " << endl;
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
    srand((unsigned)time(NULL));
    starGame();

    return 0;
}


