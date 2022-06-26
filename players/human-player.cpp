#include "players/human-player.h"

std::string human_player_t::get_cell_name(int x, int y)
{
  std::string cell_name = std::to_string(x + 1);
  cell_name += static_cast<char>(65+y);
  return cell_name;
}

std::pair<int, int> human_player_t::make_move(const field_t &my_field, const field_t &enemy_field)
{
  output_stream << "Your field:" << std::endl;
  output_stream << my_field << std::endl;
  output_stream << "Enemy's field" << std::endl;
  output_stream << enemy_field << std::endl;
  output_stream << "Input you turn! [Example 1A or 10B or 6J]" << std::endl;

  std::string s;
  std::getline(input_stream, s);
  std::set<std::string> cells;

  for (int i=1; i<field_t::FIELD_SIZE+1; i++)
  {
    for (char j='A'; j<char(65+field_t::FIELD_SIZE); j++)
    {
      cells.insert(std::to_string(i)+j);
    }
  }
  while (std::find(cells.begin(), cells.end(), s) == cells.end()) {
    output_stream << "Incorrect move! [Correct example 1A or 10B or 6J]" << std::endl;
    std::getline(input_stream, s);
  }
  int x = std::stoi(s.substr(0, s.length()-1))-1;
  int y = s.back() - 65;
  return std::pair{x, y};
}



void human_player_t::on_duplicate_move(int x, int y)
{
  output_stream << get_cell_name(x, y) << " DUPLICATE! Repeat move!" << std::endl;
}

void human_player_t::on_incorrect_move(int x, int y)
{
  assert(false);
}

void human_player_t::on_miss(int x, int y)
{
  output_stream << get_cell_name(x, y) << " MISS! Enemy's turn!" << std::endl;
}

void human_player_t::on_hit(int x, int y)
{
  output_stream << get_cell_name(x, y) << " HIT! Your next move!" << std::endl;
}

void human_player_t::on_win()
{
  output_stream << "You WIN!" << std::endl;
}

void human_player_t::on_kill(int x, int y)
{
  output_stream << get_cell_name(x, y) << " KILL! Your next move!" << std::endl;
}

void human_player_t::on_lose()
{
  output_stream << "You LOSE!" << std::endl;
}