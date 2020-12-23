#ifndef DAY23_DAY23_H
#define DAY23_DAY23_H
#include "../Day_super/Day.h"

struct Cup
{
    long value;
    Cup* next_cup;
};

class Day23 : Day {

public:
    Day23(std::string task_description) : Day(task_description){};

    void calculate();

    long get_next_value(long i, long N);

};


#endif //DAY23_DAY23_H
