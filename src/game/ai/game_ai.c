/*
** game_ai.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Sat Feb 21 12:37:17 2015 Nathan Poirier
** Last update Sat Feb 21 20:28:07 2015 Nathan Poirier
*/

#include "allum.h"

int		game_ai(t_data *data, t_player *player, int *tomake)
{
  if (data->menu.difficulty == 1)
    return (game_ai_random(data, player, tomake));
  return (game_ai_best(data, player, tomake));
}

int		game_ai_random(t_data *data, t_player *player,
			       int *tomake)
{
  int		i;
  t_line	*line;
  int		nb;
  int		dir;

  i = 0;
  nb = rand() % data->game.lines_->size;
  dir = (rand() % 2 == 0) ? 1 : -1;
  while (dir != 0 &&
	 (line = (t_line *)my_list_get(data->game.lines_, nb)->data) &&
	 i < data->game.lines_->size + 1)
    {
      if (line->count > 0)
	dir = 0;
      if ((nb = nb + dir) >= data->game.lines_->size)
	nb = 0;
      else if (nb < 0)
	nb = data->game.lines_->size - 1;
      i++;
    }
  if (dir != 0)
    return (-1);
  tomake[1] = nb;
  tomake[2] = rand() % line->count + 1;
  return (0);
}
