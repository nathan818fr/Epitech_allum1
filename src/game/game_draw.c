/*
** game_draw.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Thu Feb 19 15:06:35 2015 Nathan Poirier
** Last update Sun Feb 22 12:48:26 2015 Nathan Poirier
*/

#include "allum.h"

int		game_draw_line(t_data *data, t_game *game, t_line *line,
			       int nb)
{
  int		i;

  if (tc_fct(data, TC_RESET) == -1)
    return (-1);
  i = 0;
  while (i < line->size - line->count && (i = i + 1))
    tc_putchar('.');
  if (data->game.cur_phase >= 2 && nb == data->game.cur_line)
    {
      if (tc_fct(data, TC_REVERSE) == -1)
	return (-1);
      while (i < line->size - line->count + data->game.cur_size && (i = i + 1))
	tc_putchar('|');
      if (tc_fct(data, TC_RESET) == -1)
	return (-1);
    }
  while (i < line->size && (i = i + 1))
    tc_putchar('|');
  return (0);
}

int		game_draw_cur(t_data *data, t_game *game)
{
  if (tc_fct(data, TC_REVERSE) == -1 ||
      tc_fct(data, TC_BOLD) == -1)
    return (-1);
  if (data->game.cur_phase >= 2)
    tc_putstr(CHAR_ARROW_LR);
  else
    tc_putstr(CHAR_ARROW_UD);
  return (0);
}

int		game_draw_lines(t_data *data, t_game *game)
{
  int		nb;
  t_my_listitem	*it;
  t_line	*line;

  nb = 0;
  it = game->lines_->first;
  while (it != NULL && it->data != NULL)
    {
      line = (t_line *)it->data;
      if (nb == data->game.cur_line)
	{
	  if (tc_curpos(data, game->pos[0], line->pos[1]) == -1 ||
	      game_draw_cur(data, game) == -1)
	    return (-1);
	}
      if (tc_curpos(data, line->pos[0], line->pos[1]) == -1)
	return (-1);
      if (game_draw_line(data, game, line, nb) == -1)
	return (-1);
      nb++;
      it = it->next;
    }
  return (0);
}

int		game_draw_topbar(t_data *data, t_game *game)
{
  t_my_listitem *it;
  t_player	*player;
  int		i;

  if (game->players == NULL || tc_fct(data, TC_REVERSE) == -1)
    return (-1);
  if ((it = my_list_get(game->players, data->game.cur_player)) != NULL &&
      it->data != NULL && (player = (t_player *)it->data))
    {
      if (tc_curpos(data, 0, game->pos[1]) == -1)
	return (-1);
      i = 0;
      while (i < data->term.size[0])
	{
	  if (i == data->term.size[0] / 2 - player->namelen / 2 + 1)
	    {
	      tc_putstr(player->name);
	      i += player->namelen - 1;
	    }
	  else
	    tc_putchar(' ');
	  i++;
	}
    }
  return (0);
}

int		game_draw(t_data *data)
{
  t_game	*game;
  int		r;

  r = draw_head(data, 1);
  if (r == -1)
    return (-1);
  if (r == 1)
    return (0);
  game = &data->game;
  if (game_draw_topbar(data, game) == -1)
    return (-1);
  if (data->game.cur_phase >= 3)
    {
      if (game_draw_playerinfo(data, game, data->game.cur_phase))
	return (-1);
    }
  else if (game_draw_lines(data, game) == -1)
    return (-1);
  return (0);
}
