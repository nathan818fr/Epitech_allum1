/*
** game_ai_btable.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1/src/game/ai
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Sat Feb 21 13:42:32 2015 Nathan Poirier
** Last update Sun Feb 22 14:02:03 2015 Nathan Poirier
*/

#include "allum.h"

int		ai_fill_line(t_btable *table, t_data *data, int nb)
{
  t_my_listitem	*it;
  t_line	*line;
  int		i;
  int		count;

  if ((it = my_list_get(data->game.lines_, nb)) == NULL || it->data == NULL ||
      (table->cnt[nb] = malloc(sizeof(int) * table->col)) == NULL)
    return (-1);
  my_memset(table->cnt[nb], 0, sizeof(int) * table->col);
  line = (t_line *)it->data;
  i = 0;
  count = line->count;
  while (i < table->col && count > 0)
    {
      table->cnt[nb][i] = count % 2;
      table->fin[i] += count % 2;
      count /= 2;
      i++;
    }
  return (0);
}

int		ai_fill_btable(t_btable *table, t_data *data)
{
  int		i;

  if ((table->row = data->game.lines_->size) <= 0 ||
      (table->col = game_line_maxcount(data)) <= 0)
    return (allum_exit("Error AI Best: Lines or count is 0") - 1);
  table->col = table->col / 2 + 1;
  if ((table->cnt = malloc(sizeof(int *) * table->row)) == NULL ||
      (table->fin = malloc(sizeof(int) * table->col)) == NULL ||
      (table->ana = malloc(sizeof(int) * table->col)) == NULL)
    return (allum_exit("%M") - 1);
  my_memset(table->fin, 0, sizeof(int) * table->col);
  my_memset(table->ana, 0, sizeof(int) * table->col);
  i = 0;
  while (i < table->row)
    {
      if (ai_fill_line(table, data, i) == -1)
	return (-1);
      i++;
    }
  return (0);
}

void		ai_free_btable(t_btable *table)
{
  int		i;

  if (table->cnt != NULL)
    {
      i = 0;
      while (i < table->row)
	{
	  free(table->cnt[i]);
	  table->cnt[i] = NULL;
	  i++;
	}
      free(table->cnt);
      table->cnt = NULL;
    }
  free(table->fin);
  table->fin = NULL;
  free(table->ana);
  table->ana = NULL;
}
