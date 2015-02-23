/*
** tc_fct.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Thu Feb 19 15:12:33 2015 Nathan Poirier
** Last update Sun Feb 22 20:32:32 2015 Nathan Poirier
*/

#include "allum.h"

int		tc_putchar(char c)
{
  t_data	*data;

  data = get_data();
  return (write(data->term.tty_fd, &c, 1));
}

int             tc_putstr(char *str)
{
  t_data        *data;

  data = get_data();
  return (write(data->term.tty_fd, str, my_strlen(str)));
}

/*
** Clear scren and reset print mode.
** No error message ! Must ust only be used before displaying an error !!
*/
void		tc_clear()
{
  t_data	*data;
  char          *res;

  data = get_data();
  if (!data->term.can_reset)
    return ;
  if ((res = tgetstr(TC_CLEAR, NULL)) != NULL)
    {
      tputs(res, 0, (int (*)(int))&tc_putchar);
      if ((res = tgetstr(TC_RESET, NULL)) != NULL)
	tputs(res, 0, (int (*)(int))&tc_putchar);
    }
}

int		tc_fct(t_data *data, char *fct)
{
  char		*res;

  if ((res = tgetstr(fct, NULL)) == NULL)
    {
      tc_clear();
      my_error(ERR_TCFCT, fct);
      return (allum_exit(NULL) - 1);
    }
  tputs(res, 0, (int (*)(int))&tc_putchar);
  return (0);
}

int		tc_curpos(t_data *data, int x, int y)
{
  char		*buf;
  char		*res;

  buf = data->term.tmpbuf;
  if ((res = tgetstr("cm", &buf)) == NULL)
    {
      tc_clear();
      my_error(ERR_TCFCT, "cm");
      return (allum_exit(NULL) - 1);
    }
  tputs(tgoto(res, x, y), 0, (int (*)(int))&tc_putchar);
  return (0);
}
