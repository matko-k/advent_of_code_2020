#ifndef DAY25_DAY25_H
#define DAY25_DAY25_H
#include "../Day_super/Day.h"


class Day25 : Day {

public:
    Day25(std::string task_description) : Day(task_description){};

    void calculate();

    long get_loop_size(long subject_number, long final_value);

    long get_encrypted_key(long subject_number, long loop_size);

private:
    const long divider_ = 20201227;
};


#endif //DAY25_DAY25_H
