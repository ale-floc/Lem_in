#ifndef LEM_IN_H
# define LEM_IN_H
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include "libft.h"

typedef struct 		s_tube
{
	struct s_tube   *next;
	struct s_list	*adress;
}					t_tube;

typedef struct  	s_list
{
	char			*salle;
	int				x;
	int				y;
	int				room_start;
	int				room_end;
	int				ants;
	struct s_list	*next;
	struct s_tube 	*tube;
}					t_list;

typedef struct 		s_env
{
	int 			nb_ants;
	int				start;
	int				prepare_start;
	int				end;
	int				prepare_end;
	int				error;
	int				get_end;
	int				tube;
	t_list			*begin;
	struct s_tube 	*path;
}					t_env;

typedef struct 		s_file
{
	char 			*str;
	struct s_file	*next;
}					t_file;

#endif
