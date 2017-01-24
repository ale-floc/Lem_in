/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-floc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:16:37 by ale-floc          #+#    #+#             */
/*   Updated: 2017/01/24 18:16:38 by ale-floc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			move_ants(t_env *env, int nb_ants)
{
	t_list		*start;
	t_list		*end;
	t_tube		*list;
	int			move;

	move = 0;
	start = get_start(env);
	start->ants = env->nb_ants;
	end = get_end(env);
	ft_putchar('\n');
	start->space = 0;
	while (end->ants != nb_ants)
	{
		list = get_end_tube(env, end);
		while (42)
		{
			display_end_ants(list, end, &start);
			if (list == env->path)
				if (display_ants(nb_ants, &list, &start, &move))
					break ;
			list = list->prev;
		}
		start->space = 0;
		ft_putchar('\n');
	}
}

t_tube			*display_end_ants(t_tube *list, t_list *end, t_list **s)
{
	if (list->adress->ants && list->adress != end)
	{
		list->adress->ants--;
		if ((*s)->space)
			ft_putchar(' ');
		ft_putstr(list->adress->string_ants);
		ft_putchar('-');
		ft_putstr(list->next->adress->salle);
		if (list->next->adress == end)
			end->ants++;
		else
		{
			list->next->adress->ants++;
			list->next->adress->string_ants = list->adress->string_ants;
		}
		(*s)->space = 1;
	}
	return (list);
}

int				display_ants(int ant, t_tube **list, t_list **s, int *m)
{
	(*s)->ants--;
	*m += 1;
	if (*m <= ant)
	{
		(*list)->adress->ants++;
		(*list)->adress->string_ants = ft_strdup(ft_strjoin("L", ft_itoa(*m)));
		if ((*s)->space)
			ft_putchar(' ');
		ft_putstr((*list)->adress->string_ants);
		ft_putchar('-');
		ft_putstr((*list)->adress->salle);
	}
	return (1);
}
