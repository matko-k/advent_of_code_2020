#ifndef DAY4_DAY4_H
#define DAY4_DAY4_H
#include "../Day_super/Day.h"

class Day4 : Day {
struct Passport{
    std::string byr;
    std::string iyr;
    std::string eyr;
    std::string hgt;
    std::string hcl;
    std::string ecl;
    std::string pid;
    std::string cid;
};
public:
    Day4(std::string task_description) : Day(task_description){};
    void calculate();
    bool checkPassport(Passport passport);
    bool checkPassport_advanced(Passport passport);
};


#endif //DAY4_DAY4_H
