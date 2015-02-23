/*
** game_player.c for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Thu Feb 19 12:28:13 2015 Nathan Poirier
** Last update Sat Feb 21 20:24:09 2015 Nathan Poirier
*/

#include "allum.h"

void		__game_player_create_name(t_player *player)
{
  char		*name;
  int		i;

  if (player->type == PLAYER_TYPE_KEYBOARD)
    name = "Player ";
  else
    name = "Computer ";
  i = 0;
  while (i < PLAYER_MAX_NAMELEN && name[i])
    {
      player->name[i] =name[i];
      i++;
    }
  if (i < PLAYER_MAX_NAMELEN)
    player->name[i] = '0' + (player->id % 10);
  player->namelen = i + 1;
}

t_player	*game_player_create(t_data *data, int type, char *name)
{
  t_player	*player;
  int		i;

  if ((player = malloc(sizeof(t_player))) == NULL)
    return (NULL);
  my_memset(player, 0, sizeof(t_player));
  data->game.__player_id++;
  player->id = data->game.__player_id;
  player->type = type;
  if (name == NULL)
    __game_player_create_name(player);
  else
    {
      i = 0;
      while (i < PLAYER_MAX_NAMELEN && name[i])
	{
	  player->name[i] = name[i];
	  i++;
	}
      player->namelen = i;
    }
  return (player);
}

t_player	*game_player_getwinner(t_data *data)
{
  t_player	*player;
  t_my_listitem	*it;

  player = NULL;
  it = data->game.players->first;
  while (it != NULL && it->data != NULL)
    {
      if (!((t_player *)it->data)->is_dead)
	{
	  if (player != NULL)
	    return (NULL);
	  player = (t_player *)it->data;
	}
      it = it->next;
    }
  return (player);
}
