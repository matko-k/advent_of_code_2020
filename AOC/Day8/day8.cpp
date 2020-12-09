#include "day8.h"
#include <regex>

void Day8::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_8_input.txt");


  for(std::string line; std::getline(file, line);) {
    std::stringstream parser;

    parser << line;

    std::string command;
    std::string value;

    parser >> command;
    parser >> value;

    Command current_command;
    current_command.command = command;
    current_command.value = stoi(value);
    current_command.visited = false;

    commands.push_back(current_command);

  }

  execute_program(commands);

  for(Command& command : commands)
  {
    switch_command(&command);

    if(execute_program(commands))
    {
      std::cout<<"Terminated!"<<std::endl;
      break;
    }
    switch_command(&command);
  }
}

bool Day8::execute_program(std::vector<Command> commands)
{
  int command_index = 0;
  int accumulator = 0;
  bool terminated = true;

  while(command_index < commands.size())
  {
    if(commands[command_index].visited)
    {
      terminated = false;
      break;
    }
    std::string current_command = commands[command_index].command;
    if(current_command == "acc")
    {
      accumulator += commands[command_index].value;
      //std::cout<<"Accumulator + "<<commands[command_index].value<<" = "<<accumulator<<std::endl;
      commands[command_index].visited = true;
      command_index++;
    }
    else if(current_command == "jmp")
    {
      commands[command_index].visited = true;
      command_index += commands[command_index].value;
      //std::cout<<"Jumping "<<commands[command_index].value<<std::endl;

    }
    else if(current_command == "nop")
    {
      //std::cout<<"Nope :)"<<std::endl;
      commands[command_index].visited = true;
      command_index++;
      continue;
    }
    else{
      std::cout<<"Unknown command!"<<std::endl;
      terminated = false;
      break;
    }
  }

  std::cout<<"Final accumulator value = "<<accumulator<<std::endl;//
  return terminated;
}

void Day8::switch_command(Command *command)
{
  if(command->command == "jmp")
  {
    command->command = "nop";
    return;
  }
  if(command->command == "nop")
  {
    command->command = "jmp";
    return;
  }
}