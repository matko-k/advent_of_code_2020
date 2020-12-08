#ifndef DAY7_DAY7_H
#define DAY7_DAY7_H
#include "../Day_super/Day.h"

using bag_pair = std::pair<std::string, int>;
class Day7 : Day {

struct Bag
        {
          std::vector<bag_pair> contained_bags;
          std::vector<std::string> bags_this_one_is_contained_in;

          std::string name;

          Bag(std::string new_name) : name{new_name} {};

          void contains_bag(std::string name, int amount)
          {
            bag_pair bags(name, amount);
            contained_bags.push_back(bags);
          }

          void add_container(std::string name)
          {
           bags_this_one_is_contained_in.push_back(name);
          }
        };

public:
    Day7(std::string task_description) : Day(task_description)
    {
    };

    std::unordered_map<std::string, Bag*> bag_index;
    void calculate();

    void check_uniques(std::vector<std::string> container_list, std::unordered_map<std::string, int> &unique_list)
    {
      for (auto bag_name : container_list) {
        ++unique_list[bag_name];
        auto new_list = bag_index[bag_name]->bags_this_one_is_contained_in;
        check_uniques(new_list, unique_list);
      }
    }

    int check_nesting(std::vector<bag_pair> bag_list) {
      int local_sum{0};
      for (auto b : bag_list) {
        local_sum += b.second;
        auto new_list = bag_index[b.first]->contained_bags;
        local_sum += b.second * check_nesting(new_list);
      }
      return local_sum;
    }

};


#endif //DAY7_DAY7_H
