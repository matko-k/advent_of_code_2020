#include "day5.h"
#include <regex>

void Day5::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_5_input.txt");
  std::vector<std::string> values;
  std::vector<int> rows;
  std::vector<int> columns;
  std::vector<int> seat_IDs;

  for(std::string value; std::getline(file, value);)
  {
    values.push_back(value);
    int row = 0;
    int column = 0;
    for(int i = 0; i < value.size(); i++)
    {
      if(i<7)
      {
        if(value[i] == 'B')
        {
          row += pow(2,6-i);
        }
      }
      else
      {
        if(value[i] == 'R')
        {
          column += pow(2, 9 - i);
        }
      }
    }
    rows.push_back(row);
    columns.push_back(column);
    seat_IDs.push_back(row*8 + column);
  }
  file.close();

  std::sort(seat_IDs.begin(), seat_IDs.end());
  std::set<int> seat_IDs_set (seat_IDs.begin(), seat_IDs.end());
  seat_IDs.assign(seat_IDs_set.begin(), seat_IDs_set.end());

  int my_seat_ID;

  for(int i = 1; i < 127; i++)
  {
    for(int j = 0; j<8; j++)
    {
      int my_seat_ID = i*8 + j;
      bool minus_1 = std::count(seat_IDs.begin(), seat_IDs.end(), my_seat_ID - 1);
      bool plus_1 = std::count(seat_IDs.begin(), seat_IDs.end(), my_seat_ID + 1);
      bool isnt_there = !std::count(seat_IDs.begin(), seat_IDs.end(), my_seat_ID);
      //std::cout<<minus_1<<plus_1<<isnt_there<<std::endl;
      if( minus_1 && plus_1 && isnt_there) std::cout<<"My seat ID: "<<my_seat_ID<<std::endl;

    }
  }
  std::cout<<"Highest seat ID: "<<seat_IDs[seat_IDs.size()-1]<<std::endl;

}