/*
** game_line.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Thu Feb 19 12:15:07 2015 Nathan Poirier
** Last update Sat Feb 21 14:09:07 2015 Nathan Poirier
*/

#include "allum.h"

t_line		*game_line_create(int size)
{
  t_line	*line;

  if ((line = malloc(sizeof(t_line))) == NULL)
    return (NULL);
  my_memset(line, 0, sizeof(t_line));
  line->size = size;
  line->count = size;
  return (line);
}

int		game_line_remaining(t_data *data, int min)
{
  int		nb;
  t_my_listitem	*it;

  nb = 0;
  it = data->game.lines_->first;
  while (it != NULL && it->data != NULL)
    {
      if (((t_line *)it->data)->count >= min)
	nb++;
      it = it->next;
    }
  return (nb);
}

int		game_line_maxcount(t_data *data)
{
  int		cnt;
  t_my_listitem	*it;
  t_line	*line;

  cnt = -1;
  it = data->game.lines_->first;
  while (it != NULL && it->data != NULL)
    {
      line = (t_line *)it->data;
      if (line->count > cnt)
	cnt = line->count;
      it = it->next;
    }
  return (cnt);
}
