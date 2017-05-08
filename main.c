/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:23:02 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/24 16:23:03 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_recursive_possible(t_list *start, t_env *env)
{
	t_tube	*tmp;

	tmp = NULL;
	tmp = push_tube(tmp, start);
	ft_recursive_tube(start->tube, env, tmp);
	if (!env->get_end || !env->path)
		ft_error(env, 2);
	env->path = parse_list(env);
	return (0);
}

void		start_ants(t_env *env)
{
	t_list	*start;
	t_list	*end;

	start = env->begin;
	end = env->begin;
	while (start)
	{
		if (start->room_start)
			break ;
		start = start->next;
	}
	while (end)
	{
		if (end->room_end)
			break ;
		end = end->next;
	}
	ft_recursive_possible(start, env);
}

void		free_final(t_env *env, t_file *file)
{
	while (file)
	{
		free(file->str);
		free(file);
		file = file->next;
	}
	while (env->begin)
	{
		free(env->begin->salle);
		free(env->begin);
		env->begin = env->begin->next;
	}
}

void		lem_in_begin(t_env *env, t_file *file)
{
	if (!file || !env->start || !env->end || !env->tube)
		ft_error(env, 1);
	start_ants(env);
	if (env->get_end)
	{
		while (file)
		{
			ft_putendl(file->str);
			free(file->str);
			free(file);
			file = file->next;
		}
		move_ants(env, env->nb_ants);
	}
	else
		ft_error(env, 1);
	free_final(env, file);
}

int			main(int argc, char **argv)
{
	char	*line;
	t_env	*env;
	t_file	*file;

	(void)argc;
	env = lem_init();
	file = NULL;
	if (argv[1])
		check_arg(env, ft_strtrim(argv[1]));
	while (get_next_line(0, &line))
	{
		line = line_parse(env, line);
		if (env->nb_ants == -1 && ft_isdigit(line[0]))
			env->nb_ants = parse_get_ants(env, line);
		else if ('#' == line[0])
			env = parse_diese(env, line);
		else if (parse_check(env, line))
			env = check_room_or_tube(env, line);
		else
			ft_error(env, 1);
		file = push_fd(file, line);
	}
	lem_in_begin(env, file);
	return (0);
}
