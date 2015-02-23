/*
** menu_draw_list.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Sat Feb 21 19:04:43 2015 Nathan Poirier
** Last update Sun Feb 22 19:33:15 2015 Nathan Poirier
*/

#include "allum.h"

void		menu_draw_list_spaces(t_data *data, int len)
{
  int		i;

  i = 0;
  while (i < len)
    {
      tc_putchar(' ');
      i++;
    }
}

int		menu_draw_list_itemstyle(t_data *data, int sel, int i)
{
  if (data->term.mh_fallback)
    {
      if (tc_fct(data, TC_RESET) == -1 ||
	  (i - 1 == sel && tc_fct(data, TC_UNDERLINE) == -1))
	return (-1);
    }
  else
    {
      if (tc_fct(data, (i - 1 == sel) ? TC_RESET : TC_HALFBRIGHT) == -1)
	return (-1);
    }
  return (0);
}

int		menu_draw_list(t_data *data, int is_current,
			       char **opts, int sel)
{
  int		i;

  if (tc_fct(data, TC_RESET) == -1 ||
      (is_current && tc_fct(data, TC_REVERSE) == -1))
    return (-1);
  tc_putstr(opts[0]);
  tc_putstr(":");
  i = 1;
  while (opts[i])
    {
      if (tc_fct(data, TC_RESET) == -1 || (my_putstr(" ") && 0))
	return (-1);
      if (is_current)
	{
	  if (menu_draw_list_itemstyle(data, sel, i))
	    return (-1);
	  my_putstr(opts[i]);
	}
      else if (i - 1 == sel)
	my_putstr(opts[i]);
      else
	menu_draw_list_spaces(data, (int)my_strlen(opts[i]));
      i++;
    }
  return (0);
}
