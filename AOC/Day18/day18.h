#ifndef DAY18_DAY18_H
#define DAY18_DAY18_H
#include "../Day_super/Day.h"


class Day18 : Day {

public:
    Day18(std::string task_description) : Day(task_description){};

    void calculate();

    std::string evaluate_expression_1(std::string expression);
    std::string evaluate_expression_2(std::string expression);
    long calculate_line_1(std::string expression);
    long calculate_line_2(std::string expression);
};


#endif //DAY18_DAY18_H
