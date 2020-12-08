#ifndef DAY4_DAY4_H
#define DAY4_DAY4_H
#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <fstream>
#include <string>
#include <vector>


class day4 {
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
    void calculate();
    bool checkPassport(Passport passport);
    bool checkPassport_advanced(Passport passport);
};


#endif //DAY4_DAY4_H
