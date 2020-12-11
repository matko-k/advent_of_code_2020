#ifndef DAY11_DAY11_H
#define DAY11_DAY11_H
#include "../Day_super/Day.h"


class Day11 : Day {

public:
    Day11(std::string task_description) : Day(task_description){};

    void calculate();

    int count_adjacent(const std::vector<std::string>& seat_rows, const int& x, const int& y);
    std::pair<int, int> count_visible(const std::vector<std::string>& seat_rows, const int& x, const int& y);
    int count_occupied(const std::vector<std::string>& seat_rows);
};


#endif //DAY11_DAY11_H
