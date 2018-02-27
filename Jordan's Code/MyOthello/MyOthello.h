/***************************************************************
	Class: 		MyOthello
	File: 		MyOthello.h
	Author: 	Jordan Ball
	Date: 		11/28/2017
	Assignment: Project 6
	Purpose:	Class that defines the operations of an Othello
				board game
		

**********************************************************************/

#ifndef MY_OTHELLO_GAME
#define MY_OTHELLO_GAME

#include<cstdlib>
#include<string>
#include "game.h"
#include "Space.h"

namespace main_savitch_14
{
	class MyOthello : public game{
		public:
			MyOthello(){ restart(); available_flips = 0; pass_counter = 0;}
			void restart();
			void display_status() const;
			bool is_legal(const string& move) const;
			void make_move(const string& move);
			string get_user_move( )const;
			
			game* clone( ) const{return(new MyOthello(*this));}
			void compute_moves(std::queue<std::string>& moves)const;
			int evaluate( )const;
			bool is_game_over( ) const{return(pass_counter == 2);}
			game::who winning( )const;
			
		private:
			Space board[8][8];
			int pass_counter;
			int available_flips;
			
			bool is_Nlegal(const int& r, const int& c, const who& player)const;
			bool is_Slegal(const int& r, const int& c, const who& player)const;
			bool is_Elegal(const int& r, const int& c, const who& player)const;
			bool is_Wlegal(const int& r, const int& c, const who& player)const;
			bool is_NElegal(const int& r, const int& c, const who& player)const;
			bool is_SElegal(const int& r, const int& c, const who& player)const;
			bool is_NWlegal(const int& r, const int& c, const who& player)const;
			bool is_SWlegal(const int& r, const int& c, const who& player)const;
			
			void make_move_N(const int& r, const int& c, const who& player);
			void make_move_S(const int& r, const int& c, const who& player);
			void make_move_E(const int& r, const int& c, const who& player);
			void make_move_W(const int& r, const int& c, const who& player);
			void make_move_NE(const int& r, const int& c, const who& player);
			void make_move_NW(const int& r, const int& c, const who& player);
			void make_move_SE(const int& r, const int& c, const who& player);
			void make_move_SW(const int& r, const int& c, const who& player);
	};

	
	
}

#endif
