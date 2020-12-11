#include "day11.h"
#include <regex>

void Day11::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_11_input.txt");
  std::vector<std::string> seat_rows_input;

  for (std::string value; std::getline(file, value);) {
    seat_rows_input.push_back(value);
  }

  std::vector<std::string> seat_rows = seat_rows_input;
  int iteration_count = 0;
  while(true) {
    int changes_count = 0;
    iteration_count++;

    std::vector<std::string> seat_rows_snapshot = seat_rows;

    for (int i = 0; i < seat_rows.size(); i++) {
      for (int j = 0; j < seat_rows[i].size(); j++) {

        if (seat_rows[i][j] == '.') continue;

        int adjacent_count = count_adjacent(seat_rows_snapshot, i, j);

        if (seat_rows[i][j] == 'L' && adjacent_count == 0) {
          seat_rows[i][j] = '#';
          changes_count++;
          continue;
        }
        if (seat_rows[i][j] == '#' && adjacent_count > 3) {
          seat_rows[i][j] = 'L';
          changes_count++;
          continue;
        }
      }
    }

    if(changes_count == 0) break;
  }

  std::cout<<"Process finished after "<<iteration_count<<" iterations"<<std::endl;
  std::cout<<"occupied_seats: "<<count_occupied(seat_rows)<<std::endl;

  //part 2

  seat_rows = seat_rows_input;

  iteration_count = 0;
  while(true) {
    int changes_count = 0;
    iteration_count++;

    std::vector<std::string> seat_rows_snapshot = seat_rows;

    for (int i = 0; i < seat_rows.size(); i++) {
      for (int j = 0; j < seat_rows[i].size(); j++) {

        if (seat_rows[i][j] == '.') continue;

        std::pair<int, int> visible_seats = count_visible(seat_rows_snapshot, i, j);

        if (seat_rows[i][j] == 'L' && visible_seats.first == 0) {
          seat_rows[i][j] = '#';
          changes_count++;
          continue;
        }
        if (seat_rows[i][j] == '#' && visible_seats.first > 4) {
          seat_rows[i][j] = 'L';
          changes_count++;
          continue;
        }
      }
    }

    if(changes_count == 0) break;
  }

  std::cout<<"Process finished after "<<iteration_count<<" iterations"<<std::endl;
  std::cout<<"occupied_seats: "<<count_occupied(seat_rows)<<std::endl;

}

std::pair<int, int> Day11::count_visible(const std::vector<std::string>& seat_rows, const int& i, const int& j)
{
  int count_occupied = 0;
  int count_empty = 0;
  int row_length = seat_rows[i].size();
  int column_length = seat_rows.size();

  std::vector<int> i_modifiers {-1, 0, 1};
  std::vector<int> j_modifiers {-1, 0, 1};

  int current_i = i;
  int current_j = j;

  for(int delta_i : i_modifiers)
  {
    for(int delta_j : j_modifiers)
    {
      if (delta_i == 0 && delta_j == 0) continue;

      int current_i = i;
      int current_j = j;

      current_i += delta_i;
      current_j += delta_j;
      while(current_i >= 0 && current_j >= 0 && current_i < column_length && current_j < row_length)
      {
        if(seat_rows[current_i][current_j] == '#')
        {
          count_occupied++;
          break;
        }
        if(seat_rows[current_i][current_j] == 'L')
        {
          count_empty++;
          break;
        }
        current_i += delta_i;
        current_j += delta_j;
      }

    }
  }

  return std::make_pair(count_occupied, count_empty);

}

int Day11::count_adjacent(const std::vector<std::string>& seat_rows, const int& i, const int& j)
{
  int count = 0;
  int row_length = seat_rows[i].size();
  int column_length = seat_rows.size();
  bool left_most_column = j == 0;
  bool right_most_column = j == row_length - 1;
  bool top_most_row = i == 0;
  bool bottom_most_row = i == column_length - 1;


  if(!left_most_column)
  {
    if(!bottom_most_row)
    {
      if(seat_rows[i+1][j-1] == '#') count++;
    }

    if(seat_rows[i][j-1] == '#') count ++;

    if(!top_most_row)
    {
      if(seat_rows[i-1][j-1] == '#') count++;
    }
  }

  if(!right_most_column)
  {
    if(!bottom_most_row)
    {
      if(seat_rows[i+1][j+1] == '#') count++;
    }

    if(seat_rows[i][j+1] == '#') count ++;

    if(!top_most_row)
    {
      if(seat_rows[i-1][j+1] == '#') count++;
    }
  }

  if(!bottom_most_row)
  {
    if(seat_rows[i+1][j] == '#') count++;
  }
  if(!top_most_row)
  {
    if(seat_rows[i-1][j] == '#') count++;
  }

  return count;
}

int Day11::count_occupied(const std::vector<std::string>& seat_rows)
{
  int count = 0;
  for(std::string row : seat_rows)
  {
    for(char seat : row)
    {
      if(seat == '#') count++;
    }
  }
  return count;
}