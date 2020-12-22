#include "day22.h"

void Day22::calculate()
{
  std::ifstream file("/home/incubed/AdventOfCode/advent_of_code_2020/AOC/sources/day_22_input.txt");
  std::vector<int> player1_deck;
  std::vector<int> player2_deck;
  int current_deck = 1;
  for(std::string line; std::getline(file, line);)
  {
    if(line[0] == 'P') continue;
    if(line.empty())
    {
      current_deck = 2;
      continue;
    }

    if(current_deck == 1)
    {
      player1_deck.push_back(stoi(line));
    }
    else
    {
      player2_deck.push_back(stoi(line));
    }
  }

  std::vector<int> player1_deck_saved = player1_deck;
  std::vector<int> player2_deck_saved = player2_deck;

  int round = 0;
  while(!player1_deck.empty() && !player2_deck.empty())
  {
    round++;

    int player1_card = player1_deck.front();
    player1_deck.erase(player1_deck.begin());

    int player2_card = player2_deck.front();
    player2_deck.erase(player2_deck.begin());

    if(player1_card > player2_card)
    {
      player1_deck.push_back(player1_card);
      player1_deck.push_back(player2_card);
    }
    else
    {
      player2_deck.push_back(player2_card);
      player2_deck.push_back(player1_card);
    }
  }

  std::vector<int> winner_deck = player2_deck.empty() ? player1_deck : player2_deck;


  long result1 = 0;
  for(int i = 0; i < winner_deck.size(); i++)
  {
    result1 += winner_deck[i] * (winner_deck.size()-i);
  }

  player1_deck = player1_deck_saved;
  player2_deck = player2_deck_saved;

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  int winner2 = get_recursive_combat_winner(player1_deck, player2_deck);

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  winner_deck = winner2==1 ? player1_deck : player2_deck;

  long result2 = 0;
  for(int i = 0; i < winner_deck.size(); i++)
  {
    result2 += winner_deck[i] * (winner_deck.size()-i);
  }

  std::cout<<"Result 1: "<<result1<<std::endl;
  std::cout<<"Result 2: "<<result2<<std::endl;

  std::cout << "Part 2 duration: " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;

}


std::string Day22::get_game_status(const std::vector<int>& deck1, const std::vector<int>& deck2)
{
  std::string game_status = "";

  for(int card : deck1)
  {
    game_status += std::to_string(card) + "-";
  }
  game_status += "|";

  for(int card : deck2)
  {
    game_status += std::to_string(card) + "-";
  }

  return game_status;
}

int Day22::get_recursive_combat_winner(std::vector<int>& player1_deck, std::vector<int>& player2_deck)
{

  std::vector<std::string> game_statuses;

  int game_winner = 0;
  int round = 0;

  while(true) {
    round++;
    int round_winner = 0;

    if (std::find(game_statuses.begin(), game_statuses.end(), get_game_status(player1_deck, player2_deck)) !=
        game_statuses.end())
    {
      return 1;
    }
    game_statuses.push_back(get_game_status(player1_deck, player2_deck));

    int player1_card = player1_deck.front();
    player1_deck.erase(player1_deck.begin());

    int player2_card = player2_deck.front();
    player2_deck.erase(player2_deck.begin());

    if(player1_deck.size() < player1_card || player2_deck.size() < player2_card)
    {
      round_winner = player1_card > player2_card ? 1 : 2;
    }
    else
    {
      std::vector<int> player1_subdeck;
      std::vector<int> player2_subdeck;
      for(int i = 0; i < player1_card; i++)
      {
        player1_subdeck.push_back(player1_deck[i]);
      }
      for(int i = 0; i < player2_card; i++)
      {
        player2_subdeck.push_back(player2_deck[i]);
      }
      round_winner = get_recursive_combat_winner(player1_subdeck, player2_subdeck);
    }

    if(round_winner == 1)
    {
      player1_deck.push_back(player1_card);
      player1_deck.push_back(player2_card);
    }
    if(round_winner == 2)
    {
      player2_deck.push_back(player2_card);
      player2_deck.push_back(player1_card);
    }

    if(player2_deck.empty())
    {
      return 1;
    }
    if(player1_deck.empty())
    {
      return 2;
    }
  }

}