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

#ifndef SPACE_H_TAG
#define SPACE_H_TAG

#include<cstdlib>

using namespace std;


class Space{
	public:
		Space(bool b = false, bool w = false, bool e = true){
			black = b;
			white = w;
			empty = e;
		}
		bool is_black()const;
		bool is_white()const;
		bool is_empty()const;
		void flip();
		void make_black();
		void make_white();
		void display()const;
	private:
		bool black;
		bool white;
		bool empty;
};


#endif
