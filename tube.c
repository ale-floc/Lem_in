/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:59:48 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/24 18:59:49 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_tube			*end_exist_in_tube(t_tube *tmp)
{
	t_tube		*sous_tube;
	t_tube		*my_tube;

	my_tube = search_end(tmp);
	if (my_tube)
		return (my_tube);
	else
	{
		my_tube = tmp;
		while (my_tube)
		{
			if (my_tube->adress->room_end)
				return (my_tube);
			sous_tube = my_tube->adress->tube;
			while (sous_tube)
			{
				if (sous_tube->adress->room_end)
					return (my_tube);
				sous_tube = sous_tube->next;
			}
			my_tube = my_tube->next;
		}
	}
	return (tmp);
}

int				search_to_begin(t_env **env, t_tube **tube)
{
	int			i;

	i = 0;
	if ((*env)->move > nb_of_rooms(*env) * 2)
		ft_error(*env, 2);
	if ((*tube)->adress->room_end)
	{
		i = 1;
		(*env)->get_end = 1;
	}
	else if (*tube && (*tube)->adress && (*tube)->adress->tube)
	{
		i = 1;
		*tube = end_exist_in_tube(*tube);
	}
	return (i);
}

int				search_path(t_env **env, t_tube **tube, t_tube *tmp)
{
	int			e;

	e = 0;
	if ((*tube)->adress->room_end)
		(*env)->get_end = 1;
	if (!(*tube)->adress)
		e = 1;
	if (!(*env)->get_end && (*tube)->adress && !e)
	{
		(*env)->move++;
		*env = ft_recursive_tube((*tube)->adress->tube, *env,
			push_tube(tmp, (*tube)->adress));
	}
	if ((*env)->get_end == 1 && !e)
	{
		(*env)->path = push_tube((*env)->path, (*tube)->adress);
		e = 1;
	}
	return (e);
}

t_env			*ft_recursive_tube(t_tube *tube, t_env *env, t_tube *tmp)
{
	t_tube		*secu;
	int			e;

	secu = tube;
	e = 0;
	while (tube && !e)
	{
		if (search_to_begin(&env, &tube))
		{
			if (!check_if_exist(tmp, tube))
			{
				e = search_path(&env, &tube, tmp);
				if (e)
					break ;
			}
		}
		else
			break ;
		tube = tube->next;
		env->move++;
		if (secu == tube)
			break ;
	}
	return (env);
}
