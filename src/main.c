/*
** main.c for  in /repo/Epitech/Empty_Project/src
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Tue Feb 10 16:19:46 2015 Nathan Poirier
** Last update Sun Feb 22 20:31:25 2015 Nathan Poirier
*/

#include "allum.h"

/*
** Return the data variable.
** Must be used only if it is impossible to pass the variable as a parameter.
*/
t_data		*get_data()
{
  static t_data	data;

  return (&data);
}

/*
** Display an error message and set is_running to false.
*/
int		allum_exit(char *err)
{
  t_data	*data;

  data = get_data();
  data->is_running = MY_FALSE;
  tc_clear();
  if (err != NULL)
    my_error(err);
  return (0);
}

/*
** Initialize data and termcaps.
*/
t_data		*allum_init(char **env)
{
  t_data	*data;

  data = get_data();
  my_memset(data, 0, sizeof(t_data));
  if (tc_init(data, env) == -1)
    return (NULL);
  if (game_init(data) == -1)
    return (NULL);
  data->is_running = 1;
  srand(time(NULL));
  return (data);
}

/*
** Free memory and close fd.
*/
int		allum_free(int exitcode)
{
  t_data	*data;

  data = get_data();
  tc_free(data);
  if (data->game.players != NULL)
    my_list_free(data->game.players);
  if (data->game.lines_ != NULL)
    my_list_free(data->game.lines_);
  return (exitcode);
}

/*
** Main function: Initialize data and start menu loop.
*/
int		main(int argc, char **argv, char **env)
{
  t_data	*data;

  if ((data = allum_init(env)) == NULL)
    return (allum_free(EXIT_FAILURE));
  if (data->is_running && menu_loop(data) == -1)
    return (allum_free(EXIT_FAILURE));
  return (allum_free(EXIT_SUCCESS));
}
