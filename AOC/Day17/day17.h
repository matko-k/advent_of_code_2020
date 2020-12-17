#ifndef DAY17_DAY17_H
#define DAY17_DAY17_H
#include "../Day_super/Day.h"


class Day17 : Day {
struct Cube
{
    int x;
    int y;
    int z;

    char status;

    bool is_active()
    {
      if(status == '#') return true;
      return false;
    }
};

    struct HyperCube
    {
        int x;
        int y;
        int z;
        int w;

        char status;

        bool is_active()
        {
          if(status == '#') return true;
          return false;
        }
    };

struct CubeSpace {
    std::vector<Cube> cubes;

    Cube get_cube(int x, int y, int z) {
      Cube invalid_cube;
      invalid_cube.status = '!';

      for (Cube cube : cubes) {
        if (cube.x == x && cube.y == y && cube.z == z) return cube;
      }
      return invalid_cube;

    }

    std::vector<int> get_corners() {
      std::vector<int> corners = {INT_MAX, INT_MIN, INT_MAX, INT_MIN, INT_MAX, INT_MIN};
      for (Cube cube : cubes) {
        corners[0] = std::min(corners[0], cube.x);
        corners[1] = std::max(corners[1], cube.x);
        corners[2] = std::min(corners[2], cube.y);
        corners[3] = std::max(corners[3], cube.y);
        corners[4] = std::min(corners[4], cube.z);
        corners[5] = std::max(corners[5], cube.z);
      }

      return corners;
    }


    void expand() {
      std::vector<int> corners = get_corners();

      //bottom
      for (int i = corners[0] - 1; i <= corners[1] + 1; i++) {
        for (int j = corners[2] - 1; j <= corners[3] + 1; j++) {
          Cube cube;
          cube.x = i;
          cube.y = j;
          cube.z = corners[4] - 1;
          cube.status = '.';
          cubes.push_back(cube);
        }
      }

      //top
      for (int i = corners[0] - 1; i <= corners[1] + 1; i++) {
        for (int j = corners[2] - 1; j <= corners[3] + 1; j++) {
          Cube cube;
          cube.x = i;
          cube.y = j;
          cube.z = corners[5] + 1;
          cube.status = '.';
          cubes.push_back(cube);
        }
      }

      //left
      for (int i = corners[2] - 1; i <= corners[3] + 1; i++) {
        for (int j = corners[4]; j <= corners[5]; j++) {
          Cube cube;
          cube.x = corners[0] - 1;
          cube.y = i;
          cube.z = j;
          cube.status = '.';
          cubes.push_back(cube);
        }
      }

      //right
      for (int i = corners[2] - 1; i <= corners[3] + 1; i++) {
        for (int j = corners[4]; j <= corners[5]; j++) {
          Cube cube;
          cube.x = corners[1] + 1;
          cube.y = i;
          cube.z = j;
          cube.status = '.';
          cubes.push_back(cube);
        }
      }

      //front
      for (int i = corners[0]; i <= corners[1]; i++) {
        for (int j = corners[4]; j <= corners[5]; j++) {
          Cube cube;
          cube.x = i;
          cube.y = corners[2] - 1;
          cube.z = j;
          cube.status = '.';
          cubes.push_back(cube);
        }
      }

      //back
      for (int i = corners[0]; i <= corners[1]; i++) {
        for (int j = corners[4]; j <= corners[5]; j++) {
          Cube cube;
          cube.x = i;
          cube.y = corners[3] + 1;
          cube.z = j;
          cube.status = '.';
          cubes.push_back(cube);
        }
      }
    }

    int count_active() {
      int sum = 0;
      for (Cube cube : cubes) {
        if (cube.is_active()) sum++;
      }
      return sum;
    }
};

struct HyperCubeSpace
{
  std::vector<HyperCube> hypercubes;

  HyperCube get_hypercube(int x, int y, int z, int w)
  {
    HyperCube invalid_cube;
    invalid_cube.status = '!';

    for(HyperCube hypercube : hypercubes)
    {
      if(hypercube.x == x && hypercube.y == y  && hypercube.z == z && hypercube.w == w) return hypercube;
    }
    return invalid_cube;

  }
  std::vector<int> get_corners()
  {
    std::vector<int> corners = {INT_MAX, INT_MIN, INT_MAX, INT_MIN, INT_MAX, INT_MIN, INT_MAX, INT_MIN};
    for(HyperCube hypercube : hypercubes)
    {
      corners[0] = std::min(corners[0], hypercube.x);
      corners[1] = std::max(corners[1], hypercube.x);
      corners[2] = std::min(corners[2], hypercube.y);
      corners[3] = std::max(corners[3], hypercube.y);
      corners[4] = std::min(corners[4], hypercube.z);
      corners[5] = std::max(corners[5], hypercube.z);
      corners[6] = std::min(corners[6], hypercube.w);
      corners[7] = std::max(corners[7], hypercube.w);
    }

    return corners;
  }


  void expand() {
    std::vector<int> corners = get_corners();

   //w const
    for (int i = corners[0] - 1; i <= corners[1] + 1; i++) {
      for (int j = corners[2] - 1; j <= corners[3] + 1; j++) {
        for (int k = corners[4] - 1; k <= corners[5] + 1; k++){
          HyperCube hypercube;
          hypercube.x = i;
          hypercube.y = j;
          hypercube.z = k;
          hypercube.w = corners[6] - 1;
          hypercube.status = '.';
          hypercubes.push_back(hypercube);
        }
      }
    }

    //w const
    for (int i = corners[0] - 1; i <= corners[1] + 1; i++) {
      for (int j = corners[2] - 1; j <= corners[3] + 1; j++) {
        for (int k = corners[4] - 1; k <= corners[5] + 1; k++){
          HyperCube hypercube;
          hypercube.x = i;
          hypercube.y = j;
          hypercube.z = k;
          hypercube.w = corners[7] + 1;
          hypercube.status = '.';
          hypercubes.push_back(hypercube);
        }
      }
    }

    //z const
    for (int i = corners[0] - 1; i <= corners[1] + 1; i++) {
      for (int j = corners[2] - 1; j <= corners[3] + 1; j++) {
        for (int k = corners[6]; k <= corners[7]; k++){
          HyperCube hypercube;
          hypercube.x = i;
          hypercube.y = j;
          hypercube.z = corners[4] - 1;
          hypercube.w = k;
          hypercube.status = '.';
          hypercubes.push_back(hypercube);
        }
      }
    }

    //z const
    for (int i = corners[0] - 1; i <= corners[1] + 1; i++) {
      for (int j = corners[2] - 1; j <= corners[3] + 1; j++) {
        for (int k = corners[6]; k <= corners[7]; k++){
          HyperCube hypercube;
          hypercube.x = i;
          hypercube.y = j;
          hypercube.z = corners[5] + 1;
          hypercube.w = k;
          hypercube.status = '.';
          hypercubes.push_back(hypercube);
        }
      }
    }

    //y const
    for (int i = corners[0] - 1; i <= corners[1] + 1; i++) {
      for (int j = corners[4] ; j <= corners[5]; j++) {
        for (int k = corners[6]; k <= corners[7]; k++){
          HyperCube hypercube;
          hypercube.x = i;
          hypercube.y = corners[2] - 1;
          hypercube.z = j;
          hypercube.w = k;
          hypercube.status = '.';
          hypercubes.push_back(hypercube);
        }
      }
    }

    //y const
    for (int i = corners[0] - 1; i <= corners[1] + 1; i++) {
      for (int j = corners[4] ; j <= corners[5]; j++) {
        for (int k = corners[6]; k <= corners[7]; k++){
          HyperCube hypercube;
          hypercube.x = i;
          hypercube.y = corners[3] + 1;
          hypercube.z = j;
          hypercube.w = k;
          hypercube.status = '.';
          hypercubes.push_back(hypercube);
        }
      }
    }

    //x const
    for (int i = corners[2]; i <= corners[3]; i++) {
      for (int j = corners[4] ; j <= corners[5]; j++) {
        for (int k = corners[6]; k <= corners[7]; k++){
          HyperCube hypercube;
          hypercube.x = corners[0] - 1;
          hypercube.y = i;
          hypercube.z = j;
          hypercube.w = k;
          hypercube.status = '.';
          hypercubes.push_back(hypercube);
        }
      }
    }


    //x const
    for (int i = corners[2]; i <= corners[3]; i++) {
      for (int j = corners[4] ; j <= corners[5]; j++) {
        for (int k = corners[6]; k <= corners[7]; k++){
          HyperCube hypercube;
          hypercube.x = corners[1] + 1;
          hypercube.y = i;
          hypercube.z = j;
          hypercube.w = k;
          hypercube.status = '.';
          hypercubes.push_back(hypercube);
        }
      }
    }
  }

  int count_active()
  {
    int sum = 0;
    for(HyperCube hypercube : hypercubes)
    {
      if(hypercube.is_active()) sum++;
    }
    return sum;
  }

};
public:
    Day17(std::string task_description) : Day(task_description){};

    void calculate();
};


#endif //DAY17_DAY17_H
