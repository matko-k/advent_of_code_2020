#include "day18.h"

void Day18::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_18_input.txt");

  long result1 = 0;
  long result2 = 0;
  for(std::string line; std::getline(file, line);)
  {
    result1 += stol(evaluate_expression_1(line));
    result2 += stol(evaluate_expression_2(line));
  }

  std::cout<<"Result 1: " << result1 << std::endl;
  std::cout<<"Result 2: " << result2 << std::endl;
}

bool isNumeric(std::string str) {
  for (int i = 0; i < str.length(); i++)
    if (isdigit(str[i]) == false)
      return false;
  return true;
}

std::string Day18::evaluate_expression_1(std::string expression)
{
  if(expression.find('(') != std::string::npos)
  {
    std::string::iterator it1;
    for(it1 = expression.begin(); it1 != expression.end(); it1++)
    {
      if(*it1 == '(' && *(it1+1)!= '(') break;
    }
    std::string::iterator it2;
    int count = 0;
    for(it2 = it1+1; it2 != expression.end(); it2++)
    {
      if(*it2 == '(') count ++;
      if(*it2 == ')')
      {
        if(count == 0) break;
        else count--;
      }
    }
    std::string new_expression = std::string(it1 + 1, it2);
    std::string ex = evaluate_expression_1(new_expression);
    std::string reconstructed = "";
    reconstructed = std::string(expression.begin(), it1);
    reconstructed += ex;
    reconstructed += std::string(it2+1, expression.end());
    return evaluate_expression_1(reconstructed);
  }

  return std::to_string(calculate_line_1(expression));
}

std::string Day18::evaluate_expression_2(std::string expression)
{
  if(expression.find('(') != std::string::npos)
  {
    std::string::iterator it1;
    for(it1 = expression.begin(); it1 != expression.end(); it1++)
    {
      if(*it1 == '(' && *(it1+1)!= '(') break;
    }
    std::string::iterator it2;
    int count = 0;
    for(it2 = it1+1; it2 != expression.end(); it2++)
    {
      if(*it2 == '(') count ++;
      if(*it2 == ')')
      {
        if(count == 0) break;
        else count--;
      }
    }
    std::string new_expression = std::string(it1 + 1, it2);
    std::string ex = evaluate_expression_2(new_expression);
    std::string reconstructed = "";
    reconstructed = std::string(expression.begin(), it1);
    reconstructed += ex;
    reconstructed += std::string(it2+1, expression.end());
    return evaluate_expression_2(reconstructed);
  }

  return std::to_string(calculate_line_2(expression));
}

long Day18::calculate_line_1(std::string expression)
{
  long result = 0;
  std::string current = "+";

  std::stringstream ss(expression);
  std::string symbol;
  while(getline(ss, symbol, ' '))
  {
    if (isNumeric(symbol)) {
      if (current == "+") result += stol(symbol);
      else result *= stol(symbol);
    }
    if (symbol == "+" || symbol == "*") current = symbol;
  }
  return result;
}
long Day18::calculate_line_2(std::string expression)
{
  if(expression.find('+') != std::string::npos)
  {
    long temp_sum = 0;
    std::string current = "+";
    std::string new_expression = "";
    std::stringstream ss(expression);
    std::string symbol;

    while (getline(ss, symbol, ' ')) {
      if (isNumeric(symbol)) {
        if (current == "+") {
          temp_sum += stol(symbol);
        } else {
          new_expression += std::to_string(temp_sum) + " * ";
          temp_sum = stol(symbol);
        }
      }
      if (symbol == "+" || symbol == "*") current = symbol;
    }
    new_expression += std::to_string(temp_sum);
    return calculate_line_2(new_expression);
  }
  else {
    std::string current = "+";
    long result = 0;
    std::stringstream ss(expression);
    std::string symbol;
    while (getline(ss, symbol, ' ')) {
      if (isNumeric(symbol)) {
        if (current == "+") result += stol(symbol);
        else result *= stol(symbol);
      }
      if (symbol == "+" || symbol == "*") current = symbol;
    }
    return result;
  }
}