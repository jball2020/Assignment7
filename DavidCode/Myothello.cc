////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
David Wisniewski
project 6b
Description:
This is the implementation file for Myothello.Here all of the helper functions
are implemented along with the ones required to make the game wor for phase 2
*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
#include"Myothello.h"
using namespace std;

namespace std
{
Myothello::Myothello()
{
  restart();
  h_skips = 0;
  c_skips = 0;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
game * Myothello::clone()const
{
  return new Myothello(*this);
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
 void Myothello::restart()
 {
   const int size = 7;
   for (int i = 0; i <= size; ++i)
   {
     for (int j = 0; j <= size; ++j)
     {
       board[i][j].empty();
     }
   }
   board[3][3].set_white();
   board[3][4].set_black();
   board[4][3].set_black();
   board[4][4].set_white();

 }
 ////////////////////////////////////////////////////////////////////////////////
 ////////////////////////////////////////////////////////////////////////////////
void Myothello::display_status()const
  {
    int X = 1;
    std::cout << '\n';
    std::cout << "  A" << " B"<< " C"<< " D" << " E" << " F" << " G" << " H \n";
    for (int i = 0; i < 8; ++i)
    {
      for (int j = 0; j < 8; ++j)
      {
        if (j==0)
        {
          std::cout << X << " "<< board[i][j];
          X++;
        }
      else
      std::cout << board[i][j];
      }
      std::cout << '\n';
    }

  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool Myothello::is_legal(const std::string& move)const
{
  int row, column;

  column = int(toupper(move[0])-'A');
  row = int(move[1] - '1');

  if(move == "0")
  {
  return true;
  }
  else if(row < 0 || column < 0)
  {
    return false;
  }
//****************************************************************************//
  else  if(row > 7 || column > 7)
  {
    return false;
  }
  else if( board[row][column].is_empty() == false)
  {
    return false;
  }
//****************************************************************************//
  else if(check_up(row,column))
  {
    return true;
  }
//****************************************************************************//
  else if(check_down(row,column))
  {
    return true;
  }
//****************************************************************************//
  else if(check_left(row,column))
  {
    return true;
  }
//****************************************************************************//
  else if(check_right(row,column))
  {
    return true;
  }
//****************************************************************************//
  else  if(check_up_right(row,column))
  {
    return true;
  }
//****************************************************************************//
  else  if(check_down_right(row,column))
  {
    return true;
  }
//****************************************************************************//
  else  if( check_down_right(row, column))
  {
    return true;
  }
//****************************************************************************//
  else  if(check_up_left(row, column))
  {
    return true;
  }
//****************************************************************************//
  else  if(check_down_left(row, column))
  {
    return true;
  }

  else
  {
    return  false;
  }

}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Myothello::make_move(const std::string& move)
{
  int row, column;
  if(move == "A1")
    return;
  if(move == "0")
  {
    std::cout << "Turn skipped" << '\n';
    if(next_mover() == HUMAN)
    addH();
    if (next_mover() == COMPUTER)
    addC();
    game::make_move(move);
    return;
  }
  if(next_mover() == HUMAN)
    resetH();

  if (next_mover() == COMPUTER)
    resetC();

  column = int(toupper(move[0])-'A');
  row = int(move[1] - '1');
  if(row < 0 || column < 0)
  {
    return;
  }
  else if(next_mover() == HUMAN) // then it's the first players turn
  {
    board[row][column].set_black();
  }
  else if (next_mover() == COMPUTER)
  {
    board[row][column].set_white();

  }

  flip_up(row, column);
  flip_down(row, column);
  flip_left(row,column);
  flip_right(row, column);
  flip_up_right(row, column);
  flip_down_right(row, column);
  flip_up_left(row, column);
  flip_down_left(row, column);


  game::make_move(move);


}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool Myothello::check_up(const int & row, const int & column)const
{
  bool legal;
  if(next_mover() == HUMAN) // then it's the first players turn
  {
//Checks up to see if the move is legal
    if(board[row-1][column].is_white())
    {
      for(int i = row-1; i >= 0 ; --i)
      {
        if(board[i][column].is_black())
        {
          return legal = true;
        }
        if(board[i][column].is_empty())
        {
          return legal = false;
        }
      }
    }
  }
  if(next_mover() == COMPUTER) // then it's the second player's turn
   {
     if(board[row-1][column].is_black())
     {
       for(int i = row-1; i >= 0 ; --i)
       {
         if(board[i][column].is_white())
         {
           return legal = true;
         }
         if(board[i][column].is_empty())
         {
           return legal = false;
         }
       }
     }
  }
 return legal =  false;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool Myothello::check_down(const int & row, const int & column)const
{
  if(next_mover() == HUMAN) // then it's the first players turn
  {
    if(board[row + 1][column].is_white())
    {
      for(int i = row+1; i < 8  ; ++i)
      {
        if(board[i][column].is_black())
        {
          return true;
        }
        if(board[i][column].is_empty())
        {
          return false;
        }
      }//end of for loop
    }
  }
  if(next_mover() == COMPUTER) // then it's the second player's turn
  {
  //Checks down to see if the move is legal
     if(board[row + 1][column].is_black())
      {
        for(int i = row+1; i < 8  ; ++i)
        {
          if(board[i][column].is_white())
          {
            return true;
          }
          if(board[i][column].is_empty())
          {
            return false;
          }
        }//end of for loop
      }
  }
 return false;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool Myothello::check_left(const int & row, const int & column)const
{
  bool legal;
  if(next_mover() == HUMAN) // then it's the first players turn
  {
    //Checks up to see if the move is legal
    if(board[row][column-1].is_white())
    {
      for(int i = column-1; i >= 0 ; --i)
      {
        if(board[row][i].is_black())
        {
          return true;
        }
        if(board[row][i].is_empty())
        {
          return false;
        }
      }
    }
  }
  if(next_mover() == COMPUTER) // then it's the second player's turn
  {
    if(board[row][column-1].is_black())
    {
      for(int i = column-1; i >=0 ; --i)
      {
        if(board[row][i].is_white())
        {
          return true;
        }
        if(board[row][i].is_empty())
        {
          return false;
        }
      }
    }
  }
return false;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool Myothello::check_right(const int & row, const int & column)const
{
  if(next_mover() == HUMAN) // then it's the first players turn
  {
    if(board[row][column+1].is_white())
    {
      for(int i = column+1; i < 8  ; ++i)
      {
        if(board[row][i].is_black())
        {
          return true;
        }
        if(board[row][i].is_empty())
        {
          return false;
        }
      }//end of for loop
    }
  }//end of if(mover == HUMAN)

  if(next_mover() == COMPUTER) // then it's the second player's turn
  {
    if(board[row][column+1].is_black())
    {
      for(int i = column+1; i < 8  ; ++i)
      {
        if(board[row][i].is_white())
        {
        return  true;
        }
        if(board[row][i].is_empty())
        {
          return false;
        }
      }//end of for loop
    }

  }
return false;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool Myothello::check_up_right(const int & row, const int & column)const
{
  bool legal;
  if(next_mover() == HUMAN) // then it's the first players turn
  {
    if(board[row-1][column+1].is_white())
    {
      for(int i = row-1,c = column+1;  i >= 0 && c < 8 ; --i, ++c)
      {
        if(board[i][c].is_black())
        {
          return legal = true;
        }
        if(board[i][c].is_empty())
        {
          return legal = false;
        }
      }
    }
  }

  if(next_mover() == COMPUTER) // then it's the second player's turn
  {
    if(board[row-1][column+1].is_black())
    {
      for(int i = row-1,c = column+1;  i >= 0 && c < 8 ; --i, ++c)
      {
        if(board[i][c].is_white())
        {
          return legal = true;
        }
        if(board[i][c].is_empty())
        {
          return legal = false;
        }
      }
    }
  }
return legal = false;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool Myothello::check_down_right(const int & row, const int & column)const
  {
    bool legal;
    if(next_mover() == HUMAN) // then it's the first players turn
    {
      if(board[row +1][column+1].is_white())
      {
        for(int i = row+1, c = column+1; ((i < 8) && (c < 8)) ; ++i, ++c)
        {
          if(board[i][c].is_empty())
          {
            return legal = false;
          }
          if(board[i][c].is_black())
          {
            return legal = true;
          }
        }//end of for loop
      }
    }
    if(next_mover() == COMPUTER) // then it's the second player's turn
     {
       if(board[row +1][column+1].is_black())
       {
         for(int i = row+1, c = column+1; ((i < 8) && (c < 8)) ; ++i, ++c)
         {
         if(board[i][c].is_white())
           {
             return legal = true;
           }
        if(board[i][c].is_empty())
           {
             return legal = false;
           }
         }//end of for loop
       }
     }
     return legal = false;
  }


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool Myothello::check_up_left(const int & row, const int & column)const
  {
    bool legal;
    if(next_mover() == HUMAN) // then it's the first players turn
    {
      if(board[row -1][column-1].is_white())
      {
        int c = column-1;
        for(int i = row-1; i >= 0  ; --i)
        {
          if(board[i][c].is_black())
          {
            return legal = true;
          }
          if(board[i][c].is_empty())
          {
            return legal = false;
          }
          --c;
        }//end of for loop
      }
    }
    if(next_mover() == COMPUTER) // then it's the second player's turn
     {
       if(board[row -1][column-1].is_black())
       {
         int c = column-1;
         for(int i = row-1; i >= 0  ; --i)
         {
           if(board[i][c].is_white())
           {
             return legal = true;
           }
           if(board[i][c].is_empty())
           {
             return legal = false;
           }
           c--;
         }//end of for loop
       }
     }
     return legal = false;
  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool Myothello::check_down_left(const int & row, const int & column)const
{
  bool legal;
  if(next_mover() == HUMAN) // then it's the first players turn
  {
    if(board[row+1][column-1].is_white())
    {
      int c = column-1;
      for(int i = row+1; i < 8 ; ++i)
      {
        if(board[i][c].is_black())
        {
          return legal = true;
        }
        if(board[i][c].is_empty())
        {
          return legal = false;
        }
        c--;
      }
    }

    }
  if(next_mover() == COMPUTER) // then it's the second player's turn
  {
    if(board[row+1][column-1].is_black())
    {
      int c = column-1;
      for(int i = row+1; i < 8 ; ++i)
      {
        if(board[i][c].is_white())
        {
          return legal = true;
        }
        if(board[i][c].is_empty())
        {
          return legal = false;
        }
        c--;
      }
    }
  }
  return legal = false;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Myothello::flip_up( int & row,int & column)
{
  if(!check_up(row,column))
  {
    return;
  }
  if(next_mover() == HUMAN)
  {
    for(int i = row-1; i >= 0 ; --i)
    {
      if(board[i][column].is_black())
        return;
      board[i][column].flip();
    }
  }

  if(next_mover() == COMPUTER) // then it's the second player's turn
  {
    for(int i = row-1; i >= 0 ; --i)
    {
      if(board[i][column].is_white())
        return;
      board[i][column].flip();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Myothello::flip_down( int & row,  int & column)
{
  if(!check_down(row,column))
  {
    return;
  }
  if(next_mover() == HUMAN) // then it's the first players turn
  {
    for(int i = row + 1; i < 8  ; ++i)
    {
      if(board[i][column].is_black())
        return;
      board[i][column].flip();
    }
  }

  if(next_mover() == COMPUTER) // then it's the second player's turn
  {
    for(int i = row + 1; i < 8  ; ++i)
      {
        if(board[i][column].is_white())
          return;
        board[i][column].flip();
      }
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Myothello::flip_left(int & row,int & column)
{
  if(!check_left(row,column))
  {
    return;
  }
  if(next_mover() == HUMAN) // then it's the humans turn
  {
    for(int i = column-1; i >= 0 ; --i)
      {
        if(board[row][i].is_black())
          return;
        board[row][i].flip();
      }
    }

  if(next_mover() == COMPUTER) // then it's the computers turn
  {
    for(int i = column-1; i >= 0 ; --i)
    {
      if(board[row][i].is_white())
        return;
      board[row][i].flip();
    }
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Myothello::flip_right(int & row,  int & column)
{
  if(!check_right(row,column))
  {
    return;
  }

  if(next_mover() == HUMAN) // then it's the humans turn
  {
    for(int i = column + 1; i < 8  ; ++i)
    {
      if(board[row][i].is_black())
        return;
      board[row][i].flip();
    }
  }

  if(next_mover() == COMPUTER) // then it's the computers turn
    {
      for(int i = column + 1; i < 8  ; ++i)
        {
          if(board[row][i].is_white())
            return;
          board[row][i].flip();
        }//end of for loop
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Myothello::flip_up_right(int & row,  int & column)
{
  if(!check_up_right(row,column))
  {
    return;
  }
  if(next_mover() == HUMAN) // then it's the humans turn
  {
      int r = row -1;
      for(int i = column + 1; i < 8  ; ++i)
      {
        if(board[r][i].is_black())
          return;
        board[r][i].flip();
        --r;
      }
    }

  if(next_mover() == COMPUTER) // then it's the computers turn
  {
    int r = row -1;
    for(int i = column + 1; i < 8  ; ++i)
    {
      if(board[r][i].is_white())
        return;
      board[r][i].flip();
      --r;
    }//end of for loop
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Myothello::flip_down_right(int & row,  int & column)
{
  if(!check_down_right(row,column))
  {
    return;
  }
  if(next_mover() == HUMAN) // then it's the humans turn
  {
    int r = row +1;
    for(int i = column + 1; i < 8  ; ++i)
    {
      if(board[r][i].is_black())
        return;
      board[r][i].flip();
      ++r;
    }
  }

    if(next_mover() == COMPUTER) // then it's the computers turn
    {
      int r = row +1;
      for(int i = column + 1; i < 8  ; ++i)
      {
        if(board[r][i].is_white())
          return;
        board[r][i].flip();
        ++r;
      }//end of for loop
    }
  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Myothello::flip_up_left(int & row,  int & column)
{
  if(next_mover() == HUMAN) // then it's the humans turn
  {
    if(board[row-1][column - 1].is_white())
    {
      int c = column - 1;
      for(int i = row -1; i >= 0 && c >=0  ; --i)
      {
        if(board[i][c].is_black())
        {
          ++c;
          for(int j = i+1 ; j < row; ++j)
          {
            board[j][c].flip();
            ++c;
          }
          return;
        }
        if(board[i][c].is_empty())
        {
          return;
        }

        --c;
      }//end of for loop
    }
  }//end of if(mover == HUMAN)

    if(next_mover() == COMPUTER) // then it's the computers turn
    {//changed once
      if(board[row-1][column - 1].is_black())
      {
        int c = column - 1;
        for(int i = row -1; i >= 0 && c >=0  ; --i)
        {
          if(board[i][c].is_white())
          {
            ++c;
            for(int j = i+1 ; j < row; ++j)
            {
              board[j][c].flip();
              ++c;
            }
            return;
            }
          if(board[i][c].is_empty())
          {
            return;
          }

          --c;
        }//end of for loop
      }
    }
  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Myothello::flip_down_left(int & row,  int & column)
{// changed once
  if(next_mover() == HUMAN) // then it's the humans turn
  {
    if(board[row+1][column - 1].is_white())
    {
      int c = column - 1;
      for(int i = row+1; i < 8 && c >=0; ++i)
      {
        if(board[i][c].is_black())
        {
          ++c;
          for(int j = i-1 ; j > row; --j)
          {
            board[j][c].flip();
            ++c;
          }
          return;
        }
        if(board[i][c].is_empty())
        {
          return;
        }

        --c;
      }//end of for loop
    }
  }//end of if(mover == HUMAN)

    if(next_mover() == COMPUTER) // then it's the computers turn
    {
      if(board[row+1][column - 1].is_black())
      {
        int c = column - 1;
        for(int i = row+1; i < 8 && c >=0 ; ++i)
        {
          if(board[i][c].is_white())
          {
            ++c;
            for(int j = i-1 ; j > row; --j)
            {
              board[j][c].flip();
              ++c;
            }
            return;
          }
          if(board[i][c].is_empty())
          {
            return;
          }
          --c;
        }//end of for loop
      }
    }//end of if(mover == HUMAN)
  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
bool Myothello::is_game_over( )const
{
  int over = 0;
  int b = 0;
  int w = 0;
  bool is_over;
  if(showC() > 5)
  {
    return is_over = true;
  }
  if(showH() >5)
  {
    return is_over = true;
  }
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      if (board[i][j].is_empty())
      {
        over++;
      }
      if (board[i][j].is_white())
      {
        w++;
      }
      if (board[i][j].is_black())
      {
        b++;
      }

    }
  }
  if(over == 0)
  return is_over  = true;

  else if(w == 0)
  return is_over  = true;

  else if(b == 0)
  return is_over  = true;

  else if(showH() == 2)
  return is_over  = true;

  else if(showC() == 2)
  return is_over  = true;

  else
  return is_over = false;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
Myothello::who Myothello::winning( ) const
{
  who winner;
  int b = 0;
  int w = 0;
  for (int i = 0; i < 8; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      if (board[i][j].is_black())
      {
        b++;
      }
      if (board[i][j].is_white())
      {
        w++;
      }
    }
  }
  if(b > w)
  {
    winner = HUMAN;
  }
  else if( b < w)
  {
    winner = COMPUTER;

  }
  else if(b == 0)
  {
    winner = COMPUTER;
  }
  else if(w == 0)
  {
    winner = HUMAN;
  }
  else
  winner = NEUTRAL;

  std::cout << winner <<" is the winner" << '\n';
  std::cout << "white has:"<< w << '\n';
  std::cout << "black has"<< b << '\n';
  return winner;

}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Myothello::compute_moves(std::queue<std::string>& moves) const
{
  char c;
  string m = "  ";
  int move_count;
  for ( c = 'A'; c < 'I' ; ++c)
  {
    for( char i = '1'; i < '9'; ++i)
    {
    m[0] = c;
    m[1] = i;
    if(is_legal(m))
      {
      moves.push(m);
      ++ move_count;
      }
    }
  }
  if(move_count == 0)
  {
    std::cout << " no legal moves" << '\n';
    return;
  }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
int Myothello::evaluate( )const
{
  int w = 0;
  int b = 0;
  int best_number = 0;
  for(int i = 0; i < 8; ++i)
  {
    for(int j = 0; j < 8; ++j)
    {
      if(board[i][j].is_white())
        ++w;
      if(board[i][j].is_black())
        ++b;
    }
  }
 best_number = w-b;

return best_number;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
std::string Myothello::get_user_move( ) const
{
  std::queue<std::string>  moves;
  string answer;
  compute_moves(moves);
  if(moves.empty())
  {
    return answer = "0";
  }
	display_message("Your move, please: ");
	getline(cin, answer);
	return answer;
//////////////////////////////////////////////////////////////////////////////

}





















}//end of namespace wrap
