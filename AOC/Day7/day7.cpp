#include "day7.h"
#include <regex>


void Day7::calculate()
{

  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_7_input.txt");
  bag_index = {};
  for(std::string line; std::getline(file, line);)
  {
    std::stringstream parser;

    parser << line;

    std::string current_bag_name, new_bag_pattern, new_bag_color;

    parser >> new_bag_pattern;
    parser >> new_bag_color;

    current_bag_name = new_bag_pattern + " " + new_bag_color;

    parser.ignore(13);

    Bag *current_bag;
    if(bag_index.find(current_bag_name) == bag_index.end())
    {
      current_bag = new Bag(current_bag_name);
      bag_index[current_bag_name] = current_bag;
    }
    else
    {
      current_bag = bag_index[current_bag_name];
    }

    int amount;
    parser >> amount;
    if(parser.fail())
    {
      parser.clear();
      continue;
    }

    while (parser)
    {
      parser >> new_bag_pattern;
      parser >> new_bag_color;
      std::string new_bag_name = new_bag_pattern + " " + new_bag_color;
      parser.ignore(6);

      current_bag->contains_bag(new_bag_name, amount);
      if(bag_index.find(new_bag_name) == bag_index.end())
      {
        Bag *new_bag = new Bag(new_bag_name);
        bag_index[new_bag_name] = new_bag;
      }
      bag_index[new_bag_name]->add_container(current_bag_name);

      parser>>amount;
      if(parser.fail())
      {
        parser.clear();
        break;
      }
    }
  }

  std::cout << "Amount of registered bags: " << bag_index.size() << "\n";

  file.close();



  std::unordered_map<std::string, int> unique_containers{};
  auto direct_containers = bag_index["shiny gold"]->bags_this_one_is_contained_in;
  auto direct_contained = bag_index["shiny gold"]->contained_bags;
  check_uniques(direct_containers, unique_containers);

  std::cout << "Answer 1: " << unique_containers.size() << std::endl;
  std::cout << "Answer 2: " << check_nesting(direct_contained) << std::endl;
}