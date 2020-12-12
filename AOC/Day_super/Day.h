#ifndef DAY_DAY_H
#define DAY_DAY_H
#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <sstream>
#include <bits/stdc++.h>
#include <regex>

class Day
{
public:

    Day(std::string task_description)
    {
      task_description_ = task_description;
    }

    virtual void calculate() = 0;

private:

    std::string task_description_;
};
#endif //DAY_DAY_H
