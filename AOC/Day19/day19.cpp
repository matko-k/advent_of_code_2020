#include "day19.h"

void Day19::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_19_input.txt");
  std::unordered_map<int, Rule> rules;
  std::vector<std::string> inputs;

  for(std::string line; std::getline(file, line);)
  {
    if(line.find(':') != std::string::npos)
    {
      Rule rule;
      if(line.find('"') != std::string::npos)
      {
        rule = get_rule_char(line);
      }
      else if(line.find('|') != std::string::npos)
      {
        rule = get_rule_sub_piped(line);
      }
      else
      {
        rule = get_rule_sub(line);
      }

      rules[rule.rule_ID] = rule;
    }
    else if(!line.empty())
    {
      inputs.push_back(line);
    }
  }

  std::vector<std::string> matching_1;

  for(std::string input : inputs)
  {
    int match_size = 0;
    bool matches = matches_rules(input, rules, 0, match_size);
    if (matches && match_size == input.size())
    {
      matching_1.push_back(input);
    }
  }

  Rule rule;
  rule.type = RuleType::SUB_RULES_PIPED;

  rule.rule_ID = 8;
  rule.rule_1 = {42};
  rule.rule_2 = {42, 8};
  rules[rule.rule_ID] = rule;

  rule.rule_ID = 11;
  rule.rule_1 = {42, 31};
  rule.rule_2 = {42, 11, 31};
  rules[rule.rule_ID] = rule;

  std::unordered_map<std::string, bool> matching_2;

  for(int n = 0; n < 10; n++)
    for(int m = 0; m <= n; m++)
  {
    Rule rule_zero;
    rule_zero.type = RuleType::SUB_RULES;
    rule_zero.rule_ID = 0;
    rule_zero.rule_1.push_back(42);
    for(int i = 0; i <= n; i++)
    {
      rule_zero.rule_1.push_back(42);
    }
    for(int i = 0; i < m; i++)
    {
      rule_zero.rule_1.push_back(31);
    }
    rule_zero.rule_1.push_back(31);
    rules[0] = rule_zero;

    std::vector<std::string> current_matches = {};
    for (std::string input : inputs) {
      int match_size = 0;
      bool matches = matches_rules(input, rules, 0, match_size);
      if (matches && match_size == input.size()) {
        matching_2[input] = true;
      }
    }
  }

  std::cout<<"Result 1: "<<matching_1.size()<<std::endl;
  std::cout<<"Result 2: "<<matching_2.size()<<std::endl;
}

Rule Day19::get_rule_char(std::string line)
{
  Rule rule;
  rule.type = RuleType::CHARACTER;
  int pos1 = line.find(":");
  rule.rule_ID = stoi(line.substr(0, pos1));
  int pos2 = line.find('"');
  rule.character = line[pos2+1];

  return rule;
}

Rule Day19::get_rule_sub(std::string line)
{
  Rule rule;
  rule.type = RuleType::SUB_RULES;
  int pos1 = line.find(":");
  rule.rule_ID = stoi(line.substr(0, pos1));

  std::stringstream ss(line.substr(pos1 + 2));
  std::string num;
  while(getline(ss, num, ' '))
  {
    rule.rule_1.push_back(stoi(num));
  }

  return rule;
}

Rule Day19::get_rule_sub_piped(std::string line)
{
  Rule rule;
  rule.type = RuleType::SUB_RULES_PIPED;
  int pos1 = line.find(":");
  rule.rule_ID = stoi(line.substr(0, pos1));

  int pos2 = line.find("|");
  std::stringstream ss(line.substr(pos1 + 2, pos2 - pos1 -2));
  std::string num;
  while(getline(ss, num, ' '))
  {
    rule.rule_1.push_back(stoi(num));
  }

  std::stringstream ss2(line.substr(pos2 + 2));
  while(getline(ss2, num, ' '))
  {
    rule.rule_2.push_back(stoi(num));
  }
  return rule;
}

bool Day19::matches_rules(const std::string& line, std::unordered_map<int, Rule>& rules, int rule_number, int& match_size)
{

  Rule rule = rules[rule_number];

  if(rule.type == RuleType::CHARACTER)
  {
    return line[match_size++] == rule.character;
  }

  int saved_match_size = match_size;

  if(rule.type == SUB_RULES)
  {
    for(int rule_num : rules[rule_number].rule_1)
    {
      if(!matches_rules(line, rules, rule_num, match_size))
      {
        return false;
      }
    }
    return true;
  }
  else
  {
    bool matches = true;

    for(int rule_num : rules[rule_number].rule_1)
    {
      if(!matches_rules(line, rules, rule_num, match_size))
      {
        matches = false;
        break;
      }
    }

    if(!matches) {
      match_size = saved_match_size;
      matches = true;
      for (int rule_num : rules[rule_number].rule_2) {
        if (!matches_rules(line, rules, rule_num, match_size)) {
          matches = false;
          break;
        }
      }
    }
    return matches;
  }
}