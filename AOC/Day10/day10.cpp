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

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  abracadabra(joltages, count);

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  std::cout<<"Total ways: "<<count<<std::endl;
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;


}


void Day10::abracadabra(std::vector<int> joltages, double &count)
{
  if(joltages.size() < 2)
  {
    count++;
    return;
  }
  std::vector<bool> valid_joltages = find_joltages(joltages);

  for(int i = 0; i < valid_joltages.size(); i++)
  {
    if(valid_joltages[i])
    {
      std::vector<int> new_joltages;
      switch (i) {
        case 0:
          new_joltages = joltages;
          new_joltages.pop_back();
          abracadabra(new_joltages, count);
          break;
        case 1:
          new_joltages = joltages;
          new_joltages.pop_back();
          new_joltages.pop_back();
          abracadabra(new_joltages, count);
          break;
        case 2:
          new_joltages = joltages;
          new_joltages.pop_back();
          new_joltages.pop_back();
          new_joltages.pop_back();
          abracadabra(new_joltages, count);
          break;
        default:
          break;
      }
    }
  }

  return;
}

std::vector<bool> Day10::find_joltages(const std::vector<int>& joltages)
{
  int diff1, diff2, diff3;
  std::vector<bool> valid_joltages {};

  switch (joltages.size()) {
    case 2:
      diff1 = joltages[joltages.size()-1] - joltages[joltages.size()-2];
      valid_joltages.push_back(diff1 < 4);
      break;

    case 3:
      diff1 = joltages[joltages.size()-1] - joltages[joltages.size()-2];
      diff2 = joltages[joltages.size()-1] - joltages[joltages.size()-3];
      valid_joltages.push_back(diff1 < 4);
      valid_joltages.push_back(diff2 < 4);
      break;

    default:
      diff1 = joltages[joltages.size()-1] - joltages[joltages.size()-2];
      diff2 = joltages[joltages.size()-1] - joltages[joltages.size()-3];
      diff3 = joltages[joltages.size()-1] - joltages[joltages.size()-4];
      valid_joltages.push_back(diff1 < 4);
      valid_joltages.push_back(diff2 < 4);
      valid_joltages.push_back(diff3 < 4);
  }

  return valid_joltages;
}
