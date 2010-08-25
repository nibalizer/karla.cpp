//Spencer Krum
//Assignment 4
// March 15, 2010
//CS 161-1, Karla Fant
//dbad license
//Oddly game

#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>


using namespace std;
//some useful global variables
bool randomized = false;
int piles[3] = {0,0,0};
int playerOnePile = 0;
int playerTwoPile = 0;
int round = 0;

string currentPlayer = "Gamestart";	//gamestart is teh guy who is playing before everyone else gets there
string player1 = "Player One";
string player2 = "Player Two";
string gamestart = "Gamestart";



					//variable declarations i think
void setupGame();
void statusGame();
void nextTurn();
void winner();


int main(){				//short and sweet main, left the deffinition of game over inside a while loop
	setupGame();
	while ((piles[0] + piles[1] + piles[2]) != 0){
	nextTurn();
	}
	winner();
	return 0;
}

void setupGame(){			//the setup, seed random from time, use modulous to bring the random number down to size, then again to check for odd numbers, dealing with zero, etc
	
	//set up three piles
	srand(time(0));
	if (!randomized){
	for (int i = 0; i < 3; ++i){
		int random = rand();
		random = random % 10;
		if ((random % 2) != 0){
 			piles[i] = random;
		}
		else{
			if (random == 0){
				random += 1;
				piles[i] = random;
			}
			else{	
				random -= 1;
				piles[i] = random;
			}
	
		}
		randomized = true;	//this boolean is left over from the monstrosity that is my attempt to do this in openGL, trust me, you don't want to see that piece of s***, it's almost 500 lines of pure fail
	}
	}
	//tell the audience what is up
	cout << "Assignment 4 - Spencer Krum\n";
	cout << "Welcome!\n";
	cout << "Today we are playing the oddly game. There are three piles.\n";
	cout << "Each has an odd number of balls in it.\nYou and a buddy will ";
	cout << "take turns taking a number of balls from one pile only.\n";
	cout << "After all the balls in all the piles are gone, the player with \n";
	cout << "the odd number of balls wins! Good Luck and follow on screen instructions!\n";
	statusGame();
	
}	

//function to tell the user the status of the game as it moves forward
void statusGame(){	
	cout << "The current game status is: \n";
	cout << "Player One has " << playerOnePile << ".\n";
	cout << "Player Two has " << playerTwoPile << ".\n";
	cout << "Pile One has " << piles[0] << ".\n";
	cout << "Pile Two has " << piles[1] << ".\n";
	cout << "Pile Three has " << piles[2] << ".\n";
	cout << "It is now round " << round << ".\n";
	cout << "It is now " << currentPlayer << "'s turn.\n" ;
}


void nextTurn(){
	if (currentPlayer == gamestart){ 	//then it is the very first turn of the very first round
		currentPlayer = player1;
		round = 1;
	}
	cout << "It is now " << currentPlayer << "'s turn. Which pile will you remove from?\n";
	int pile;
	cin >> pile;
	cout << "You have chosen pile " << pile << ". How many balls will you pull from this pile?\n";
	int balls;
	cin >> balls;
	cout << "You have chosen to take " << balls << " from pile " << pile << ".\n";
	
	if ((piles[(pile - 1)] > 0 ) && (balls <= (piles[(pile - 1)]) )){
		piles[(pile -1)] -= balls;
		if (currentPlayer == player1){
			playerOnePile += balls;
			currentPlayer = player2;
			statusGame();
		}
		else{
			playerTwoPile += balls;
			round +=1;				//keeping track of rounds seems like a good idea
			currentPlayer = player1;		//by using a next step and currentPlayer model, this could be expanded to more players without too much grief.
			statusGame();		
		}
	}
	else {
		cout << "Your selections are incompatible with the physical system. Try again.\n"; //smarmy kids trying to ruin the game for everyone
		nextTurn();
	}
}

void winner(){
	if ((playerOnePile % 2) == 0) {
		cout << "Congratulations " << player2 << ". You won the game!\n" <<endl; //this win decision system makes it a lot easier for player two to win by cheating, but I like to assume an honest world. 
	}
	else{
		cout << "Congratulations " << player1 << ". You won the game!\n" <<endl; 
	}
}













