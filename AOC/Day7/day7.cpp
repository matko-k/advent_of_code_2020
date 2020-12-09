#include "day7.h"
#include <regex>


void Day7::calculate()
{

  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_7_input.txt");
  bags_database = {};
  for(std::string line; std::getline(file, line);)
  {
    std::stringstream parser;

    parser << line;

    std::string new_bag_pattern;
    std::string new_bag_color;

    parser >> new_bag_pattern;
    parser >> new_bag_color;

    std::string current_bag_name = new_bag_pattern + " " + new_bag_color;

    Bag *current_bag;
    if(bags_database.find(current_bag_name) == bags_database.end())
    {
      current_bag = new Bag(current_bag_name);
      bags_database[current_bag_name] = current_bag;
    }
    else
    {
      current_bag = bags_database[current_bag_name];
    }

    parser.ignore(13);
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
      if(bags_database.find(new_bag_name) == bags_database.end())
      {
        Bag *new_bag = new Bag(new_bag_name);
        bags_database[new_bag_name] = new_bag;
      }
      bags_database[new_bag_name]->add_container_bag(current_bag_name);

      parser>>amount;
      if(parser.fail())
      {
        parser.clear();
        break;
      }
    }
  }

  std::cout << "Amount of registered bags: " << bags_database.size() << "\n";

  file.close();



  std::unordered_map<std::string, int> containers{};
  auto direct_containers = bags_database["shiny gold"]->container_bags;
  auto direct_contained = bags_database["shiny gold"]->contained_bags;
  check_containers(direct_containers, containers);

  std::cout << "Shiny gold containers: " << containers.size() << std::endl;


  std::cout << "Bags contained in shiny gold: " << check_contained(direct_contained) << std::endl;
}