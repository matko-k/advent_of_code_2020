#ifndef DAY8_DAY8_H
#define DAY8_DAY8_H
#include "../Day_super/Day.h"



class Day8 : Day {
struct Command{
    std::string command;
    int value;
    bool visited;
};
public:
    Day8(std::string task_description) : Day(task_description){};

    void calculate();

    std::vector<Command> commands;
    bool execute_program(std::vector<Command>commands);
    void switch_command(Command *command);
};


#endif //DAY8_DAY8_H
