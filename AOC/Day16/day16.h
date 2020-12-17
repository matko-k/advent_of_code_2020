#ifndef DAY16_DAY16_H
#define DAY16_DAY16_H
#include "../Day_super/Day.h"


class Day16 : Day {
struct Range{
    int low;
    int high;
};
public:
    Day16(std::string task_description) : Day(task_description){};

    void calculate();
};


#endif //DAY16_DAY16_H
