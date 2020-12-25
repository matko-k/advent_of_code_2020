#include "day25.h"

void Day25::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_25_input.txt");
  std::string line;
  std::getline(file, line);
  long card_public_key = stol(line);
  std::getline(file, line);
  long door_public_key = stol(line);

  long card_loop_size = get_loop_size(7, card_public_key);
  long door_loop_size = get_loop_size(7, door_public_key);

  long encrypted_key = get_encrypted_key(door_public_key, card_loop_size);

  long result1 = encrypted_key;

  std::cout<<"Result 1: "<<result1<<std::endl;


}


long Day25::get_loop_size(long subject_number, long final_value)
{
  long loop_size = 0;
  long value = 1;
  while(value != final_value)
  {
    loop_size++;
    value *= subject_number;
    value = value % divider_;
  }

  return loop_size;
}

long Day25::get_encrypted_key(long subject_number, long loop_size)
{
  long value = 1;
  while(loop_size > 0)
  {
    value *= subject_number;
    value = value % divider_;
    loop_size--;
  }
  return value;
}