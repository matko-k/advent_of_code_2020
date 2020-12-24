#include "day24.h"

void Day24::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_24_input.txt");
  int days = 100;

  std::vector<std::vector<std::string>> directions;
  for(std::string line; std::getline(file, line);)
  {
    std::string current_direction = "";
    std::vector<std::string> line_of_directions;
    for(char c : line)
    {
      if(c == 'e' || c == 'w')
      {
        current_direction.push_back(c);
        line_of_directions.push_back(current_direction);
        current_direction = "";
      }
      else
      {
        current_direction.push_back(c);
      }
    }
    directions.push_back(line_of_directions);
    line_of_directions.clear();
  }

  int max_length = 0;
  for(std::vector<std::string> dir : directions)
  {
    max_length = std::max(max_length, (int)dir.size());
  }

  max_length = 100;

  std::vector<std::vector<bool>> tiles;
  tiles.resize(4*max_length);
  for(std::vector<bool>& tile_row : tiles)
  {
    tile_row.resize(4*max_length, false);
  }

  const int start_x = 2*max_length;
  const int start_y = 2*max_length;

  for(std::vector<std::string> direction_line : directions)
  {
    int current_x = 0;
    int current_y = 0;

    for(std::string direction : direction_line)
    {
      if(direction == "e")
      {
        current_x += 2;
      }
      else if(direction == "w")
      {
        current_x += -2;
      }
      else if(direction == "ne")
      {
        current_x += 1;
        current_y += 1;
      }
      else if(direction == "se")
      {
        current_x += 1;
        current_y += -1;
      }
      else if(direction == "nw")
      {
        current_x += -1;
        current_y += 1;
      }
      else if(direction == "sw")
      {
        current_x += -1;
        current_y += -1;
      }
    }
    tiles[start_x+current_x][start_y+current_y] = !tiles[start_x+current_x][start_y+current_y];
  }


  int result1 = 0;
  for(std::vector<bool> tile_row : tiles)
    for(bool tile : tile_row)
    {
      if(tile) result1++;
    }

  while(days > 0)
  {
    std::vector<std::vector<bool>> tiles_snap = tiles;

    for(int i = 0; i < tiles_snap.size(); i++)
      for(int j = 0; j < tiles_snap[i].size(); j++)
      {
        int count = count_adjacent(tiles, i, j);
        if(tiles[i][j])
        {
          if(count == 0 || count > 2)
            tiles_snap[i][j] = false;
        }
        else
        {
          if(count == 2)
            tiles_snap[i][j] = true;
        }
      }

    tiles = tiles_snap;
    days--;
  }

  int result2 = 0;
  for(std::vector<bool> tile_row : tiles)
    for(bool tile : tile_row)
    {
      if(tile) result2++;
    }
  std::cout<<"Result 1: "<<result1<<std::endl;
  std::cout<<"Result 2: "<<result2<<std::endl;
}

int Day24::count_adjacent(const std::vector<std::vector<bool>>& tiles, int i, int j)
{
  int max_i = tiles.size();
  int max_j = tiles[0].size();

  int count = 0;

  if(i+2 < max_i)
    if(tiles[i+2][j])
      count++;
  if(i-2 >= 0)
    if(tiles[i-2][j])
      count++;
  if(i+1 < max_i && j+1 < max_j)
    if(tiles[i+1][j+1])
      count++;
  if(i+1 < max_i && j-1 >= 0)
    if(tiles[i+1][j-1])
      count++;
  if(i-1 >= 0 && j+1 < max_j)
    if(tiles[i-1][j+1])
      count++;
  if(i-1 >= 0 && j-1 >= 0)
    if(tiles[i-1][j-1])
      count++;

  return count;
}