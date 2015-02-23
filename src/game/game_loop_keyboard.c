/*
** game_loop_keyboard.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1/src/game
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Thu Feb 19 14:38:44 2015 Nathan Poirier
** Last update Fri Feb 20 14:26:28 2015 Nathan Poirier
*/

#include "allum.h"

int		game_loop_keyboard_col_key(t_data *data, int *selected,
					   t_line *line)
{
  if (tc_iskey(data, 1, 27) || tc_iskey(data, 1, 127))
    return (0);
  else if (tc_iskey(data, 3, 27, 91, 68))
    {
      data->game.cur_size--;
      if (data->game.cur_size <= 0)
	return (0);
    }
  else if (tc_iskey(data, 3, 27, 91, 67) &&
	   data->game.cur_size < line->count)
    data->game.cur_size++;
  else if (tc_iskey(data, 1, 10) || tc_iskey(data, 1, 32))
    {
      line->count -= data->game.cur_size;
      *selected = 1;
    }
  return (1);
}

int		game_loop_keyboard_col(t_data *data, t_player *player,
				       int *selected)
{
  t_line	*line;
  t_my_listitem	*it;

  if ((it = my_list_get(data->game.lines_, data->game.cur_line)) == NULL ||
      it->data == NULL)
    return (0);
  line = (t_line *)it->data;
  if (line->count <= 0)
    return (0);
  data->game.cur_size = 1;
  while (data->is_running && !(*selected))
    {
      data->game.cur_phase = 2;
      if (game_draw(data) == -1 || tc_readkey(data) == -1)
	return (-1);
      if (game_loop_keyboard_col_key(data, selected, line) == 0)
	return (0);
    }
  return (0);
}

int		game_loop_keyboard_line(t_data *data, t_player *player)
{
  int		selected;

  selected = 0;
  while (data->is_running && !selected)
    {
      data->game.cur_phase = 1;
      if (game_draw(data) == -1)
	return (-1);
      if (tc_readkey(data) == -1)
	return (-1);
      if (tc_iskey(data, 3, 27, 91, 65) && data->game.cur_line > 0)
	data->game.cur_line--;
      else if (tc_iskey(data, 3, 27, 91, 66) &&
	       data->game.cur_line < data->game.lines_->size - 1)
	data->game.cur_line++;
      else if (tc_iskey(data, 3, 27, 91, 67) || tc_iskey(data, 1, 10) ||
	       tc_iskey(data, 1, 32))
	if (game_loop_keyboard_col(data, player, &selected) == -1)
	  return (-1);
    }
  return (0);
}
