#include "day2.h"
#include <regex>

void day2::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_2_input.txt");
  std::vector<std::string> values;

  for(std::string value; std::getline(file, value);)
  {
    values.push_back(value);
  }
  file.close();

  std::regex regex("([0-9]*)-([0-9]*) ([a-z]|[A-Z]|[0-9]): (.*)");
  std::smatch matches;
  int valid_passes = 0;
  int valid_passes2 = 0;

  // part 1
  for(std::string s: values)
  {
    if(std::regex_search(s, matches, regex)) {
      int low = std::stoi(matches[1].str());
      int high = std::stoi(matches[2].str());
      char token = matches[3].str()[0];
      std::string pass = matches[4].str();


      int count = 0;

      for (char c : pass) {
        if(c == token)
        {
          count++;
        }
      }

      if(count >= low && count <= high)
      {
        valid_passes++;
      }

      if(pass.size() < low || pass.size() < high) continue;

      if(pass[low-1] == token && pass[high-1] != token){
        valid_passes2++;
        continue;
      }

      if(pass[low-1] != token && pass[high-1] == token){
        valid_passes2++;
        continue;
      }
    }
  }

  std::cout << "Valid passes 1: " << valid_passes<<std::endl;
  std::cout << "Valid passes 2: " << valid_passes2<<std::endl;
}