#ifndef DAY19_DAY19_H
#define DAY19_DAY19_H
#include "../Day_super/Day.h"

enum RuleType{
    CHARACTER = 0,
    SUB_RULES = 1,
    SUB_RULES_PIPED = 2
};

struct Rule {
    int rule_ID;
    RuleType type;
    char character;
    std::vector<int> rule_1;
    std::vector<int> rule_2;
};

class Day19 : Day {

public:


    Day19(std::string task_description) : Day(task_description){};

    void calculate();

    Rule get_rule_char(std::string line);
    Rule get_rule_sub(std::string line);
    Rule get_rule_sub_piped(std::string line);

    bool matches_rules(const std::string& line, std::unordered_map<int, Rule>& rules, int rule_number, int& match_size);
};


#endif //DAY19_DAY19_H
