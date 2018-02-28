////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************
David Wisniewski
project 6a
this is the implementation file for space
*******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
#include"space.h"
space::space()
{
  white = false;
  black = false;
  blank = true;
}
void space::flip()
{
  if(white == true)
    {
      white = false;
      black = true;
    }
  else if(black == true)
    {
      white = true;
      black = false;
    }
  else
  {
    return;
  }
}
void space::display(const std::ostream& outs)const
{
  std::string output;
  std::string color;
  if(black == true)
  {
    output = FILLED_CIRCLE;
    color = BLUE;
  }
  else if(white == true)
  {
    output = FILLED_CIRCLE;
    color = WHITE;
  }
  else
  {
    output = SQUARE;
    color = GREEN;

  }

      std::cout << color << output << RESET<< " "<< RESET;

}
ostream& operator << (ostream& outs, const space& s)
{
        s.display(outs);
        return outs;
}
