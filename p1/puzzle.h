#ifndef PUZZLE_H
  #define PUZZLE_H

class Puzzle
{
 public:
  Puzzle(const char grid[][9]);
  bool placeNumber(int, char,char grid[][9] );
  bool checkSquare(int, char,char grid[][9] );
  bool checkRow(int, char,char grid[][9]);
  bool checkCol(int, char,char grid[][9]);
  void solve(char grid[][9]);
  //StackAr<int> possible;
}; // Puzzle class

#endif

