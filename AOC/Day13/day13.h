#ifndef DAY13_DAY13_H
#define DAY13_DAY13_H
#include "../Day_super/Day.h"


class Day13 : Day {
struct Shuttle{
    int ID;
    int offset;
};
public:
    Day13(std::string task_description) : Day(task_description){};

    void calculate();
};


#endif //DAY13_DAY13_H
