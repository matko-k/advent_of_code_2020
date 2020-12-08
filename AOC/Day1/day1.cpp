#include "day1.h"

void Day1::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_1_input.txt");
  std::vector<int> values;

  for(std::string value; std::getline(file, value);)
  {
    values.push_back(stoi(value));
  }

  file.close();
  bool found = false;

  for(int i = 0; i < values.size()-1; i++) {
    for (int j = 0; j < values.size()-1; j++)
    {
      if(i == j) continue;
      if(values[i] + values[j] == 2020)
      {
        found = true;
        std::cout<<"Two values: "<<values[i]<<" + "<<values[j]<<" = "<<values[i]+values[j]<<"| result is "<<values[i]*values[j]<<std::endl;
      }
      if (found) break;
    }
    if (found) break;
  }

  found = false;

  for(int i = 0; i < values.size()-1; i++) {
    for (int j = 0; j < values.size() - 1; j++) {
      for (int k = 0; k < values.size() - 1; k++) {
        if (i == j) continue;
        if (i == k) continue;
        if (j == k) continue;

        if (values[i] + values[j] + values[k] == 2020) {
          found = true;
          std::cout << "Three values: " << values[i] << " + " << values[j] << " + " << values[k] << " = "
                    << values[i] + values[j] + values[k] << "| result is " << values[i] * values[j] * values[k]
                    << std::endl;
        }
        if (found) break;
      }
      if (found) break;
    }
    if (found) break;
  }
}