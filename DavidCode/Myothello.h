////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
David Wisniewski
Project 6b
Description:
This is the header file for Myothello here all of the functions needed to play
a two player game with another human are declared
*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
#ifndef MyOthello
#define MyOthello

#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <string>
#include "game.h"
#include "space.h"
using namespace std;
namespace std
{
class Myothello:public game
{
public:
  Myothello();
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
Below are make move and restat. Make move flips all of the peices that can be
fliped legally and restart starts the game over from the beginning.
*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
  void make_move(const std::string& move);
  void restart( );
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
Phase 3 functions
*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
  game* clone( )const;
  void compute_moves(std::queue<std::string>& moves) const;
  int evaluate( )const;
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
is_game_over returns true if the board is filled
winning returns who is the winner
display status shows the board
*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
  bool is_game_over( )const;
  who winning( ) const;
  void display_status( )const;
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
is_legal determines if the move made by the computer or human is legal or not
after is legal are helper functions that check multiple directions.
*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
  bool is_legal(const std::string& move) const;
  bool check_up(const int& row, const int& column)const;
  bool check_down(const int& row, const int& column)const;
  bool check_left(const int& row, const int& column)const;
  bool check_right(const int& row, const int& column)const;
  bool check_up_right(const int& row, const int& column)const;
  bool check_down_right(const int& row, const int& column)const;
  bool check_up_left(const int& row, const int& column)const;
  bool check_down_left(const int& row, const int& column)const;
////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
Helper  functions for make move each one is called in make move.
*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
  void flip_up( int & row,  int & column);
  void flip_down( int & row,  int & column);
  void flip_left(int & row,  int & column);
  void flip_right(int & row,  int & column);
  void flip_up_right(int & row,  int & column);
  void flip_down_right(int & row,  int & column);
  void flip_up_left(int & row,  int & column);
  void flip_down_left(int & row,  int & column);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
  void addH(){++h_skips;}
  void addC(){++c_skips;}
  int showH()const{return h_skips;}
  int showC()const{return c_skips;}
  void resetH(){h_skips = 0;}
  void resetC(){c_skips = 0;}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
std::string get_user_move( ) const;

private:
  space board[8][8];
  int h_skips;
  int c_skips;

};
}
#endif


// public:Copyright (c) 2017 Copyright Holder All Rights Reserved.
