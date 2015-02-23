/*
** tc_sig.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Wed Feb 18 16:15:08 2015 Nathan Poirier
** Last update Sun Feb 22 19:46:54 2015 Nathan Poirier
*/

#include <signal.h>
#include "allum.h"

int			my_signal(int sig, void (*func)(int))
{
  struct sigaction	new;
  struct sigaction	old;

  new.sa_handler = func;
  sigemptyset(&new.sa_mask);
  new.sa_flags = SA_RESETHAND | SA_NODEFER;
  if (sigaction(sig, &new, &old) < 0)
    return (-1);
  return (0);
}

void		tc_sig_handle_interrupt(int sig)
{
  t_data	*data;

  data = get_data();
  data->term.sigint_handled = MY_TRUE;
  if (my_signal(SIGINT, &tc_sig_handle_interrupt) == -1)
    allum_exit(ERR_SIGINT);
  else
    {
      tc_clear();
      allum_exit("Program interrupted !");
    }
}

void            tc_sig_handle_winchange(int sig)
{
  t_data        *data;

  data = get_data();
  data->term.sigint_handled = MY_TRUE;
  game_updatesize(data);
  if (my_signal(SIGWINCH, &tc_sig_handle_winchange) == -1)
    allum_exit(ERR_SIGWINCH);
}

int		tc_sig_register(t_data *data)
{
  if (my_signal(SIGINT, &tc_sig_handle_interrupt) == -1)
    return (my_error_zero(ERR_SIGINT) - 1);
  if (my_signal(SIGWINCH, &tc_sig_handle_winchange) == -1)
    return (my_error_zero(ERR_SIGWINCH) - 1);
  return (0);
}
