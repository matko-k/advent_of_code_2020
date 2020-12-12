#include "day12.h"

void Day12::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_12_input.txt");

  std::vector<Command> commands;

  for (std::string value; std::getline(file, value);) {
    Command command;
    command.action = value.substr(0, 1)[0];
    command.value = stod(value.substr(1, value.size()-1));
    commands.push_back(command);
  }

  Ship ship;
  ship.x = 0;
  ship.y = 0;
  ship.theta = 0;

  ShipWithWaypoint ship_waypoint;
  Ship ship2;
  ship2.x = 0;
  ship2.y = 0;
  ship2.theta = 0;
  ship_waypoint.ship = ship2;
  ship_waypoint.waypoint_x = 10;
  ship_waypoint.waypoint_y = 1;

  for(Command command : commands)
  {
    switch (command.action) {

      case 'N':
        ship.move(0, command.value);
        ship_waypoint.move(0, command.value);
        break;
      case 'S':
        ship.move(0, -command.value);
        ship_waypoint.move(0, -command.value);
        break;
      case 'E':
        ship.move(command.value, 0);
        ship_waypoint.move(command.value, 0);
        break;
      case 'W':
        ship.move(-command.value, 0);
        ship_waypoint.move(-command.value, 0);
        break;
      case 'L':
        ship.rotate(command.value);
        ship_waypoint.rotate(command.value);
        break;
      case 'R':
        ship.rotate(-command.value);
        ship_waypoint.rotate(-command.value);
        break;
      case 'F':
        ship.move_forward(command.value);
        ship_waypoint.move_forward(command.value);
        break;
      default: std::cout<<"Unknown action"<<std::endl;
    }
  }

  std::cout<<"Part1: Ship pose : "<<ship.x<<" + "<<ship.y<<" = "<<fabs(ship.x) + fabs(ship.y)<<std::endl;

  std::cout<<"Part2: Ship pose : "<<ship_waypoint.ship.x<<" + "<<ship_waypoint.ship.y<<" = "<<fabs(ship_waypoint.ship.x) + fabs(ship_waypoint.ship.y)<<std::endl;


}