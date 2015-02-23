/*
** draw.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1/src
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Sat Feb 21 17:34:13 2015 Nathan Poirier
** Last update Sun Feb 22 13:46:12 2015 Nathan Poirier
*/

#include "allum.h"

/*
** Check if window is too small.
*/
int		draw_toosmall(t_data *data, int type)
{
  if (data->term.size[0] <= 42 || data->term.size[1] <= 12 ||
      (type == 1 && data->game.is_toosmall))
    {
      if (tc_fct(data, TC_CLEAR) == -1 ||
	  tc_fct(data, TC_REVERSE) == -1)
	return (-1);
      tc_putstr("The window is too small...");
      return (1);
    }
  return (0);
}

/*
** Clear screen and draw "ALLUM1" header at top.
** If the window is too small, -1 is returned and an error message
** is displayed.
*/
int		draw_head(t_data *data, int type)
{
  if (draw_toosmall(data, type) == 1)
    return (1);
  if (tc_fct(data, TC_CLEAR) == -1)
    return (-1);
  if (data->term.size[0] > 11)
    {
      if (tc_curpos(data, data->term.size[0] / 2 - 11 / 2, 0) == -1 ||
	  tc_fct(data, TC_RESET) == -1)
	return (-1);
      tc_putstr("A L L U M 1");
    }
  return (0);
}
