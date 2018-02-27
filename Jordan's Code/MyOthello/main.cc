/***************************************************************
	File: 		main.cc
	Author: 	Jordan Ball
	Date: 		11/28/2017
	Assignment: Project 6
	Purpose:	Declares and intitiates a MyOthello game
		

**********************************************************************/


#include "game.h"
#include "colors.h"
#include<iostream>
#include "MyOthello.h"

using namespace std;
using namespace main_savitch_14;

int main(){
	MyOthello mygame;
	cout << "Welcome to MyOthello!" << endl
		 << "Rules:1)Player 1 is blue and Player 2 is White" << endl
		 << "      2)You must place a piece that outflanks your opponent's pieces" << endl
	     << "      3)If the opponent's piece is outflanked, it will be flipped to your color." << endl
	     << "      4)Please enter your move by entering the column letter followed by the row" << endl
		 << "        number. Ex: \"D3\"" << endl;
		 
	game::who winner;
	winner = mygame.play();
	if(winner == game::HUMAN){
		cout << CYAN << "Congratulations, you won the game!" << RESET << endl;
	} else if(winner == game::COMPUTER){
		cout << "You lost against the computer!\n";
	} else if(winner == game::NEUTRAL){
		cout << "You tied!\n";
	}
	return(0);
}
