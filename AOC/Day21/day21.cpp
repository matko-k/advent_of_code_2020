#include "day21.h"

void Day21::calculate() {
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_21_input.txt");

  std::vector<Food> all_food;
  for (std::string line; std::getline(file, line);) {
    int pos;
    pos = line.find('(');
    std::stringstream ingredients(line.substr(0, pos));
    std::stringstream allergens(line.substr(pos + 9, line.length() - 1 - pos - 9));
    std::string ingredient;
    std::string allergen;
    Food food;

    while (getline(ingredients, ingredient, ' ')) {
      food.ingredients.push_back(ingredient);
    }
    while (getline(allergens, allergen, ',')) {
      food.allergens.push_back(allergen.substr(1, allergen.size() - 1));
    }
    all_food.push_back(food);
  }

  std::vector<Food> remaining_food = all_food;
  std::unordered_map<std::string, std::string> allergen_mapping;
  find_allergens(remaining_food, allergen_mapping);

  std::vector<std::pair<std::string, std::string>> ingredient_allergen_pairs;

  for(std::pair<std::string, std::string> p : allergen_mapping)
  {
    ingredient_allergen_pairs.push_back(p);
  }

  std::sort(ingredient_allergen_pairs.begin(), ingredient_allergen_pairs.end(), [](std::pair<std::string, std::string>& p1, std::pair<std::string, std::string>& p2)
  {
      return p1.second < p2.second;
  });

  std::vector<std::string> allergenics;

  for (std::pair<std::string, std::string> pair : ingredient_allergen_pairs) {
    allergenics.push_back(pair.first);
  }

  int result1 = 0;

  for (Food food : all_food)
  {
    for (std::string in : food.ingredients)
    {
      if (std::find(allergenics.begin(), allergenics.end(), in) != allergenics.end()) {
        continue;
      }
      result1++;
    }
  }
  std::string result2 = "";

  for(std::string in : allergenics) result2+= in + ",";

  std::cout<<"Result 1: " <<result1<<std::endl;
  std::cout<<"Result 2: " <<std::endl<<result2<<std::endl;
}

bool Day21::find_allergens(std::vector<Food>& remaining_food, std::unordered_map<std::string, std::string>& allergen_mapping)
{

  bool done = true;

  for(Food food : remaining_food)
  {
    if(!food.allergens.empty())
    {
      done = false;
      break;
    }
  }

  if(done)
    return true;

  std::sort(remaining_food.begin(), remaining_food.end(), less_than_food());

  for(Food food : remaining_food) {
    for (std::string ingredient : food.ingredients) {
      for (std::string allergen : food.allergens)
      {
        if(!isValidPair(remaining_food, ingredient, allergen))
        {
          continue;
        }

        std::vector<Food> old_remaining_food = remaining_food;

        removePair(remaining_food, ingredient, allergen);

        if(!find_allergens(remaining_food, allergen_mapping))
        {
          remaining_food = old_remaining_food;
          continue;
        }
        allergen_mapping[ingredient] = allergen;
        return true;
      }
    }
  }
}

bool Day21::isValidPair(std::vector<Food>& remaining_food, const std::string& ingredient, const std::string& allergen)
{
  for(Food f : remaining_food)
  {
    if(std::find(f.allergens.begin(), f.allergens.end(), allergen) != f.allergens.end())
    {
      if(std::find(f.ingredients.begin(), f.ingredients.end(), ingredient) == f.ingredients.end())
        return false;
    }
  }

  return true;
}

void Day21::removePair(std::vector<Food>& remaining_food, const std::string& ingredient, const std::string& allergen)
{
  std::vector<std::string>::iterator it;
  for(Food& f : remaining_food)
  {
    it = std::find(f.allergens.begin(), f.allergens.end(), allergen);
    if(it != f.allergens.end())
      f.allergens.erase(it);
    it = std::find(f.ingredients.begin(), f.ingredients.end(), ingredient);
    if(it != f.ingredients.end())
      f.ingredients.erase(it);
  }
}

void Day21::sortMap(std::unordered_map<std::string, std::string>& allergens_table)
{



}