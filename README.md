# Rock, Paper, Scissors Game
---
Simple project for rock, paper, scissors game made with pure C++ using simple procedural programming.
---
## How to play
1. Compile the code (more on this later).
2. Start the game by entering the number of rounds you want to play ranging from 1 to 10.
3. The game will prompt you to enter rock (1) or paper (2) or scissors (3).
4. After entering your discision the computer will generate a random discision.
5. The game will check if its a draw or your win or computer wins based on the inputs.
6. After finishing all the rounds there will be a Game Over page that shows game info and results.
---
## How to compile
```bash
g++ main.cpp -o game.exe
```
---
## Data Storing Mechanism
The game mainly using structs to store necessarily data for the game using to structures:
1. stGameResults : which stores overall game results mainly for the Game Over screen and ending info/results.
2. stRoundStatus : which stores round specific data including discisions and round result.
3. an array of stRoundStatus : to store each round data as an element in array to help with calculating ending game results later on.
---
## Game Logic
The code will first run the main loop of the game using the StartGame() procedure which include the main loop of the game.
Inside the main loop it will first prompt the player for the number of rounds he/she wants to play using ReadHomManyRounds().
After prompting the round count a for loop will begin in each iteration will call StartRound() function which return stRoundStatus datatype to store in the array of rounds.
After finishing all rounds it will call PrintGameSummary() to print ending results of the game.

