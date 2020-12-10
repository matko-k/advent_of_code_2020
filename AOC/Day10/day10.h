#ifndef DAY10_DAY10_H
#define DAY10_DAY10_H
#include "../Day_super/Day.h"


class Day10 : Day {

public:
    Day10(std::string task_description) : Day(task_description){};

    void calculate();
    void abracadabra(std::vector<int> joltages, double &count);
    std::vector<bool> find_joltages(const std::vector<int>& joltages);
};


#endif //DAY10_DAY10_H
