#ifndef DAY22_DAY22_H
#define DAY22_DAY22_H
#include "../Day_super/Day.h"


class Day22 : Day {

public:
    Day22(std::string task_description) : Day(task_description){};

    void calculate();

    std::string get_game_status(const std::vector<int>& deck1, const std::vector<int>& deck2);

    int get_recursive_combat_winner(std::vector<int>& player1_deck, std::vector<int>& player2_deck);
};


#endif //DAY22_DAY22_H
