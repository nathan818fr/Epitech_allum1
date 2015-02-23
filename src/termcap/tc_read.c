/*
** tc_read.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Wed Feb 18 14:52:54 2015 Nathan Poirier
** Last update Sun Feb 22 19:46:02 2015 Nathan Poirier
*/

#include "errno.h"
#include "allum.h"

int		tc_readkey(t_data *data)
{
  data->term.read_len = read(STDIN_FILENO, data->term.read_buf, TC_READSIZE);
  if (data->term.read_len < 0)
    {
      data->term.read_len = 0;
      if ((errno == EINTR || errno == EAGAIN) && data->term.sigint_handled)
	data->term.sigint_handled = MY_FALSE;
      else
	return (allum_exit(ERR_INREAD) - 1);
    }
  return (data->term.read_len);
}

t_my_bool	tc_iskey(t_data *data, int len, ...)
{
  t_my_bool	res;
  va_list	ap;
  int		i;
  int		val;

  if (data->term.read_len != len)
    return (MY_FALSE);
  res = MY_TRUE;
  va_start(ap, len);
  i = 0;
  while (i < len && res)
    {
      val = va_arg(ap, int);
      if (data->term.read_buf[i] != val)
	res = MY_FALSE;
      i++;
    }
  va_end(ap);
  return (res);
}
