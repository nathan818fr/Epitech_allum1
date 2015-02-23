/*
** game_ai_best.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1/src/game/ai
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Sat Feb 21 12:47:38 2015 Nathan Poirier
** Last update Sun Feb 22 14:03:24 2015 Nathan Poirier
*/

#include "allum.h"

int		game_ai_best_analyze(t_btable *table, t_data *data)
{
  int		i;
  int		len;

  len = -1;
  i = 0;
  while (i < table->col)
    {
      if (table->fin[i] % 2 != 0)
	{
	  table->ana[i] = 1;
	  len = i + 1;
	}
      i++;
    }
  return (len);
}

int		game_ai_best_solve_nb(int *nb1, int *nb2, int len)
{
  int		i;
  int		pow;
  int		count;

  count = 0;
  pow = 1;
  i = 0;
  while (i < len)
    {
      if (nb2 != NULL)
	count += MY_ABS(nb1[i] - nb2[i]) * pow;
      else
	count += nb1[i] * pow;
      pow *= 2;
      i++;
    }
  return (count);
}

int		game_ai_best_solve(t_btable *table, t_data *data,
				   int *line, int *count)
{
  int		i;
  int		nb;

  i = 0;
  while (i < table->row)
    {
      nb = game_ai_best_solve_nb(table->cnt[i], table->ana, table->col);
      if (nb < game_ai_best_solve_nb(table->cnt[i], NULL, table->col))
	{
	  *line = i;
	  *count = nb;
	  return (0);
	}
      i++;
    }
  return (-1);
}

int		game_ai_best_end(t_data *data, int *tomake)
{
  int		lw1;
  int		lw2;
  t_my_listitem	*it;
  t_line	*line;
  int		i;

  lw2 = game_line_remaining(data, 2);
  lw1 = game_line_remaining(data, 1) - lw2;
  if (lw2 == 1)
    {
      i = 0;
      it = data->game.lines_->first;
      while (it != NULL && it->data != NULL)
	{
	  if ((line = (t_line *)it->data) && line->count >= 2)
	    {
	      tomake[1] = i;
	      tomake[2] = line->count - ((lw1 % 2 == 0) ? 1 : 0);
	      return (1);
	    }
	  i++;
	  it = it->next;
	}
    }
  return (0);
}

int		game_ai_best(t_data *data, t_player *player, int *tomake)
{
  t_btable	table;
  int		len;
  int		line;
  int		count;
  t_my_listitem	*it;

  if (game_ai_best_end(data, tomake) == 1)
    return (0);
  if (ai_fill_btable(&table, data) == -1)
    return (-1);
  len = game_ai_best_analyze(&table, data);
  len = len;
  line = 0;
  count = 0;
  if (game_ai_best_solve(&table, data, &line, &count) == 0 &&
      (it = my_list_get(data->game.lines_, line)) != NULL &&
      it->data != NULL && ((t_line *)it->data)->count > count)
    {
      tomake[1] = line;
      tomake[2] = ((t_line *)it->data)->count - count;
      ai_free_btable(&table);
      return (0);
    }
  ai_free_btable(&table);
  return (game_ai_random(data, player, tomake));
}
