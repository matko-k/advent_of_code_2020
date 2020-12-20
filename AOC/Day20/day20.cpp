#include "day20.h"

void Day20::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_20_input.txt");

  std::vector<Tile> unordered_tiles;
  Tile new_tile;
  int count = 0;
  std::string last_line;
  for(std::string line; std::getline(file, line);)
  {
    if(line.empty())
    {
      new_tile.sides[1] = last_line;
      unordered_tiles.push_back(new_tile);
      count = 0;
      new_tile.image.clear();
    }

    else if(line.find("Tile") != std::string::npos)
    {
      new_tile.ID = stol(line.substr(4, line.size()-5));
    }

    else {
      if (count == 0) {
        new_tile.sides[0] = line;
        new_tile.sides[2] = line[0];
        new_tile.sides[3] = line[line.size() - 1];
      }
      else {
        new_tile.sides[2] += line[0];
        new_tile.sides[3] += line[line.size() - 1];
      }
      count++;
      last_line = line;
      new_tile.image.push_back(line);
    }
  }

  new_tile.sides[1] = last_line;
  unordered_tiles.push_back(new_tile);

  Tile test;
  test.sides[0] = "12";
  test.sides[1] = "12";
  test.sides[2] = "12";
  test.sides[3] = "12";
  test.image.push_back("ab");
  test.image.push_back("cd");
  std::vector<Tile> testt;
  testt.push_back(test);
  rotate_tile(testt, 0);

  side_ = sqrt(unordered_tiles.size());
  std::vector<std::vector<int>> placed_tiles;
  placed_tiles.resize(side_, {});
  for(std::vector<int>& v : placed_tiles)
  {
    v.resize(side_, -1);
  }

  bool success = check_tiles_around(0, 0, unordered_tiles, placed_tiles);

  long result1 = 1;

  if(success)
  {
   result1 *= unordered_tiles[placed_tiles[0][0]].ID;
   result1 *= unordered_tiles[placed_tiles[side_ - 1][0]].ID;
   result1 *= unordered_tiles[placed_tiles[0][side_ - 1]].ID;
   result1 *= unordered_tiles[placed_tiles[side_ - 1][side_ - 1]].ID;
  }

  for(int i = 0; i < unordered_tiles.size(); i++)
  {
    rotate_tile(unordered_tiles, i);
    flip_tile(unordered_tiles, i);
  }
  std::vector<std::string> final_image = cut_sides(unordered_tiles, placed_tiles);

  std::vector<std::pair<int,int>> sea_monster = create_monster();

  int monster_length = 20;
  int monster_width = 3;
  int monster_count = 0;
  int turn_count = 0;
  while(monster_count == 0 && turn_count < 8) {
    for (int i = 0; i < final_image.size() - monster_width; i++) {
      for (int j = 0; j < final_image.size() - monster_length; j++) {
        bool monster_found = true;
        for (std::pair<int, int> coordinate : sea_monster) {
          if (final_image[i + coordinate.second][j + coordinate.first] != '#') {
            monster_found = false;
            break;
          }
        }
        if (monster_found) {
          monster_count++;
          for (std::pair<int, int> coordinate : sea_monster)
            final_image[i + coordinate.second][j + coordinate.first] = '0';
        }
      }
    }

    if(turn_count == 3)
    {
      flip_image(final_image);
      turn_count++;
    }
    else{
      rotate_image(final_image);
      turn_count++;
    }
  }
  int result2 = 0;
  for(std::string line : final_image)
    for(char c : line)
    if(c == '#') result2++;

  std::cout<<"Result 1: "<<result1<<std::endl;
  std::cout<<"Result 2: "<<result2<<std::endl;
}

bool Day20::check_tiles_around(int i, int j, std::vector<Tile>& unordered_tiles, std::vector<std::vector<int>>& placed_tiles)
{
  if(i >= side_) return true;

  if(j >= side_) return check_tiles_around(i+1, 0, unordered_tiles, placed_tiles);

  for(int count = 0; count < unordered_tiles.size(); count++)
  {
    if(placed_tiles[i][j] > 0) continue;

    placed_tiles[i][j] = count;

    for(int flips = 0; flips < 2; flips++) {
      for(int rotations = 0; rotations < 4; rotations++) {
        if (!tile_fits(i, j, unordered_tiles, placed_tiles)) {
          rotate_tile(unordered_tiles, count);
          continue;
        }

        bool next_fits = check_tiles_around(i, j + 1, unordered_tiles, placed_tiles);
        if (!next_fits) {
          rotate_tile(unordered_tiles, count);
          continue;
        }
        return true;
      }
      flip_tile(unordered_tiles, count);
    }
    placed_tiles[i][j] = -1;
  }

  return false;
}

bool Day20::tile_fits(int i, int j, std::vector<Tile>& unordered_tiles , std::vector<std::vector<int>>& placed_tiles)
{
  if(!(i == 0 || unordered_tiles[placed_tiles[i][j]].sides[2] == unordered_tiles[placed_tiles[i-1][j]].sides[3])) return false;
  if(!(j == 0 || unordered_tiles[placed_tiles[i][j]].sides[0] == unordered_tiles[placed_tiles[i][j-1]].sides[1])) return false;

  return true;
}

void Day20::flip_tile(std::vector<Tile>& unordered_tiles, int pos)
{
  Tile tile = unordered_tiles[pos];

  std::swap(tile.sides[2], tile.sides[3]);

  int n = tile.sides[0].length();
  for(int i = 0; i < n/2; i++)
  {
    std::swap(tile.sides[0][i], tile.sides[0][n - 1 -i]);
    std::swap(tile.sides[1][i], tile.sides[1][n - 1 -i]);
  }

  flip_image(tile.image);

  unordered_tiles[pos] = tile;
}

void Day20::rotate_tile(std::vector<Tile>& unordered_tiles, int pos)
{
  Tile tile = unordered_tiles[pos];

  std::swap(tile.sides[0], tile.sides[3]);
  std::swap(tile.sides[0], tile.sides[1]);
  std::swap(tile.sides[0], tile.sides[2]);

  int n = tile.sides[0].length();
  for(int i = 0; i < n/2; i++)
  {
    std::swap(tile.sides[0][i], tile.sides[0][n - 1 -i]);
    std::swap(tile.sides[1][i], tile.sides[1][n - 1 -i]);
  }

  rotate_image(tile.image);
  unordered_tiles[pos] = tile;
}

std::vector<std::string> Day20::cut_sides(std::vector<Tile>& unordered_tiles , std::vector<std::vector<int>>& placed_tiles)
{
  std::vector<std::string> final_image;

  int n = unordered_tiles[0].image[0].length();
  for(int i = 0; i < side_; i++)
  {
    for(int k = 1; k < n - 1; k++)
    {
      std::string image_line = "";
      for(int j = 0; j < side_; j++)
      {
        image_line += unordered_tiles[placed_tiles[i][j]].image[k].substr(1, n-2);
      }
      final_image.push_back(image_line);
    }
  }

  return final_image;
}

std::vector<std::pair<int,int>> Day20::create_monster()
{
  std::vector<std::pair<int,int>> monster;
  monster.push_back(std::make_pair(18, 0));
  monster.push_back(std::make_pair(0, 1));
  monster.push_back(std::make_pair(5, 1));
  monster.push_back(std::make_pair(6, 1));
  monster.push_back(std::make_pair(11, 1));
  monster.push_back(std::make_pair(12, 1));
  monster.push_back(std::make_pair(17, 1));
  monster.push_back(std::make_pair(18, 1));
  monster.push_back(std::make_pair(19, 1));
  monster.push_back(std::make_pair(1, 2));
  monster.push_back(std::make_pair(4, 2));
  monster.push_back(std::make_pair(7, 2));
  monster.push_back(std::make_pair(10, 2));
  monster.push_back(std::make_pair(13, 2));
  monster.push_back(std::make_pair(16, 2));

  return monster;
}

void Day20::flip_image(std::vector<std::string>& image)
{
  int n = image.size();
  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n/2; j++)
    {
      std::swap(image[i][j], image[i][n - 1 -j]);
    }
  }
}

void Day20::rotate_image(std::vector<std::string> &image)
{

  std::vector<std::string> new_image = image;
  int n = image.size();
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    {
      new_image[i][j] = image[n - 1 -j][i];
    }

  image = new_image;
}