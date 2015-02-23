/*
** tc_verify.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Sun Feb 22 13:11:46 2015 Nathan Poirier
** Last update Sun Feb 22 19:55:08 2015 Nathan Poirier
*/

#include "allum.h"

int		tc_verify_exists(char *fct, t_my_bool print_error)
{
  if (tgetstr(fct, NULL) == NULL)
    {
      if (print_error)
	my_error(ERR_REQUIREDTC, fct);
      return (-1);
    }
  return (0);
}

int		tc_verify(t_data *data)
{
  if (tc_verify_exists(TC_CLEAR, 1) == -1 ||
      tc_verify_exists(TC_RESET, 1) == -1 ||
      tc_verify_exists(TC_REVERSE, 1) == -1 ||
      tc_verify_exists(TC_BOLD, 1) == -1 ||
      tc_verify_exists(TC_HIDECURSOR, 1) == -1 ||
      tc_verify_exists(TC_SHOWCURSOR, 1) == -1)
    return (-1);
  if (tc_verify_exists(TC_HALFBRIGHT, 0) == -1)
    {
      if (tc_verify_exists(TC_UNDERLINE, 1) == -1)
	return (-1);
      data->term.mh_fallback = MY_TRUE;
    }
  else
    data->term.mh_fallback = MY_FALSE;
  return (0);
}
