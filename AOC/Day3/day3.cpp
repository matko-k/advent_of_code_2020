#include "day3.h"
#include <regex>

void day3::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_3_input.txt");
  std::vector<std::string> values;

  for(std::string value; std::getline(file, value);)
  {
    values.push_back(value);
  }
  file.close();
  int row_length = values[0].size();
  int tree_count = 0;
  std::vector<int> tree_counts {0, 0, 0, 0, 0};
  std::vector<int> slopes_column {1, 3, 5, 7, 1};
  std::vector<int> slopes_row {1, 1, 1, 1, 2};
  int column_index = 0;
  int row_index = 1;
  while (row_index < values.size())
  {
      column_index = (column_index + 3) % row_length;

      if(values[row_index].c_str()[column_index] == '#')
      {
        tree_count++;
      }
      row_index++;

  }

  for (int i = 0; i < 5; i++)
  {
    int column_index = 0;
    int row_index = 0;
    while (row_index < values.size()-1)
    {
      column_index = (column_index + slopes_column[i]) % row_length;
      row_index+=slopes_row[i];
      if(values[row_index].c_str()[column_index] == '#')
      {
        tree_counts[i]++;
      }
      }
  }
  std::cout << "Tree count " << tree_count<<std::endl;
  int result = 1;
  for (int count : tree_counts)
  {
    result *= count;
  }
  std::cout << "Result " << result<<std::endl;

}