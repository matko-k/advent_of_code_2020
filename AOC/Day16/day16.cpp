#include "day16.h"

void Day16::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_16_input.txt");

  std::vector<std::pair<Range, Range>> ranges;
  std::vector<std::string> range_names;
  std::string line;
  for(line; std::getline(file, line);)
  {
    if(line.empty()) break;

    int it = line.find(":");

    range_names.push_back(line.substr(0, it));

    std::string remaining_line = line.substr(it+2);
    it = remaining_line.find("-");
    std::pair<Range, Range> range;
    range.first.low = stoi(remaining_line.substr(0, it));
    remaining_line = remaining_line.substr(it+1);
    it = remaining_line.find("or");
    range.first.high = stoi(remaining_line.substr(0, it - 1));
    remaining_line = remaining_line.substr(it+3);

    it = remaining_line.find("-");
    range.second.low = stoi(remaining_line.substr(0, it));
    remaining_line = remaining_line.substr(it+1);
    range.second.high = stoi(remaining_line);

    ranges.push_back(range);
  }

  std::getline(file, line);

  std::vector<int> my_ticket;
  std::getline(file, line);
  std::stringstream ss(line);
  std::string num;
  while(getline(ss, num, ','))
  {
    my_ticket.push_back(stoi(num));
  }

  std::getline(file, line);
  std::getline(file, line);

  std::vector<std::vector<int>> tickets;

  for(line; std::getline(file, line);)
  {
    std::stringstream ss(line);
    std::string num;
    std::vector<int> ticket;
    while(getline(ss, num, ','))
    {
      ticket.push_back(stoi(num));
    }
    tickets.push_back(ticket);
  }

  std::vector<int> invalids;

  for(std::vector<std::vector<int>>::iterator it = tickets.begin(); it != tickets.end(); it++)
  {
    bool invalid_ticket = false;
    for(int num : *it)
    {
      bool valid = false;
      for(std::pair<Range, Range> range : ranges)
      {
        if(((num >= range.first.low && num <= range.first.high) || (num >= range.second.low && num <= range.second.high)))
        {
          valid = true;
          break;
        }
      }
      if(!valid)
      {
        invalids.push_back(num);
        invalid_ticket = true;
      }
    }

    if(invalid_ticket) {
      tickets.erase(it);
      it--;
    }
  }

  int sum = 0;

  for(int inv : invalids)
  {
    sum += inv;
  }
  std::cout<<"Result 1: "<<sum<<std::endl;


  //part 2

  std::unordered_map<std::string, std::vector<int>> valid_positions;
  for(int i = 0; i < range_names.size(); i++)
  {
    for(int k = 0; k < my_ticket.size(); k++)
    {
      bool value_valid = true;
      for(int j = 0; j < tickets.size(); j++)
      {
        int num = tickets[j][k];
        std::pair<Range, Range> range = ranges[i];
        if(!((num >= range.first.low && num <= range.first.high) || (num >= range.second.low && num <= range.second.high)))
        {
          value_valid = false;
          break;
        }
      }

      if(value_valid)
      {
        valid_positions[range_names[i]].push_back(k);
      }
    }
  }


  while(true)
  {
    bool map_clear = true;
    for(std::unordered_map<std::string, std::vector<int>>::iterator it = valid_positions.begin(); it != valid_positions.end(); it++)
    {
      if(it->second.size() != 1)map_clear = false;
    }
    if(map_clear){
      break;
    }

    for(std::unordered_map<std::string, std::vector<int>>::iterator it = valid_positions.begin(); it != valid_positions.end(); it++)
    {
      if(it->second.size() == 1)
      {
        for(std::unordered_map<std::string, std::vector<int>>::iterator it2 = valid_positions.begin(); it2 != valid_positions.end(); it2++)
        {
          if(it2->second.size() > 1)
          {
            std::vector<int>::iterator it3 = std::find(it2->second.begin(), it2->second.end(), it->second[0]);
            if(it3 != it2->second.end())
            {
              it2->second.erase(it3);
            }
          }
        }
      }
    }
  }

  long long result = 1;

  for(int i = 0; i < range_names.size(); i++)
  {
    if(range_names[i].find("departure") != std::string::npos)
    {
      result *= (long)my_ticket[valid_positions[range_names[i]][0]];
    }
  }
  std::cout<<"Result 2: "<<result<<std::endl;
}