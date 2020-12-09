#include "day9.h"
#include <regex>

void Day9::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_9_input.txt");
  std::vector<long> values;
  int window = 25;
  long broken_element;
  for(std::string value; std::getline(file, value);)
  {
    values.push_back(stol(value));
  }

  for(int i = window; i < values.size(); i++)
  {
    bool found_one = false;
    for(int j = i-window; j < i; j++)
    {
      int diff = values[i] - values[j];
      std::vector<long>::iterator it;
      it = std::find(values.begin() + j, values.begin()+j+window+1, diff);
      if(*it != values[j] && it != values.begin()+j+window+1){
        found_one = true;
        //std::cout<<values[i]<< " = " <<values[j]<< " + " << *it<<std::endl;
        break;
      }
    }
    if(!found_one)
    {
      std::cout<<"Broken element: "<<values[i]<<std::endl;
      broken_element = values[i];
      break;
    }
    else
    {

    }
  }
  int sum;
  bool found_sum = false;
  for(int i = 0; i < values.size(); i++)
  {
    sum = 0;
    if (found_sum)
    {
      break;
    }
    for(int j = i; j < values.size(); j++)
    {
      sum += values[j];
      if(sum == broken_element)
      {
        found_sum = true;
        std::cout<<"XMAS number: "<<*max_element(values.begin()+i, values.begin()+j+1) + *min_element(values.begin()+i, values.begin()+j+1)<<std::endl;
        break;
      }
    }
  }
}