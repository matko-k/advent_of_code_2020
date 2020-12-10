#include "day10.h"
#include <regex>
#include <chrono>

void Day10::calculate() {
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_10_input.txt");

  std::vector<int> joltages;
  joltages.push_back(0);
  for (std::string value; std::getline(file, value);) {
    joltages.push_back(stoi(value));
  }

  std::sort(joltages.begin(), joltages.end());

  int ones_count = 0;
  int twos_count = 0;
  int threes_count = 0;
  int current_joltage = 0;
  bool invalid_adapters = false;

  for (int i = 1; i < joltages.size();)
  {
    if (joltages[i] - current_joltage == 1) {
      ones_count++;
      i++;
      current_joltage += 1;
      continue;
    }
    if (joltages[i] - current_joltage == 2) {
      twos_count++;
      i++;
      current_joltage += 2;
      continue;
    }
    if (joltages[i] - current_joltage == 3) {
      threes_count++;
      i++;
      current_joltage += 3;
      continue;
    }
    invalid_adapters = true;
    break;
  }

  threes_count++;
  if (invalid_adapters) {
    std::cout << "Adapters are invalid" << std::endl;
  }
  else
  {
    std::cout << "Ones " << ones_count << std::endl;
    std::cout << "Twos " << twos_count << std::endl;
    std::cout << "Threes " << threes_count << std::endl;
    std::cout<< "Ones times Threes = "<<ones_count*threes_count<<std::endl;
  }

  double count = 0;

  std::vector<int> valid_neighbours = count_valid_neighbours(joltages);

  abracadabra(valid_neighbours, count);

  std::cout << std::fixed;
  std::cout << std::setprecision(20);
  std::cout<<"Total ways : "<<count<<std::endl;

}

void Day10::abracadabra(std::vector<int> joltages, double &count)
{
  double first = joltages[joltages.size()-3];
  double second = joltages[joltages.size()-2];
  double third = joltages[joltages.size()-1];
  double old_first;

  for(int i = joltages.size() - 4; i >= 0; i--)
  {
    if(joltages[i] == 1)
    {
      old_first = first;
      first = first;
      third = second;
      second = old_first;
    }
    if(joltages[i] == 2)
    {
      old_first = first;
      first = first + second;
      third = second;
      second = old_first;
    }
    if(joltages[i] == 3)
    {
      old_first = first;
      first = first + second + third;
      third = second;
      second = old_first;

    }
  }
  count = first;
}

std::vector<int> Day10::count_valid_neighbours(const std::vector<int>& joltages)
{
  std::vector<int> valid_neighbours_count = {};
  for(int i = 0; i < joltages.size() - 3; i++)
  {
    int count = 0;
    if(std::find(joltages.begin()+i+1, joltages.begin()+i+4,joltages[i] + 1) != joltages.begin()+i+4)
    {
      count++;
    }
    if(std::find(joltages.begin()+i+1, joltages.begin()+i+4,joltages[i] + 2) != joltages.begin()+i+4)
    {
      count++;
    }
    if(std::find(joltages.begin()+i+1, joltages.begin()+i+4,joltages[i] + 3) != joltages.begin()+i+4)
    {
      count++;
    }
    valid_neighbours_count.push_back(count);
  }

  int count = 0;
  if(std::find(joltages.end()-2, joltages.end(),joltages[joltages.size()-3] + 1) != joltages.end())
  {
    count++;
  }
  if(std::find(joltages.end()-2, joltages.end(),joltages[joltages.size()-3] + 2) != joltages.end())
  {
    count++;
  }
  if(std::find(joltages.end()-2, joltages.end(),joltages[joltages.size()-3] + 3) != joltages.end())
  {
    count++;
  }
  valid_neighbours_count.push_back(count);
  valid_neighbours_count.push_back(1);
  valid_neighbours_count.push_back(1);

  return valid_neighbours_count;
}
