/*
** menu_draw.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Sat Feb 21 17:52:34 2015 Nathan Poirier
** Last update Sat Feb 21 20:30:11 2015 Nathan Poirier
*/

#include "allum.h"

int		menu_draw_topbar(t_data *data)
{
  int		i;
  char		*txt;
  int		txtlen;

  if (tc_curpos(data, 0, 1) == -1 ||
      tc_fct(data, TC_REVERSE) == -1)
    return (-1);
  txt = (data->menu.phase == 1) ? "PLAY" : "MENU";
  txtlen = my_strlen(txt);
  i = 0;
  while (i < data->term.size[0])
    {
      if (i == data->term.size[0] / 2 - txtlen / 2)
	{
	  tc_putstr(txt);
	  i += txtlen - 1;
	}
      else
	tc_putchar(' ');
      i++;
    }
  return (0);
}

int		menu_draw_home(t_data *data)
{
  char		*btns[2];
  int		i;

  btns[0] = "PLAY";
  btns[1] = "EXIT";
  i = 0;
  while (i < 2)
    {
      if (tc_curpos(data, data->term.size[0] / 2 - 5, 3 + i * 2) == -1)
	return (-1);
      if (tc_fct(data, (data->menu.cur == i) ? TC_REVERSE : TC_RESET) == -1)
	return (-1);
      tc_putstr((data->menu.cur == i) ? "[> " : "[  ");
      tc_putstr(btns[i]);
      tc_putstr((data->menu.cur == i) ? " <]" : "  ]");
      i++;
    }
  return (0);
}

int		menu_draw(t_data *data)
{
  int           r;

  r = draw_head(data, 1);
  if (r == -1)
    return (-1);
  if (r == 1)
    return (0);
  if (menu_draw_topbar(data) == -1)
    return (-1);
  if (data->menu.phase == 0 && menu_draw_home(data) == -1)
    return (-1);
  if (data->menu.phase == 1 && menu_draw_play(data) == -1)
    return (-1);
  return (0);
}
