#include "day15.h"

void Day15::calculate()
{
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  std::string test = "0,3,6";
  std::string input = "8,11,0,19,1,2";

  std::vector<long> starting_numbers;

  std::stringstream ss(input);
  for(long i; ss >> i; )
  {
    starting_numbers.push_back(i);
    if(ss.peek() == ',') ss.ignore();
  }

  std::vector<long> spoken_numbers_turns{};
  int total_turns = 30000000;
  spoken_numbers_turns.resize(total_turns, 0);

  long turn_count = 0;

  for(int i = 0; i < starting_numbers.size() - 1; i++)
  {
    turn_count++;
    spoken_numbers_turns[starting_numbers[i]] = turn_count;
  }

  long last_spoken_number = starting_numbers.back();

  total_turns -= starting_numbers.size();
  
  for(int i = 0; i < total_turns; i++)
  {
    turn_count++;

    int last_spoken_turn = spoken_numbers_turns[last_spoken_number];
    spoken_numbers_turns[last_spoken_number] = turn_count;

    if(last_spoken_turn == 0)
    {
      last_spoken_number = 0;
    }
    else
    {
      last_spoken_number = turn_count - last_spoken_turn;
    }
  }

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout<<"Last spoken: "<<last_spoken_number<<std::endl;
  std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}