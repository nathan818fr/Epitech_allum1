/*
** tc_init.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1/src/termcap
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Wed Feb 18 11:43:58 2015 Nathan Poirier
** Last update Sun Feb 22 20:32:54 2015 Nathan Poirier
*/

#include "allum.h"

int		tc_init(t_data *data, char **env)
{
  char		*term_name;

  if ((data->term.tty_fd = open("/dev/tty", O_RDWR | O_NOCTTY | O_SYNC)) == -1)
    return (my_error_zero(ERR_OPENTTY) - 1);
  if ((term_name = my_getenv(env, "TERM")) == NULL)
    return (my_error_zero(ERR_NOTERM) - 1);
  if (tgetent(NULL, term_name) == ERR)
    return (my_error_zero(ERR_BADTERM) - 1);
  if (tc_verify(data))
    return (-1);
  if (tcgetattr(0, &data->term.termios) == -1)
    return (my_error_zero(ERR_GETTERM) - 1);
  my_memcpy(&data->term.termios_reset, &data->term.termios, sizeof(t_termios));
  data->term.can_reset = 1;
  data->term.termios.c_lflag &= ~(ICANON);
  data->term.termios.c_lflag &= ~(ECHO);
  data->term.termios.c_cc[VMIN] = 1;
  data->term.termios.c_cc[VTIME] = 0;
  if (tcsetattr(0, TCSADRAIN, &data->term.termios) == -1)
    return (my_error_zero(ERR_SETTERM) - 1);
  if (tc_sig_register(data) == -1 ||
      tc_fct(data, TC_HIDECURSOR) == -1)
    return (-1);
  data->term.can_reset = 2;
  return (0);
}

void		tc_free(t_data *data)
{
  if (data->term.can_reset)
    {
      if (data->term.can_reset >= 2)
	tc_fct(data, TC_SHOWCURSOR);
      if (tcsetattr(0, TCSADRAIN, &data->term.termios_reset) == -1)
	my_error(ERR_RESETTERM);
      data->term.can_reset = MY_FALSE;
    }
  if (data->term.tty_fd > 0)
    close(data->term.tty_fd);
}
