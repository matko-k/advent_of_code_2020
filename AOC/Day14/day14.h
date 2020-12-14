#ifndef DAY14_DAY14_H
#define DAY14_DAY14_H
#include "../Day_super/Day.h"


class Day14 : Day {

public:
    Day14(std::string task_description) : Day(task_description){};

    long long decipher(std::string mask, long long entry);
    std::vector<long long> decipher2(std::string mask, long long entry);
    void calculate();
};


#endif //DAY14_DAY14_H
