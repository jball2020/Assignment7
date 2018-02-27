/***************************************************************
	Class: 		Space
	File: 		Space.cc
	Author: 	Jordan Ball
	Date: 		11/28/2017
	Assignment: Project 6
	Purpose:	A class that defines a space for an Othello game
				a space is either white, black, or empty. Contains
				functions for flipping the space and checking the state
				of the piece
		

**********************************************************************/


#include<iostream>
#include<cstdlib>
#include<string>
#include "Space.h"
#include "colors.h"

using namespace std;

bool Space::is_black()const{
	return(black);
}

bool Space::is_white()const{
	return(white);
}

bool Space::is_empty()const{
	return(empty);
}

void Space::flip(){
	if(black){
		black = false;
		white = true;
		empty = false;
	} else if(white){
		black = true;
		white = false;
		empty = false;
	}
}

void Space::make_black(){
	black = true;
	white = false;
	empty = false;
}

void Space::make_white(){
	black = false;
	white = true;
	empty = false;
}

void Space::display()const{
	if(black){
		cout << " "<< B_CYAN << "  " << RESET << " ";
	}else if(white){
		cout << " " << B_WHITE << "  " << RESET << " ";
	}else if(empty){
		cout << "    ";
	}
}
