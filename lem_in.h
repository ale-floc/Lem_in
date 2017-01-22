/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anramos <anramos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 17:10:01 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/22 20:23:29 by anramos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include "libft.h"

typedef struct		s_tube
{
	struct s_tube	*next;
	struct s_tube	*prev;
	struct s_list	*adress;
}					t_tube;

typedef struct		s_list
{
	char			*salle;
	int				x;
	int				y;
	int				room_start;
	int				room_end;
	int				ants;
	char			*string_ants;
	struct s_list	*next;
	struct s_tube	*tube;
}					t_list;

typedef struct		s_env
{
	int				nb_ants;
	int				start;
	int				prepare_start;
	int				end;
	int				prepare_end;
	int				error;
	int				get_end;
	int				tube;
	int				move;
	t_list			*begin;
	struct s_tube	*path;
	int				e;
}					t_env;

typedef struct		s_file
{
	char			*str;
	struct s_file	*next;
}					t_file;

void				ft_error(t_env *env, int error);
void				error_usage(void);
void				options_on(t_env *e, char c);
void				lem_in_begin(t_env *env);
void				move_ants(t_env *env, int nb_ants);
int					check_arg(t_env *e, char *str);
int					parse_get_ants(t_env *env, char *line);
int					parse_check(t_env *env, char *line);
int					check_if_exist(t_tube *tube1, t_tube *tube2);
int					check_if_exist_in_tube(t_tube *tube1, t_list *tube2);
int					space_room(t_env *env, char *line);
int					is_strnb(t_env *env, char *str1, char *str2);
int					nb_of_rooms(t_env *env);
int					ft_recursive_possible(t_list *start, t_env *env);
int					is_space_or_tab(char c);
int					ft_strcmp_join(char *s1, char *s2);
char				**ft_strsplit_fn(char const *s, int (*f) (char));
char				*ft_strjoin_join(char const *s1, char const *s2);
t_env				*lem_init(void);
t_env				*parse_diese(t_env *env, char *line);
t_env				*check_command(t_env *env, char *line);
t_env				*check_tube(t_env *env, char *line);
t_env				*check_room_or_tube(t_env *env, char *line);
t_env				*ft_recursive_tube(t_tube *tube, t_env *env, t_tube *tmp);
t_list				*parse_room(t_env *env, char *line);
t_list				*init_one_list(char *str, int x, int y, t_env *env);
t_list				*ft_listpush(char **str, t_list *list, t_env *env);
t_list				*get_end(t_env *env);
t_list				*get_start(t_env *env);
t_tube				*parse_list(t_env *env);
t_tube				*list_push_tube(t_list *list, t_list *second);
t_tube				*push_tube(t_tube *tube, t_list *list);
t_tube				*search_end(t_tube *tmp);
t_tube				*end_exist_in_tube(t_tube *tmp);
t_tube				*get_end_tube(t_env *env, t_list *end);
t_file				*push_fd(t_file *file, char *str);

#endif
