/*
** menu.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Sat Feb 21 17:48:10 2015 Nathan Poirier
** Last update Sun Feb 22 14:08:11 2015 Nathan Poirier
*/

#include "allum.h"

void		menu_loop_play_keyslist(t_data *data)
{
  if (data->menu.cur >= 2 && data->menu.cur < 6)
    {
      if (tc_iskey(data, 3, 27, 91, 68) &&
	  data->menu.players[data->menu.cur - 2] > 0)
	data->menu.players[data->menu.cur - 2]--;
      else if (tc_iskey(data, 3, 27, 91, 67) &&
	       data->menu.players[data->menu.cur - 2] <
	       ((data->menu.cur - 2 < 2) ? 1 : 2))
	data->menu.players[data->menu.cur - 2]++;
    }
  if (data->menu.cur == 1)
    {
      if (tc_iskey(data, 3, 27, 91, 68) && data->menu.nblines > 0)
	data->menu.nblines--;
      else if (tc_iskey(data, 3, 27, 91, 67) && data->menu.nblines <
	       OPT_LINES_3MAX- 1)
	data->menu.nblines++;
    }
  if (data->menu.cur == 6)
    {
      if (tc_iskey(data, 3, 27, 91, 68) && data->menu.difficulty > 0)
	data->menu.difficulty--;
      else if (tc_iskey(data, 3, 27, 91, 67) && data->menu.difficulty < 1)
	data->menu.difficulty++;
    }
}

int		menu_loop_play_keys(t_data *data)
{
  if (tc_iskey(data, 1, 27) || tc_iskey(data, 1, 127))
    return (1);
  if (tc_iskey(data, 3, 27, 91, 65) && data->menu.cur > 0)
    data->menu.cur--;
  else if (tc_iskey(data, 3, 27, 91, 66) && data->menu.cur < 6)
    data->menu.cur++;
  if (data->menu.cur == 0 &&
      (tc_iskey(data, 1, 10) || tc_iskey(data, 1, 32)))
    {
      if (game_reset(data) == -1 || game_start(data) == -1)
	return (-1);
    }
  menu_loop_play_keyslist(data);
  return (0);
}

int		menu_loop_play(t_data *data)
{
  int		r;

  data->menu.players[0] = 0;
  data->menu.players[1] = 1;
  data->menu.players[2] = 2;
  data->menu.players[3] = 2;
  while (data->is_running)
    {
      data->menu.phase = 1;
      if (menu_draw(data) == -1)
	return (-1);
      if (tc_readkey(data) == -1)
	return (-1);
      r = menu_loop_play_keys(data);
      if (r == -1)
	return (-1);
      if (r == 1)
	{
	  data->menu.cur = 0;
	  return (0);
	}
    }
  data->menu.cur = 0;
  return (0);
}

int		menu_loop(t_data *data)
{
  while (data->is_running)
    {
      data->menu.phase = 0;
      if (menu_draw(data) == -1)
	return (-1);
      if (tc_readkey(data) == -1)
	return (-1);
      if (tc_iskey(data, 3, 27, 91, 65) && data->menu.cur > 0)
	data->menu.cur--;
      else if (tc_iskey(data, 3, 27, 91, 66) && data->menu.cur < 1)
	data->menu.cur++;
      else if (tc_iskey(data, 1, 10) || tc_iskey(data, 1, 32))
	{
	  if (data->menu.cur == 0 && menu_loop_play(data) == -1)
	    return (-1);
	  else if (data->menu.cur == 1)
	    allum_exit(NULL);
	}
      else if (tc_iskey(data, 1, 27) || tc_iskey(data, 1, 127))
	allum_exit(NULL);
    }
  return (0);
}
