/*
** game_loop_computer.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Fri Feb 20 13:09:23 2015 Nathan Poirier
** Last update Sun Feb 22 19:45:12 2015 Nathan Poirier
*/

#include <errno.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include "allum.h"

int			game_computer_sleep(t_data *data, int sm)
{
  struct timeval	tv_start;
  struct timeval	tv_cur;
  unsigned int		diff;
  unsigned int		delay;

  delay = 180 + rand() % 300 + 600 * sm;
  if (gettimeofday(&tv_start, NULL) == -1)
    return (allum_exit(ERR_TIME) - 1);
  my_memcpy(&tv_cur, &tv_start, sizeof(struct timeval));
  while ((diff = 1000000 * (tv_cur.tv_sec - tv_start.tv_sec)
	  + (tv_cur.tv_usec - tv_start.tv_usec)) < delay * 1000)
    {
      if (usleep(delay * 1000 - diff) == -1)
	{
	  if ((errno == EINTR || errno == EAGAIN) &&
	      data->term.sigint_handled)
	    data->term.sigint_handled = MY_FALSE;
	  else
	    return (allum_exit(ERR_SLEEP) - 1);
	}
      if (gettimeofday(&tv_cur, NULL) == -1)
	return (allum_exit(ERR_TIME) - 1);
    }
  return (0);
}

int		game_loop_computer_col(t_data *data, t_player *player,
				       int *tomake)
{
  t_line	*line;
  t_my_listitem	*it;

  if ((it = my_list_get(data->game.lines_, data->game.cur_line)) == NULL ||
      it->data == NULL)
    return (0);
  line = (t_line *)it->data;
  data->game.cur_size = MY_MIN(line->count, 1);
  while (data->is_running && !tomake[0])
    {
      data->game.cur_phase = 2;
      if (game_draw(data) == -1 || game_computer_sleep(data, 0) == -1)
	return (-1);
      if (tomake[2] > data->game.cur_size && data->game.cur_size < line->count)
	data->game.cur_size++;
      else
	{
	  line->count = MY_MIN(line->size,
			       MY_MAX(0, line->count - tomake[2]));
	  tomake[0] = 1;
	}
    }
  return (0);
}

int		game_loop_computer_line(t_data *data, t_player *player)
{
  int		tomake[3];
  int		loop;

  loop = 0;
  tomake[0] = 0;
  if (game_ai(data, player, tomake) == -1)
    return (-1);
  while (data->is_running && !tomake[0])
    {
      data->game.cur_phase = 1;
      if (game_draw(data) == -1 ||
	  game_computer_sleep(data, (loop == 0 ? 1 : 0)) == -1)
	return (-1);
      if (data->game.cur_line < tomake[1])
	data->game.cur_line++;
      else if (data->game.cur_line > tomake[1])
	data->game.cur_line--;
      else
	game_loop_computer_col(data, player, tomake);
      loop++;
    }
  return (0);
}
