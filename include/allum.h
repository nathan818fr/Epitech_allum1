/*
** header.h for  in /repo/Epitech/Empty_Project/include
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Tue Feb 10 16:20:21 2015 Nathan Poirier
** Last update Sun Feb 22 19:57:04 2015 Nathan Poirier
*/

#ifndef ALLUM_H_
# define ALLUM_H_

/*
** Include external headers
*/
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <time.h>
# include "myutils_bool.h"
# include "myutils_log.h"
# include "myutils_list.h"
# include "myutils_printf.h"
# include "myutils.h"

/*
** Include error messages
*/
# include "allum_errors.h"

/*
** Options define
*/
# define OPT_LINES_3MAX		11

/*
** Player define
*/
# define PLAYER_TYPE_KEYBOARD	1
# define PLAYER_TYPE_COMPUTER	2
# define PLAYER_MAX_NAMELEN	16

/*
** Custom caracters
*/
# define CHAR_ARROW_UD		"\xE2\x86\x95"
# define CHAR_ARROW_LR		"\xE2\x86\x94"

/*
** Termcap define
*/
# define TC_READSIZE		4
# define TC_CLEAR		"cl"
# define TC_RESET		"me"
# define TC_REVERSE		"mr"
# define TC_BOLD		"md"
# define TC_HALFBRIGHT		"mh"
# define TC_HIDECURSOR		"vi"
# define TC_SHOWCURSOR		"ve"
# define TC_UNDERLINE		"us"

/*
** Reduce system structures name
*/
typedef struct termios	t_termios;
typedef struct winsize	t_winsize;

/*
** Define my structures
*/
typedef struct		s_btable
{
  int			**cnt;
  int			*fin;
  int			*ana;
  int			row;
  int			col;
}			t_btable;

typedef struct		s_player
{
  int			id;
  int			type;
  char			name[PLAYER_MAX_NAMELEN + 1];
  int			namelen;
  t_my_bool		is_dead;
}			t_player;

typedef struct		s_line
{
  int			pos[2];
  int			size;
  int			count;
}			t_line;

typedef struct		s_termcap
{
  int			size[2];
  int			can_reset;
  int			tty_fd;
  t_termios		termios;
  t_termios		termios_reset;
  t_my_bool		sigint_handled;
  int			read_len;
  char			read_buf[TC_READSIZE];
  char			tmpbuf[8192];
  t_my_bool		mh_fallback;
}			t_termcap;

typedef struct		s_game
{
  t_my_bool		is_running;
  int			pos[2];
  int			__player_id;
  int			cur_player;
  int			cur_phase;
  int			cur_line;
  int			cur_size;
  t_player		*cur_infoplayer;
  int			line_maxsize;
  t_my_list		*players;
  t_my_list		*lines_;
  t_my_bool		is_toosmall;
}			t_game;

typedef struct		s_menu
{
  int			phase;
  int			cur;
  int			players[4];
  int			difficulty;
  int			nblines;
}			t_menu;

typedef struct		s_data
{
  t_my_bool		is_running;
  t_termcap		term;
  t_menu		menu;
  t_game		game;
}			t_data;

/*
** main.c
*/
t_data		*get_data();
int		allum_exit(char *err);

/*
** draw.c
*/
int		draw_toosmall(t_data *data, int type);
int		draw_head(t_data *data, int type);

/*
** termcap/tc_init.c
*/
int		tc_init(t_data *data, char **env);
void		tc_free(t_data *data);

/*
** termcap/tc_sig.c
*/
int		tc_sig_register(t_data *data);

/*
** termcap/tc_read.c
*/
int		tc_readkey(t_data *data);
t_my_bool	tc_iskey(t_data *data, int len, ...);

/*
** termcap/tc_fct.c
*/
int		tc_putchar(char c);
int		tc_putstr(char *str);
int		tc_fct(t_data *data, char *fct);
int		tc_curpos(t_data *data, int x, int y);
void		tc_clear();

/*
** termcap/tc_verify.c
*/
int		tc_verify(t_data *data);

/*
** menu/menu.c
*/
int		menu_loop(t_data *data);

/*
** menu/menu_draw.c
*/
int		menu_draw(t_data *data);

/*
** menu/menu_draw_play.c
*/
int		menu_draw_play(t_data *data);

/*
** menu/menu_draw_list.c
*/
int		menu_draw_list(t_data *data, int is_current,
			       char **opts, int selected);

/*
** game/game_init.c
*/
int		game_init(t_data *data);
int		game_reset(t_data *data);
int		game_updatesize(t_data *data);
int		game_players_reset(t_data *data);
int		game_lines_reset(t_data *data);

/*
** game/game_line.c
*/
t_line		*game_line_create(int size);
int		game_line_remaining(t_data *data, int min);
int		game_line_maxcount(t_data *data);

/*
** game/game_player.c
*/
t_player	*game_player_create(t_data *data, int type, char *name);
t_player	*game_player_getwinner(t_data *data);

/*
** game/game_loop.c
*/
int		game_start(t_data *data);

/*
** game/game_loop_keyboard.c
*/
int		game_loop_keyboard_line(t_data *data, t_player *player);

/*
** game/game_loop_computer.c
*/
int		game_loop_computer_line(t_data *data, t_player *player);

/*
** game/game_draw.c
*/
int		game_draw(t_data *data);
int		game_draw_playerinfo(t_data *data, t_game *game, int type);

/*
** game/ai/game_ai.c
*/
int		game_ai(t_data *data, t_player *player, int *tomake);
int		game_ai_random(t_data *data, t_player *player,
			       int *tomake);

/*
** game/ai/game_ai_best.c
*/
int		game_ai_best(t_data *data, t_player *player, int *tomake);

/*
** game/ai/game_ai_btable.c
*/
int		ai_fill_btable(t_btable *table, t_data *data);
void		ai_free_btable(t_btable *table);

#endif /* ALLUM_H_ */
