#ifndef DAY24_DAY24_H
#define DAY24_DAY24_H
#include "../Day_super/Day.h"


class Day24 : Day {

public:
    Day24(std::string task_description) : Day(task_description){};

    void calculate();

    int count_adjacent(const std::vector<std::vector<bool>>& tiles, int i, int j);
};


#endif //DAY24_DAY24_H
