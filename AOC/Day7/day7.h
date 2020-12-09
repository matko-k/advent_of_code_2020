#ifndef DAY7_DAY7_H
#define DAY7_DAY7_H
#include "../Day_super/Day.h"

using bag_pair = std::pair<std::string, int>;
class Day7 : Day {

struct Bag
        {
          std::string name;
          Bag(std::string new_name) : name{new_name} {};

          std::vector<bag_pair> contained_bags;
          std::vector<std::string> container_bags;

          void contains_bag(std::string name, int amount)
          {
            bag_pair bags(name, amount);
            contained_bags.push_back(bags);
          }

          void add_container_bag(std::string bag_name)
          {
            container_bags.push_back(bag_name);
          }
        };

public:
    Day7(std::string task_description) : Day(task_description)
    {
    };

    std::unordered_map<std::string, Bag*> bags_database;
    void calculate();

    void check_containers(std::vector<std::string> containers_list, std::unordered_map<std::string, int> &containers_map)
    {
      for(std::string bag_name : containers_list) {
        containers_map[bag_name]++;
        std::vector<std::string> new_containers_list = bags_database[bag_name]->container_bags;
        check_containers(new_containers_list, containers_map);
      }
    }

    int check_contained(std::vector<bag_pair> bags_list) {
      int sum = 0;
      for (bag_pair bag : bags_list) {
        sum += bag.second;
        auto new_list = bags_database[bag.first]->contained_bags;
        sum += bag.second * check_contained(new_list);
      }
      return sum;
    }

};


#endif //DAY7_DAY7_H
