//Program Name: Hangman
//Purpose: Study simple words through game.
//Description : An user will see a words unseen. The user should find out what the words is in 8 trials.
//Author: Manseung Woo
//Date Last Modified: December 9th, 2019

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Constants.
// This constants contains possible answer words.
const string GAME_WORDS[20] = {"EXAMPLE", "STARBUCKS", "PAPER", "SILVER", "NOTEBOOK", "MYTH", "REALITY", "APPLE", "MIRROR","MUSEUM",
 "CLOSET", "BEDDING", "DESK", "SNEAKERS", "DOOR", "WINDOWS", "COMPUTER", "MECHANIC", "CARPENTER", "PENCIL"};
// These two constants are for alphabet board.
const int ROWS = 5;
const int COLS = 6;
// This constant is for possible trials.
const int LIFE = 8;

// Function Prototypes.
// This function generates a random word.
string wordGenerator();
// This function assigns blank marks to a gameboard(answersheet) by it's length.
void answerSheetGenerator(char blankCharArray[], int arrayLength);
// This function shows current gameboard and possible choices for alphabets.
void displayInfo(char currentWord[], int numCharsInWord, char charBoard[][COLS], int rows);
// This function make the player choose an alphabet and modify the gameboard and alphabet sheet.
void playerTurn(string answer, char currentWord[], int numCharsInWord, char charBoard[][COLS], int rows);
// This function check if the player won the game.
bool checkWin(char currentWord[], int numCharsInWord);


// Main Function
int main(){
    // Generate a random word for the answer. declare an variable for the answer and assign the random word.
    string answerWord = wordGenerator();
    // Declare an int variable and initialize it with the length of the answer
    int howManyCharacters = answerWord.length();
    // Initialize a char array for gameboard.
    char answerSheetThisGame[howManyCharacters];
    // Assign blank marks to a gameboard(answersheet) by it's length
    answerSheetGenerator(answerSheetThisGame, howManyCharacters);
    // Declare chances for game and initialize it with 8 trials.
    int chancesLeft = LIFE;
    // Delcare and initialize an alphabets board.
    char alphabetBoard[5][6] = {
        {'A','B','C','D','E','F'},
        {'G','H','I','J','K','L'},
        {'M','N','O','P','Q','R'},
        {'S','T','U','V','W','X'},
        {'Y','Z','*','*','*','*'}};

    cout << "Welcome to Hangman!" << endl;

    // Provice the player initial status of the game.
    displayInfo(answerSheetThisGame, howManyCharacters, alphabetBoard, ROWS);

    // Until the player win or the player uses all the trials, iterate the player's turn.
    do{
        // Display the trials left.
        cout << "\nYou have " << chancesLeft << " chances left.";
        // Execute the player turn.
        playerTurn(answerWord, answerSheetThisGame, howManyCharacters, alphabetBoard, ROWS);
        // Deduct 1 from trials left at every turn.
        chancesLeft--;
        // Check if the player win the game, if the player wins, display the message and terminate the program.
        if(checkWin(answerSheetThisGame, howManyCharacters)){
            cout << "\n" << "The answer is " << answerWord << "!" << endl;
            return 0;
        };
        // After a game turn, display current status.
        displayInfo(answerSheetThisGame, howManyCharacters, alphabetBoard, ROWS);
    } while (chancesLeft > 0);
    // If the trials left become 0, display the message and terminate the program.
    cout << "\nYou LOSE. Run this program again.";

    return 0;
}



// This function generates a random word.
string wordGenerator(){
    // Generate a random number in range of 0~19
    srand(time(0));
    int ranNum = (rand() % 20) ;
    // Use the random number as an index number for game word.
    return GAME_WORDS[ranNum];
}

// This function assigns blank marks to a gameboard(answersheet) by it's length.
void answerSheetGenerator(char blankCharArray[], int arrayLength){
    for (int a=0; a<arrayLength; a++){
        blankCharArray[a] = '_';
    }
}

// This function shows current gameboard and possible choices for alphabets.
void displayInfo(char currentWord[], int numCharsInWord, char charBoard[][COLS], int rows){
    // Display current gameboard.
    cout << "\n";
    for (int a = 0; a < numCharsInWord; a++){
        cout << currentWord[a];
    }
    cout << "\n" <<endl;

    // Display current alphabet board.
    for (int b = 0; b < rows; b++){
        for (int c = 0; c < COLS; c++){
            cout << charBoard[b][c];
        }
        cout << endl;
    }
}

// This function make the player choose an alphabet and modify the gameboard and alphabet sheet.
void playerTurn(string answer, char currentWord[], int numCharsInWord, char charBoard[][COLS], int rows){
    // Declare char variable for user select
    char userSelect;
    // Declare a boolean variable to tell if a player choose valid alphabet. initialize it with false.
    bool chooseRight = false;
    // Until a player chooses valid alphabet, interate the choosing process(get user input).
    do{
    cout << "\nChoose an alphabet you want on the alphabet board:";
    cin >> userSelect;

    // If user type other than capital alphabet, make him/her do it again.
    if(userSelect<'A'||userSelect>'Z'){
        cout << "\nYou should choose A~Z(Capital)" << endl;
        continue;
    }

    // If user type an alphabet he/she already chekced, make him/her do it again.
    int countCharacter = 0;
    for (int b = 0; b < rows; b++){
        for (int c = 0; c < COLS; c++){
            if (charBoard[b][c] == userSelect){
                countCharacter++;
            }
        }
    }
    if (countCharacter != 1){ // Because if the selected alphabet has already chosen before, countCharacter become 0.
        cout << "\nYou already tried that one.";
        continue;
    }

    // Now the user chose right alphabet
    chooseRight = true;

    } while (chooseRight == false);

    // Make the alphabet that the user chose '*' on alphabet board.
    for (int b = 0; b < rows; b++){
        for (int c = 0; c < COLS; c++){
            if (charBoard[b][c] == userSelect){
                charBoard[b][c] = '*';
            }
        }
    }

    // If the alphabet that the user chose is on the answer, make it seen on game board.
    for (int a = 0; a < numCharsInWord; a++){
        if (answer[a] == userSelect){
            currentWord[a] = userSelect;
        }
    }

}

// This function check if the player won the game.
bool checkWin(char currentWord[], int numCharsInWord){
    for (int a = 0; a < numCharsInWord; a++){
        if (currentWord[a]=='_'){ // If there is '_' in game board, it's still on going.
            return false;
        }
    }
    cout << "\nYOU WIN!!!" << endl;;
    return true;
}