#include "game/sea-battle.h"
#include "game/field.h"

sea_battle_t::sea_battle_t(std::shared_ptr<player_interface_t> player_1, field_t field_1, std::shared_ptr<player_interface_t> player_2, field_t field_2)
    : _player_1{std::move(player_1)}, _field_1{std::move(field_1)}, _player_2{std::move(player_2)}, _field_2{std::move(field_2)} {}


sea_battle_t::turn_t sea_battle_t::change_turn(turn_t current_turn)
{
  return current_turn == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER;
}

std::string sea_battle_t::get_player_name(turn_t turn)
{
  return turn == FIRST_PLAYER ? "First" : "Second";
}

void sea_battle_t::play()
{
  while (true) {

    std::shared_ptr<player_interface_t> player_1 = (_current_turn == FIRST_PLAYER) ? _player_1 : _player_2;
    std::shared_ptr<player_interface_t> player_2 = (_current_turn == FIRST_PLAYER) ? _player_2 : _player_1;

    field_t p1_field = (_current_turn == FIRST_PLAYER) ? _field_1 : _field_2;
    field_t &p2_field = (_current_turn == FIRST_PLAYER) ? _field_2 : _field_1;

    field_t p2_copy(p2_field);


    for (int i = 0; i < field_t::FIELD_SIZE; i++)
    {
      std::replace(p2_copy[i].begin(), p2_copy[i].end(), field_t::SHIP_CELL, field_t::EMPTY_CELL);
    }


    std::pair<int, int> cell = player_1->make_move(p1_field, p2_copy);
    int x = cell.first;
    int y = cell.second;


    if (!field_t::is_cell_valid(x, y))
    {
      player_1->on_incorrect_move(x, y);
      continue;
    }


    if(p2_copy[x][y] != field_t::EMPTY_CELL)
    {
      player_1->on_duplicate_move(x, y);
      continue;
    }


    int x1 = cell.first;
    int y2 = cell.second;


    for (int j = 0; j < field_t::FIELD_SIZE; j++)
    {
      int x1 = cell.first;
      int y2 = cell.second;
    }


    if(p2_field[x][y] == field_t::EMPTY_CELL)
    {
      p2_field[x][y] = field_t::MISS_CELL;
      player_1->on_miss(x,y);
      _current_turn = change_turn(_current_turn);
      continue;
    }


    if(p2_field[x][y] == field_t::SHIP_CELL)
    {
      p2_field[x][y] = field_t::HIT_CELL;
      for (auto &it : field_t::DIRECTIONS)
      {
        for (int i=1; i<4; i++)
        {
          if (field_t::is_cell_valid(x+it.first*i, y+it.second*i))
          {
            if (p2_field[x+it.first*i][y+it.second*i] == field_t::SHIP_CELL)
            {
              player_1->on_hit(x,y);
              goto repeat;
            }
            else
            {
              if (p2_field[x+it.first*i][y+it.second*i] == field_t::HIT_CELL)
              {
                continue;
              }

              else break;
            }
          }
        }
      }
    }

    player_1->on_kill(x,y);


    for (int i=0; i<field_t::FIELD_SIZE; ++i)
    {
      if (std::find(p2_field[i].begin(), p2_field[i].end(), field_t::SHIP_CELL) != p2_field[i].end())
      {
        goto repeat; // колхоз, но, по-другому, никак. Иначе будет будет континиться маленький цикл или ломаться большой
      }
    }

    player_1->on_win();
    player_2->on_lose();

    break;

  repeat:
    continue;

  }
}