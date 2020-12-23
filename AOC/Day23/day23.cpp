#include "day23.h"

void Day23::calculate()
{
  std::vector<long> my_input = {2,8,4,5,7,3,9,6,1};
  std::vector<long> test = {3,8,9,1,2,5,4,6,7};
  std::vector<long> input = my_input;
  std::unordered_map<long, Cup*> cups_map;
  long N = 1000000;
  long moves = 10000000;

  std::vector<Cup*> cups;

  Cup* cup = new Cup();
  cup->value = input.front();
  cups.push_back(cup);

  for(int i = 0; i < input.size()-1; i++)
  {
    cup = new Cup();
    cup->value = input[i+1];
    cups[i]->next_cup = cup;
    cups.push_back(cup);
  }

  for(int i = 10; i <= N; i++)
  {
    cup = new Cup();
    cup->value = i;
    cups[i-2]->next_cup = cup;
    cups.push_back(cup);
  }

  cups.back()->next_cup = cups[0];

  for(Cup* c : cups)
  {
     cups_map[c->value] = c;
  }
  Cup* current_cup = cups.front();

  while(moves > 0)
  {
    Cup* cup1 = current_cup->next_cup;
    Cup* cup2 = cup1->next_cup;
    Cup* cup3 = cup2->next_cup;
    current_cup->next_cup = cup3->next_cup;

    long destination = get_next_value(current_cup->value, N);
    while(destination==cup1->value || destination==cup2->value || destination==cup3->value)
    {
      destination = get_next_value(destination, N);
    }

    Cup* destination_cup = cups_map[destination];

    cup3->next_cup = destination_cup->next_cup;
    cup2->next_cup = cup3;
    cup1->next_cup = cup2;
    destination_cup->next_cup = cup1;

    current_cup = current_cup->next_cup;
    moves--;
  }

  std::string result1 = "";
  while (true)
  {
    if(current_cup->value == 1)
    {
      break;
    }
    current_cup = current_cup->next_cup;
  }

  while(current_cup->next_cup->value != 1)
  {
    result1+=std::to_string(current_cup->next_cup->value);
    current_cup = current_cup->next_cup;
  }
  long result2 = current_cup->next_cup->next_cup->value * current_cup->next_cup->next_cup->next_cup->value;

  //std::cout<<"Result 1: "<<result1<<std::endl;
  std::cout<<"Result 2: "<<result2<<std::endl;
}


long Day23::get_next_value(long i, long N)
{
  return i == 1 ? N : i - 1;
}

