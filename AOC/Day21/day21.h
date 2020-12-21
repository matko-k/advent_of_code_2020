#ifndef DAY21_DAY21_H
#define DAY21_DAY21_H
#include "../Day_super/Day.h"

struct Food
{
    std::vector<std::string> ingredients;
    std::vector<std::string> allergens;
};

struct less_than_food
{
    inline bool operator() (const Food& food1, const Food& food2)
    {
      return ((food1.ingredients.size()+food1.allergens.size()) < (food2.ingredients.size() + food2.allergens.size()));
    }
};


class Day21 : Day {

public:
    Day21(std::string task_description) : Day(task_description){};

    void calculate();

    bool find_allergens(std::vector<Food>& remaining_food, std::unordered_map<std::string, std::string>& allergen_table);

    bool isValidPair(std::vector<Food>& remaining_food, const std::string& ingredient, const std::string& allergen);

    void removePair(std::vector<Food>& remaining_food, const std::string& ingredient, const std::string& allergen);

    void sortMap(std::unordered_map<std::string, std::string>& allergens_table);
};


#endif //DAY21_DAY21_H
