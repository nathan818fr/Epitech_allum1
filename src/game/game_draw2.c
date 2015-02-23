/*
** game_draw2.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1/src/game
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Sat Feb 21 16:44:43 2015 Nathan Poirier
** Last update Sat Feb 21 16:44:53 2015 Nathan Poirier
*/

#include "allum.h"

int		game_draw_playerinfo(t_data *data, t_game *game, int type)
{
  if (tc_curpos(data, data->term.size[0] / 2 -
		data->game.cur_infoplayer->namelen / 2 + 1,
		game->pos[1] + 2) == -1 ||
      tc_fct(data, TC_RESET) == -1)
    return (-1);
  my_putstr(data->game.cur_infoplayer->name);
  if (tc_curpos(data, data->term.size[0] / 2 - 4, game->pos[1] + 3) == -1 ||
      tc_fct(data, TC_RESET) == -1)
    return (-1);
  my_putstr(type == 4 ? " WINS !!!" : "has lost !");
  if (tc_curpos(data, data->term.size[0] / 2 - 12, game->pos[1] + 5) == -1 ||
      tc_fct(data, TC_REVERSE) == -1)
    return (-1);
  my_putstr("Press any key to continue");
  return (0);
}
