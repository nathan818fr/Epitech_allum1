/*
** game_init.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Thu Feb 19 11:59:47 2015 Nathan Poirier
** Last update Sun Feb 22 19:52:15 2015 Nathan Poirier
*/

#include "allum.h"

int		game_init(t_data *data)
{
  t_game	*game;

  game = &data->game;
  if ((game->players = my_list_create()) == NULL ||
      (game->lines_ = my_list_create()) == NULL)
    return (my_error_zero(ERR_GAMELIST) - 1);
  if (game_reset(data) == -1)
    return (-1);
  return (0);
}

int		game_reset(t_data *data)
{
  if (game_players_reset(data) == -1)
    return (-1);
  if (game_lines_reset(data) == -1)
    return (-1);
  return (0);
}

int		game_updatesize(t_data *data)
{
  t_winsize	wsize;
  t_my_listitem	*it;
  t_line	*line;
  int		i;

  if (data->term.tty_fd < 0 ||
      ioctl(data->term.tty_fd, TIOCGWINSZ, &wsize) == -1)
    return (allum_exit(ERR_TERMSIZE) -1);
  data->game.is_toosmall = (data->game.line_maxsize + 4 >= wsize.ws_col ||
			    data->game.lines_->size + 4 >= wsize.ws_row);
  data->term.size[0] = wsize.ws_col;
  data->term.size[1] = wsize.ws_row;
  data->game.pos[0] = wsize.ws_col / 2 - data->game.line_maxsize / 2 - 2;
  data->game.pos[1] = 1;
  i = 0;
  it = data->game.lines_->first;
  while (it != NULL && it->data != NULL && (line = (t_line *)it->data))
    {
      line->pos[0] = wsize.ws_col / 2 - line->size / 2;
      line->pos[1] = data->game.pos[1] + i + 2;
      i++;
      it = it->next;
    }
  return (0);
}

int		game_players_reset(t_data *data)
{
  t_game	*game;
  t_my_listitem	*it;
  t_player	*player;
  int		i;
  int		type;

  game = &data->game;
  my_list_clean(game->players);
  game->__player_id = 0;
  i = 0;
  while (i < 4)
    {
      if (data->menu.players[i] != 2)
	{
	  type = (data->menu.players[i] == 0) ?
	    PLAYER_TYPE_KEYBOARD : PLAYER_TYPE_COMPUTER;
	  if ((player = game_player_create(data, type, NULL)) == NULL)
	    return (allum_exit(ERR_CREAPLAYER) - 1);
	  if ((it = my_list_add(game->players, player)) == NULL)
	    return (allum_exit(ERR_ADDPLAYER) - 1);
	}
      i++;
    }
  return (0);
}

int		game_lines_reset(t_data *data)
{
  t_game	*game;
  t_my_listitem	*it;
  t_line	*line;
  int		i;

  game = &data->game;
  my_list_clean(game->lines_);
  i = 0;
  while (i < 4 + data->menu.nblines)
    {
      if ((line = game_line_create(i * 2 + 1)) == NULL)
	return (allum_exit(ERR_CREALINE) - 1);
      if ((it = my_list_add(game->lines_, line)) == NULL)
	return (allum_exit(ERR_ADDLINE) - 1);
      if (game->line_maxsize < i * 2 + 1)
	game->line_maxsize = i * 2 + 1;
      i++;
    }
  return (game_updatesize(data));
}
