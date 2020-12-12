#ifndef DAY12_DAY12_H
#define DAY12_DAY12_H
#include "../Day_super/Day.h"


class Day12 : Day {

struct Command{
    char action;
    double value;
};

struct Ship{
    double x;
    double y;
    double theta;

    void rotate(double delta_theta)
    {
      theta += delta_theta;
    }

    void move (double delta_x, double delta_y)
    {
      x += delta_x;
      y += delta_y;
    }

    void move_forward(double dist)
    {
      x += dist*cos(theta*M_PI/180);
      y += dist*sin(theta*M_PI/180);
    }

};

struct ShipWithWaypoint{
    Ship ship;
    double waypoint_x;
    double waypoint_y;

    void rotate(double theta)
    {
      double theta_r = theta*M_PI/180;
      double old_x = waypoint_x;
      double old_y = waypoint_y;
      waypoint_x = old_x * cos(theta_r) - old_y * sin(theta_r);
      waypoint_y = old_x * sin(theta_r) + old_y * cos(theta_r);
    }

    void move (double delta_x, double delta_y)
    {
      waypoint_x += delta_x;
      waypoint_y += delta_y;
    }

    void move_forward(double dist)
    {
      ship.x += dist*waypoint_x;
      ship.y += dist*waypoint_y;
    }
};
public:
    Day12(std::string task_description) : Day(task_description){};

    void calculate();
};


#endif //DAY12_DAY12_H
