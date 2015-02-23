/*
** allum_errors.h for allum in /repo/Epitech/B2/C_Prog_Elem/CPE_2014_allum1/include
** 
** Made by Nathan Poirier
** Login   <poirie_n@epitech.net>
** 
** Started on  Sun Feb 22 14:18:10 2015 Nathan Poirier
** Last update Sun Feb 22 19:55:22 2015 Nathan Poirier
*/

#ifndef ALLUM_ERRORS_H_
# define ALLUM_ERRORS_H_

# define ERR_ERRNO	"%M"
# define ERR_TERMSIZE	"Unable to retrieve terminal size: %M"
# define ERR_CREAPLAYER	"Unable to create new player: %M"
# define ERR_ADDPLAYER	"Unable to add new player: %M"
# define ERR_CREALINE	"Unable to create new line: %M"
# define ERR_ADDLINE	"Unable to add new line: %M"
# define ERR_BADLISTS	"Invalid players or lines list."
# define ERR_BADPLAYER	"Unable to get player from player list."
# define ERR_TIME	"Unable to get system time."
# define ERR_SLEEP	"Sleep interrupted: %M"
# define ERR_INREAD	"Unable to read user input: %M"
# define ERR_SIGINT	"Unable to handle signal: SIGINT"
# define ERR_SIGWINCH	"Unable to handle signal: SIGWINCH"
# define ERR_GAMELIST	"Unable to initialize game list: %M"
# define ERR_TCFCT	"Unsupported termcap feature: '%s'."
# define ERR_OPENTTY	"Unable to open current TTY: %M"
# define ERR_NOTERM	"The environment variable 'TERM' don't exist."
# define ERR_BADTERM	"Unable to load terminal entry: %M"
# define ERR_GETTERM	"Unable to get terminal parameters: %M"
# define ERR_SETTERM	"Unable to set terminal parameters: %M"
# define ERR_RESETTERM	"Unable to reset terminal parameters: %M"
# define ERR_REQUIREDTC	"Your terminal does not support certain required \
capabilities (%s)."

#endif /* ALLUM_ERRORS_H_ */
