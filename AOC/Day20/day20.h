#ifndef DAY20_DAY20_H
#define DAY20_DAY20_H
#include "../Day_super/Day.h"

struct Tile{
    long ID;
    std::unordered_map<int, std::string> sides;
    std::vector<std::string> image;
};

class Day20 : Day {

public:
    Day20(std::string task_description) : Day(task_description){};

    void calculate();

    bool check_tiles_around(int i, int j, std::vector<Tile>& unordered_tiles , std::vector<std::vector<int>>& placed_tiles);

    bool tile_fits(int i, int j, std::vector<Tile>& unordered_tiles , std::vector<std::vector<int>>& placed_tiles);

    void flip_tile(std::vector<Tile>& unordered_tiles, int pos);

    void flip_image(std::vector<std::string>& image);

    void rotate_tile(std::vector<Tile>& unordered_tiles, int pos);

    void rotate_image(std::vector<std::string>& image);

    std::vector<std::string> cut_sides(std::vector<Tile>& unordered_tiles , std::vector<std::vector<int>>& placed_tiles);

    std::vector<std::pair<int,int>> create_monster();

private:
    int side_;
};


#endif //DAY20_DAY20_H
