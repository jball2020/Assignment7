/***************************************************************
	Class: 		MyOthello
	File: 		MyOthello.cc
	Author: 	Jordan Ball
	Date: 		11/28/2017
	Assignment: Project 6
	Purpose:	Class that defines the operations of an Othello
				board game
		

**********************************************************************/

#include "MyOthello.h"
#include "Space.h"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <sstream>
#include <string>
#include <queue>
#include "colors.h"

using namespace std;

namespace main_savitch_14
{
	
/***************************************************************
	Function: Restart()
	Purpose: Sets the board to the starting positions with the middle
			spaces set to the correct pieces

**********************************************************************/
	void MyOthello::restart(){
		int i = 0;
		int j = 0;
		for(i = 0; i < 8; i++){
			board[i][j] = Space(false, false, true);
			for(j = 0; j < 8; j++){
				if((i == 3 && j == 3) || (i == 4 && j == 4)){
					board[i][j] = Space(false, true, false);
				} else if((i == 3 && j== 4) || (i == 4 && j==3)){
					board[i][j] = Space(true, false, false);
				} else {
					board[i][j] = Space(false, false, true);
				}
			}
		}
	}
	
	
/***************************************************************
	Function: evaluate()
	Purpose: returns an positive integer if there are more computer
			spaces on the board than user spaces. Specifically,
			it returns the amount of white spaces - black spaces.

**********************************************************************/
	int MyOthello::evaluate( )const{
		int ratio = 0;
		for(int j = 0; j < 8; j++){
			for(int i = 0; i < 8; i++){
				if(board[i][j].is_black()){
					ratio--;
				} else if(board[i][j].is_white()){
					ratio++;
				}
			}
		}
		return(ratio);
	}
	
	
/***************************************************************
	Function: compute_moves()
	Purpose: builds moves and tests them to see if they are legal, if
			they are, then the are put into the queue

**********************************************************************/
	void MyOthello::compute_moves(std::queue<std::string>& moves)const{
		string m;
		string result;
		for(int j = 1; j < 9; j++){
			for(char i = 'A'; i < 'I'; i++){
				ostringstream Convert;
				Convert << j;
				result = Convert.str();
				m = string(1, i) + result;
				if(is_legal(m)){
					moves.push(m);
				}
			}
		}
	}
	
	
/***************************************************************
	Function: winning()
	Purpose: returns who has the most pieces

**********************************************************************/
	game::who MyOthello::winning( )const{
		int b_counter = 0;
		int w_counter = 0;
		for(int j = 0; j < 8; j++){
			for(int i = 0; i < 8; i++){
				if(board[i][j].is_black()){
					b_counter++;
				} else if(board[i][j].is_white()){
					w_counter++;
				}
			}
		}
		cout << "Blue: " << b_counter << " White: " << w_counter << endl;
		if(b_counter > w_counter){
			return(HUMAN);
		}
		if(w_counter > b_counter){
			return(COMPUTER);
		}
		if(w_counter == b_counter){
			return(NEUTRAL);
		} else {
			return(NEUTRAL);
		}
	}
	
	
/***************************************************************
	Function: get_user_move()
	Purpose: computes all available moves and if there are moves, it
			asks the user to enter a move. Otherwise it automatically
			passes for the user

**********************************************************************/
	string MyOthello::get_user_move( )const{
    	queue<string> moves;
    	compute_moves(moves);
    	if(!moves.empty()){
    		string answer;
			display_message("Your move, please: ");
			getline(cin, answer);
			return answer;	
		} else {
			const string PASS = "!1@2#3";
			display_message("You have no moves! Your turn was passed!\n");
			return(PASS);
		}
		
    }
	
	
/***************************************************************
	Function: display_status()
	Purpose: displays the current status of the board to the screen
			as a grid that is easy for the user to interpret

**********************************************************************/
	void MyOthello::display_status() const{
		int i = 0;
		int j = 0;
		int count = 1;
		cout << BOLD << "    A    B    C    D    E    F    G    H   " << RESET << endl;
		cout << GREEN << "  +----+----+----+----+----+----+----+----+" << RESET << endl;
		for(j = 0; j < 8; j++){
			cout << BOLD << count << GREEN << " |" << RESET;
			count++;
			for(i = 0; i < 8; i++){
				board[i][j].display();
				cout << GREEN << "|" << RESET;
				
			}
			cout << endl;
			cout << GREEN << "  +----+----+----+----+----+----+----+----+" << RESET << endl;
		}
	}
	
	
/***************************************************************
	Function: is_legal()
	Purpose: Checks to see if the move passed in is legal, by abiding
			to the rules of Othello. Calls another is_legal function
			for each direction. As long as one of these directions
			has a legal move, it returns true.

**********************************************************************/
	bool MyOthello::is_legal(const string& move) const{
		if(move == "!1@2#3"){
			return(true);
		}
		int row = (move[1] - '0') - 1;
		int col = (int(toupper(move[0]))- 65);

		if(!board[col][row].is_empty()){
			return(false);
		} else if(col > 7 || col < 0 || row > 7 || row < 0){
			return(false);
		}
		who player;
		if(next_mover() == HUMAN){
			player = HUMAN;
			if(is_Nlegal(row, col, player) || is_Slegal(row, col, player) || is_Elegal(row, col, player) || is_Wlegal(row, col, player) ||
			   is_NElegal(row, col, player) || is_NWlegal(row, col, player) || is_SElegal(row, col, player) || is_SWlegal(row, col, player)){
				return(true);
			} else {
				return(false);
			}
		} else if(next_mover() == COMPUTER){
			player = COMPUTER;
			if(is_Nlegal(row, col, player) || is_Slegal(row, col, player) || is_Elegal(row, col, player) || is_Wlegal(row, col, player) ||
			   is_NElegal(row, col, player) || is_NWlegal(row, col, player) || is_SElegal(row, col, player) || is_SWlegal(row, col, player)){
				return(true);
			} else {
				return(false);
			}
		}
		return(false);
	}
	
	
/***************************************************************
	Function: make_move()
	Purpose: makes a move by checking if there is a legal move in either
			direction then, using a helper function for each direction,
			it flips the appropriate pieces in that direction

**********************************************************************/
	void MyOthello::make_move(const string& move){
		if(move == "!1@2#3"){
			pass_counter++;
			game::make_move(move);
			return;
		}
		pass_counter = 0;
		int row = (move[1] - '0') - 1;
		int col = (int(toupper(move[0]))- 65);
		
		who player;
		if(next_mover() == HUMAN){
			player = HUMAN;
			board[col][row].make_black();
			if(is_Nlegal(row, col, player)){
				make_move_N(row, col, player);
			}
			if(is_Slegal(row, col, player)){
				make_move_S(row, col, player);
     		}
			if(is_Elegal(row, col, player)){
				make_move_E(row, col, player);
			}
			if(is_Wlegal(row, col, player)){
				make_move_W(row, col, player);
			}
			if(is_NWlegal(row, col, player)){
				make_move_NW(row, col, player);
			}
			if(is_NElegal(row, col, player)){
				make_move_NE(row, col, player);
			}
			if(is_SWlegal(row, col, player)){
				make_move_SW(row, col, player);
			}
			if(is_SElegal(row, col, player)){
				make_move_SE(row, col, player);
			}
		} else if(next_mover() == COMPUTER){
			player = COMPUTER;
			board[col][row].make_white();
			if(is_Nlegal(row, col, player)){
				make_move_N(row, col, player);
			}
			if(is_Slegal(row, col, player)){
				make_move_S(row, col, player);
     		}
			if(is_Elegal(row, col, player)){
				make_move_E(row, col, player);
			}
			if(is_Wlegal(row, col, player)){
				make_move_W(row, col, player);
			}
			if(is_NWlegal(row, col, player)){
				make_move_NW(row, col, player);
			}
			if(is_NElegal(row, col, player)){
				make_move_NE(row, col, player);
			}
			if(is_SWlegal(row, col, player)){
				make_move_SW(row, col, player);
			}
			if(is_SElegal(row, col, player)){
				make_move_SE(row, col, player);
			}
		}
		
		game::make_move(move);
	}
	
	
//**********************************************************************************
//	Functions: These are the helper functions for is_legal
//	Purpose: Each function checks to see if the move is legal in each
//			 direction. The move is passed into the helper functions
//           brokent down into its integer representation as two seperate variables
//
//**********************************************************************************
//**********************************************************************************
	bool MyOthello::is_Nlegal(const int& r, const int& c, const who& player)const{
		int row = r, col = c;
		if(player == HUMAN){
			if(board[col][row - 1].is_black() || board[col][row - 1].is_empty() ){
				return(false);
			}
			for(int j = row - 1, i = col; j >= 0; j--){
				if(board[i][j].is_black()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);
		} else if(player == COMPUTER){
			if(board[col][row - 1].is_white() || board[col][row - 1].is_empty() ){
				return(false);
			}
			for(int j = row - 1, i = col; j >= 0; j--){
				if(board[i][j].is_white()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);
		}
		return(false);
		
	}
	
	
	bool MyOthello::is_Slegal(const int& r, const int& c, const who& player)const{
		int row = r, col = c;
		if(player == HUMAN){
			if(board[col][row + 1].is_black() || board[col][row + 1].is_empty()){
				return(false);
			}
			for(int j = row + 1, i = col; j <= 7; j++){
				if(board[i][j].is_black()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);
		} else if(player == COMPUTER){
			if(board[col][row + 1].is_white() || board[col][row + 1].is_empty()){
				return(false);
			}
			for(int j = row + 1, i = col; j <= 7; j++){
				if(board[i][j].is_white()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);
		}
		return(false);
	}
	
	
	bool MyOthello::is_Elegal(const int& r, const int& c, const who& player)const{
		int row = r, col = c;
		if(player == HUMAN){
			if(board[col+1][row].is_black() || board[col+1][row].is_empty() ){
				return(false);
			}
			for(int j = row, i = col + 1; i <= 7; i++){
				if(board[i][j].is_black()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);			
		} else if(player == COMPUTER){
			if(board[col+1][row].is_white() || board[col+1][row].is_empty()){
				return(false);
			}
			for(int j = row, i = col + 1; i <= 7; i++){
				if(board[i][j].is_white()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);
		}
		return(false);
	}
	
	
	bool MyOthello::is_Wlegal(const int& r, const int& c, const who& player)const{
		int row = r, col = c;
		if(player == HUMAN){
			if(board[col-1][row].is_black() || board[col-1][row].is_empty() ){
				return(false);
			}
			for(int j = row, i = col - 1; i >= 0; i--){
				if(board[i][j].is_black()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);		
		} else if(player == COMPUTER){
			if(board[col-1][row].is_white() || board[col-1][row].is_empty() ){
				return(false);
			}
			for(int j = row, i = col - 1; i >= 0; i--){
				if(board[i][j].is_white()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);
		}
		return(false);

	}
	
	
	bool MyOthello::is_NElegal(const int& r, const int& c, const who& player)const{
		int row = r, col = c;
		if(player == HUMAN){
			if(board[col + 1][row - 1].is_black() || board[col + 1][row - 1].is_empty()){
				return(false);
			}
			for(int j = row - 1, i = col + 1; j >= 0 && i <= 7; i++, j--){
				if(board[i][j].is_black()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);			
		} else if(player == COMPUTER){
			if(board[col + 1][row - 1].is_white() || board[col + 1][row - 1].is_empty()){
				return(false);
			}
			for(int j = row - 1, i = col + 1; j >= 0 && i <= 7; i++, j--){
				if(board[i][j].is_white()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);			
		}
		return(false);

	}
	
	
	bool MyOthello::is_NWlegal(const int& r, const int& c, const who& player)const{
		int row = r, col = c;
		if(player == HUMAN){
			if(board[col-1][row - 1].is_black() || board[col-1][row - 1].is_empty()){
				return(false);
			}
			for(int j = row - 1, i = col - 1; j >= 0 && i >= 0; i--, j--){
				if(board[i][j].is_black()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);			
		} else if(player == COMPUTER){
			if(board[col-1][row - 1].is_white() || board[col-1][row - 1].is_empty()){
				return(false);
			}
			for(int j = row - 1, i = col - 1; j >= 0 && i >= 0; i--, j--){
				if(board[i][j].is_white()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);				
		}
		return(false);

	}
	
	
	bool MyOthello::is_SElegal(const int& r, const int& c, const who& player)const{
		int row = r, col = c;
		if(player == HUMAN){
			if(board[col + 1][row + 1].is_black() || board[col + 1][row + 1].is_empty()){
				return(false);
			}
			for(int j = row + 1, i = col + 1; j <= 7 && i <= 7; i++, j++){
				if(board[i][j].is_black()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);			
		} else if(player == COMPUTER){
			if(board[col + 1][row + 1].is_white() || board[col + 1][row + 1].is_empty()){
				return(false);
			}
			for(int j = row + 1, i = col + 1; j <= 7 && i <= 7; i++, j++){
				if(board[i][j].is_white()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);		
		}
		return(false);

	}
	
	
	bool MyOthello::is_SWlegal(const int& r, const int& c, const who& player)const{
		int row = r, col = c;
		if(player == HUMAN){
			if(board[col-1][row + 1].is_black() || board[col-1][row + 1].is_empty()){
				return(false);
			}
			for(int j = row + 1, i = col - 1; j <= 7 && i >= 0; i--, j++){
				if(board[i][j].is_black()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);			
		} else if(player == COMPUTER){
			if(board[col-1][row + 1].is_white() || board[col-1][row + 1].is_empty()){
				return(false);
			}
			for(int j = row + 1, i = col - 1; j <= 7 && i >= 0; i--, j++){
				if(board[i][j].is_white()){
					return(true);
				} else if(board[i][j].is_empty()){
					return(false);
				}
			}
			return(false);		
		}
		return(false);
	}
//********************************************************************************	
//********************************************************************************


	
//**********************************************************************************
//	Functions: These are the helper functions for make_move
//	Purpose: each function flips the appropriate pieces based on the move passed
//			 into the make_move function. The move is passed into the helper functions
//           brokent down into its integer representation as two seperate variables
//
//**********************************************************************************
//**********************************************************************************
	void MyOthello::make_move_N(const int& r, const int& c, const who& player){
		int row = r, col = c;
		if(player == HUMAN){
			for(int j = row - 1, i = col; j >= 0; j--){
				if(board[i][j].is_black()){					
					return;
				} else if(board[i][j].is_white()){
					board[i][j].flip();
				}
			}

		} else if(player == COMPUTER){
			for(int j = row -1, i = col; j >= 0; j--){
				if(board[i][j].is_white()){			
					return;
				} else if(board[i][j].is_black()){
					board[i][j].flip();
				}
			}

		}
	}
	
	
	void MyOthello::make_move_S(const int& r, const int& c, const who& player){
		int row = r, col = c;
		if(player == HUMAN){
			for(int j = row + 1, i = col; j <= 7; j++){
				if(board[i][j].is_black()){					
					return;
				} else if(board[i][j].is_white()){
					board[i][j].flip();
				}
			}

		} else if(player == COMPUTER){
			for(int j = row + 1, i = col; j <= 7; j++){
				if(board[i][j].is_white()){			
					return;
				} else if(board[i][j].is_black()){
					board[i][j].flip();
				}
			}

		}
	}
	
	
	void MyOthello::make_move_E(const int& r, const int& c, const who& player){
		int row = r, col = c;
		if(player == HUMAN){
			for(int j = row, i = col + 1; i <= 7; i++){
				if(board[i][j].is_black()){					
					return;
				} else if(board[i][j].is_white()){
					board[i][j].flip();
				}
			}

		} else if(player == COMPUTER){
			for(int j = row, i = col + 1; i <= 7; i++){
				if(board[i][j].is_white()){			
					return;
				} else if(board[i][j].is_black()){
					board[i][j].flip();
				}
			}

		}
	}
	
	
	void MyOthello::make_move_W(const int& r, const int& c, const who& player){
		int row = r, col = c;
		if(player == HUMAN){
			for(int j = row, i = col - 1; i >= 0; i--){
				if(board[i][j].is_black()){;					
					return;
				} else if(board[i][j].is_white()){
					board[i][j].flip();
				}
			}

		} else if(player == COMPUTER){
			for(int j = row, i = col - 1; i >= 0; i--){
				if(board[i][j].is_white()){			
					return;
				} else if(board[i][j].is_black()){
					board[i][j].flip();
				}
			}

		}
	}
	
	
	void MyOthello::make_move_NE(const int& r, const int& c, const who& player){
		int row = r, col = c;
		if(player == HUMAN){
			for(int j = row - 1, i = col + 1; j >= 0 && i <= 7; i++, j--){
				if(board[i][j].is_black()){					
					return;
				} else if(board[i][j].is_white()){
					board[i][j].flip();
				}
			}

		} else if(player == COMPUTER){
			for(int j = row -1, i = col +1; j >= 0 && i <= 7; i++, j--){
				if(board[i][j].is_white()){			
					return;
				} else if(board[i][j].is_black()){
					board[i][j].flip();
				}
			}

		}
	}
	
	
	void MyOthello::make_move_NW(const int& r, const int& c, const who& player){
		int row = r, col = c;
		if(player == HUMAN){
			for(int j = row - 1, i = col -1; j >= 0 && i >= 0; i--, j--){
				if(board[i][j].is_black()){					
					return;
				} else if(board[i][j].is_white()){
					board[i][j].flip();
				}
			}

		} else if(player == COMPUTER){
			for(int j = row -1, i = col -1; j >= 0 && i >= 0; i--, j--){
				if(board[i][j].is_white()){			
					return;
				} else if(board[i][j].is_black()){
					board[i][j].flip();
				}
			}

		}
	}
	
	void MyOthello::make_move_SE(const int& r, const int& c, const who& player){
		int row = r, col = c;
		if(player == HUMAN){
			for(int j = row + 1, i = col + 1; j <= 7 && i <= 7; i++, j++){
				if(board[i][j].is_black()){					
					return;
				} else if(board[i][j].is_white()){
					board[i][j].flip();
				}
			}

		} else if(player == COMPUTER){
			for(int j = row+1, i = col+1; j <= 7 && i <= 7; i++, j++){
				if(board[i][j].is_white()){			
					return;
				} else if(board[i][j].is_black()){
					board[i][j].flip();
				}
			}

		}
	}
	
		
	void MyOthello::make_move_SW(const int& r, const int& c, const who& player){
		int row = r, col = c;
		if(player == HUMAN){
			for(int j = row+1, i = col-1; j <= 7 && i >= 0; i--, j++){
				if(board[i][j].is_black()){					
					return;
				} else if(board[i][j].is_white()){
					board[i][j].flip();
				}
			}

		} else if(player == COMPUTER){
			for(int j = row+1, i = col-1; j <= 7 && i >= 0; i--, j++){
				if(board[i][j].is_white()){			
					return;
				} else if(board[i][j].is_black()){
					board[i][j].flip();
				}
			}

		}
	}
	
}

