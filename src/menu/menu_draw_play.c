/*
** menu_draw.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Sat Feb 21 17:52:34 2015 Nathan Poirier
** Last update Sat Feb 21 20:29:53 2015 Nathan Poirier
*/

#include "allum.h"

int		menu_draw_play_playeropts(t_data *data, int nb)
{
  char		*opts[5];

  if ((opts[0] = my_strdup("Player X")) == NULL)
    return (allum_exit("%M") - 1);
  opts[0][7] = '0' + ((nb + 1) % 10);
  opts[1] = "Keyboard";
  opts[2] = "Computer";
  opts[3] = "Disabled";
  if (nb < 2)
    opts[3] = NULL;
  opts[4] = NULL;
  if (menu_draw_list(data, (data->menu.cur - 2 == nb) ? 1 : 0, opts,
		     data->menu.players[nb]) == -1)
    return (-1);
  free(opts[0]);
  return (0);
}

int		menu_draw_play_difficulty(t_data *data)
{
  char		*opts[4];

  opts[0] = "Computer difficulty";
  opts[1] = "Hard";
  opts[2] = "Easy";
  opts[3] = NULL;
  if (menu_draw_list(data, data->menu.cur == 6 ? 1 : 0, opts,
		     data->menu.difficulty) == -1)
    return (-1);
  return (0);
}

int             menu_draw_play_nblines(t_data *data)
{
  char          *opts[2 + OPT_LINES_3MAX];
  int		i;

  opts[0] = "Lines   ";
  i = 1;
  while (i < 1 + OPT_LINES_3MAX)
    {
      if ((opts[i] = malloc(4)) == NULL)
	return (-1);
      my_memset(opts[i], 0, 4);
      my_sprintf(opts[i], "%d", 4 + i - 1);
      i++;
    }
  opts[i] = NULL;
  if (menu_draw_list(data, data->menu.cur == 1 ? 1 : 0, opts,
		     data->menu.nblines) == -1)
    return (-1);
  i = 1;
  while (i < 2 + OPT_LINES_3MAX)
    {
      free(opts[i]);
      i++;
    }
  return (0);
}

int		menu_draw_play(t_data *data)
{
  int		i;

  if (tc_curpos(data, data->term.size[0] / 2 - 10, 3) == -1)
    return (-1);
  if (tc_fct(data, data->menu.cur == 0 ? TC_REVERSE : TC_RESET) == -1)
    return (-1);
  tc_putstr(data->menu.cur == 0 ? "[> " : "[  ");
  tc_putstr("Start the game");
  tc_putstr(data->menu.cur == 0 ? " <]" : "  ]");
  i = 0;
  while (i < 4)
    {
      if (tc_curpos(data, data->term.size[0] / 2 - 18, 7 + i) == -1)
	return (-1);
      if (menu_draw_play_playeropts(data, i) == -1)
	return (-1);
      i++;
    }
  if (tc_curpos(data, data->term.size[0] / 2 - 18, 12) == -1 ||
      menu_draw_play_difficulty(data) == -1)
    return (-1);
  if (tc_curpos(data, data->term.size[0] / 2 - 18, 5) == -1 ||
      menu_draw_play_nblines(data) == -1)
    return (-1);
  return (0);
}
