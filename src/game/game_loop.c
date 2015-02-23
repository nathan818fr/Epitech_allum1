/*
** game_loop.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1/src/game
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Thu Feb 19 14:18:36 2015 Nathan Poirier
** Last update Sun Feb 22 19:44:07 2015 Nathan Poirier
*/

#include "allum.h"

int		game_loop_waitkey(t_data *data)
{
  data->term.read_len = 0;
  while (data->is_running && data->term.read_len == 0)
    {
      if (tc_readkey(data) == -1)
	return (-1);
    }
  return (0);
}

int		game_loop_dead(t_data *data, t_player *player)
{
  player->is_dead = MY_TRUE;
  data->game.cur_phase = 3;
  if ((data->game.cur_infoplayer = player) && game_draw(data) == -1)
    return (-1);
  if (game_loop_waitkey(data) == -1)
    return (-1);
  data->game.cur_phase = 0;
  if ((data->game.cur_infoplayer = game_player_getwinner(data)) != NULL)
    {
      data->game.is_running = MY_FALSE;
      data->game.cur_phase = 4;
      if (game_draw(data) == -1)
	return (-1);
      if (game_loop_waitkey(data) == -1)
	return (-1);
    }
  else if (game_lines_reset(data) == -1)
    return (-1);
  data->game.cur_phase = 0;
  return (0);
}

int		game_loop(t_data *data, t_player *player)
{
  if (player->type == PLAYER_TYPE_KEYBOARD)
    {
      if (game_loop_keyboard_line(data, player) == -1)
	return (-1);
    }
  else
    {
      if (game_loop_computer_line(data, player) == -1)
	return (-1);
    }
  if (game_line_remaining(data, 1) <= 0)
    if (game_loop_dead(data, player) == -1)
      return (-1);
  data->game.cur_phase = 0;
  return (0);
}

int		game_start(t_data *data)
{
  t_game	*game;
  t_my_listitem	*it;
  t_player	*player;

  game = &data->game;
  game->cur_player = 0;
  if (game->players == NULL || game->lines_ == NULL ||
      game->players->size <= 0 || game->lines_->size <= 0)
    return (allum_exit(ERR_BADLISTS) - 1);
  game->is_running = 1;
  if (game_updatesize(data) == -1)
    return (-1);
  while (data->is_running && game->is_running)
    {
      if ((it = my_list_get(game->players, game->cur_player)) == NULL ||
	  it->data == NULL)
	return (allum_exit(ERR_BADPLAYER) - 1);
      player = (t_player *)it->data;
      if (!player->is_dead && game_loop(data, player) == -1)
	return (-1);
      game->cur_player++;
      if (game->cur_player >= game->players->size)
	game->cur_player = 0;
    }
  return (0);
}
