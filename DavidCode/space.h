////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
David Wisniewski
project 6b
This is the space class which is what makes up the board for othello
*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
#ifndef Space
#define Space
#include <cassert>
#include <climits>
#include<fstream>
#include <iostream>
#include <queue>
#include <string>
#include"char.h"
#include "colors.h"

using namespace std;
class space
{
public:
  space();
  bool is_black()const{ return black;}
  bool is_white()const{return white;}
  bool is_empty()const{return blank;}

  void set_black(){black = true; blank = false;}
  void set_white(){white = true; blank = false;}
  void empty(){blank = true; white = false; black = false;}
  void flip();
  void display(const std::ostream& outs)const;

private:
  bool black;
  bool white;
  bool blank;
};
std::ostream& operator << (ostream& outs, const space& s);
#endif

// public:Copyright (c) 2017 Copyright Holder All Rights Reserved.
