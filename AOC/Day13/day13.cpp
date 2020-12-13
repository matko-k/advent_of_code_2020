#include "day13.h"

void Day13::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_13_input.txt");

  std::string line;
  std::getline(file, line);
  int timestamp_earliest = stoi(line);

  std::getline(file,line);
  std::stringstream shuttles_stream(line);
  std::string shuttle_item;

  std::vector<Shuttle> shuttles;
  int offset = -1;

  while(std::getline(shuttles_stream, shuttle_item, ','))
  {
    offset ++;
    if(shuttle_item == "x") continue;

    Shuttle shuttle;
    shuttle.ID = stoi(shuttle_item);
    shuttle.offset = offset;
    shuttles.push_back(shuttle);
  }

  int closest_shuttle = -1;
  int closest_time_diff = timestamp_earliest;
  for(Shuttle shuttle : shuttles)
  {
    if(shuttle.ID > 1)
    {
      int cumulative_timestamp = 0;
      while(cumulative_timestamp < timestamp_earliest)
      {
        cumulative_timestamp += shuttle.ID;
      }
      if(cumulative_timestamp - timestamp_earliest < closest_time_diff)
      {
        closest_time_diff = cumulative_timestamp - timestamp_earliest;
        closest_shuttle = shuttle.ID;
      }
    }
  }

  std::cout<<"Closest shuttle: "<<closest_shuttle<<" @"<<timestamp_earliest + closest_time_diff<<" ,mine is: "<<timestamp_earliest<<std::endl;
  std::cout<<"Answer: "<<closest_shuttle*closest_time_diff<<std::endl;

  long current_timestamp = 0;
  long current_cycle = 1;

  for(Shuttle shuttle : shuttles)
  {
    while((current_timestamp + shuttle.offset) % shuttle.ID != 0)
    {
      current_timestamp += current_cycle;
    }
    current_cycle *= shuttle.ID;
  }

  std::cout<<"Desired timestamp: "<<current_timestamp<<std::endl;

}