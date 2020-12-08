#include "day6.h"
#include <regex>

void Day6::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_6_input.txt");
  std::unordered_set<char> group_answers;
  int answers_sum = 0;
  for(std::string line; std::getline(file, line);) {
    if (!line.empty()) {
      for (char &ch : line) {
        group_answers.insert(ch);
      }
    } else {
      answers_sum += group_answers.size();
      group_answers.clear();
    }
  }
  answers_sum += group_answers.size();

  std::cout<<"Sum of yeses: " << answers_sum << std::endl;

  file.close();

  file.open("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_6_input.txt");
  answers_sum = 0;
  std::vector<char>::iterator it;
  std::vector<char> group_answers_union {};
  bool first_answer = true;
  for(std::string line; std::getline(file, line);) {
    if (!line.empty()) {
      if(first_answer) {
        for (char ch : line) {
          group_answers_union.push_back(ch);
        }
        first_answer = false;
      }
      else
      {
        for (it = group_answers_union.begin(); it != group_answers_union.end(); it++) {
          if(line.find(*it) == std::string::npos)
          {
            group_answers_union.erase(it);
            it--;
          }
        }
      }
    }
    else
      {
      answers_sum += group_answers_union.size();
      group_answers_union.clear();
      first_answer = true;
    }
  }
  answers_sum += group_answers_union.size();

  std::cout<<"Sum of yeses 2: " << answers_sum << std::endl;

  file.close();
}