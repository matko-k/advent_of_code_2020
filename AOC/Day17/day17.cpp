#include "day17.h"

void Day17::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_17_input.txt");
  int N = 6;
  CubeSpace cube_space;
  HyperCubeSpace hypercube_space;
  int y = 0;
  for(std::string line; std::getline(file, line);)
  {
    int x = 0;
    for(char c : line)
    {

      Cube cube;
      cube.x = x;
      cube.y = y;
      cube.z = 0;
      cube.status = c;

      HyperCube hypercube;
      hypercube.x = x;
      hypercube.y = y;
      hypercube.z = 0;
      hypercube.w = 0;
      hypercube.status = c;

      cube_space.cubes.push_back(cube);
      hypercube_space.hypercubes.push_back(hypercube);

      x++;
    }
    y++;
  }

  for(int n = 0; n < N; n++)
  {

    cube_space.expand();

    std::vector<Cube> temp_cubes = {};

    for(Cube cube : cube_space.cubes)
    {
      std::vector<Cube> neighbours = {};
      for(int i = -1; i < 2; i++)
        for(int j = -1; j < 2; j++)
          for(int k = -1; k < 2; k++)
          {
            if(i == 0 && j == 0 && k == 0) continue;
            Cube to_be_inspected = cube_space.get_cube(cube.x + i, cube.y + j, cube.z + k);
            if(to_be_inspected.status == '!')
            {
              //std::cout<<"INVALID"<<std::endl;
              continue;
            }
            neighbours.push_back(to_be_inspected);
          }

      int active_neighbours = 0;
      for(Cube neighbour : neighbours)
      {
        if(neighbour.is_active()) active_neighbours++;
      }

      if(cube.is_active())
      {
        if(active_neighbours < 2 || active_neighbours > 3) cube.status = '.';
      }
      else
      {
        if(active_neighbours == 3) cube.status = '#';
      }

      temp_cubes.push_back(cube);
    }

    cube_space.cubes = temp_cubes;

  }

  //part 2
  for(int n = 0; n < N; n++) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    hypercube_space.expand();

    std::vector<HyperCube> temp_hypercubes = {};


    for (HyperCube hypercube : hypercube_space.hypercubes) {
      std::vector<HyperCube> neighbours = {};
      for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++)
          for (int k = -1; k < 2; k++)
            for (int l = -1; l < 2; l++) {
              if (i == 0 && j == 0 && k == 0 && l == 0) continue;
              HyperCube to_be_inspected = hypercube_space.get_hypercube(hypercube.x + i, hypercube.y + j,
                                                                        hypercube.z + k, hypercube.w + l);
              if (to_be_inspected.status == '!') {
                continue;
              }
              neighbours.push_back(to_be_inspected);
            }

      int active_neighbours = 0;
      for (HyperCube neighbour : neighbours) {
        if (neighbour.is_active()) active_neighbours++;
      }

      if (hypercube.is_active()) {
        if (active_neighbours < 2 || active_neighbours > 3) hypercube.status = '.';
      } else {
        if (active_neighbours == 3) hypercube.status = '#';
      }

      temp_hypercubes.push_back(hypercube);
    }

    hypercube_space.hypercubes = temp_hypercubes;
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout<<"Cycle: "<<n+1<<" finished."<<std::endl;
    std::cout << "Cycle duration = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;
  }


  int result1 = 0;
  for(Cube cube : cube_space.cubes)
  {
    if(cube.is_active()) result1++;
  }

  int result2 = 0;
  for(HyperCube hypercube : hypercube_space.hypercubes)
  {
    if(hypercube.is_active()) result2++;
  }

  std::cout<<"Result 1: "<<result1<<std::endl;

  std::cout<<"Result 2: "<<result2<<std::endl;


}