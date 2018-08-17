/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-ni <avan-ni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 11:47:29 by avan-ni           #+#    #+#             */
/*   Updated: 2018/08/17 21:51:10 by avan-ni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

int	ft_read(t_lem_in *lem)
{
	char *line;
	int i;

	i = 0;
	while (get_next_line(0, &line))
	{
		if (!ft_strcmp(line, ""))
		{
			free(line);
			return (0);
		}
		else
			lem->data[i++] = ft_strdup(line);
		free(line);
	}
	lem->data[i] = NULL;
	free(line);
	return (1);
}

int		ft_store(t_lem_in *lem)
{
	int i;

	i = 0;
	while (lem->data[i])
	{
		if (!ft_strcmp(lem->data[i], "##start"))
			lem->start = lem->rooms;
		else if (!ft_strcmp(lem->data[i], "##end"))
			lem->end = lem->rooms;
		else if (ft_strchr(lem->data[i], ' '))
			ft_save_room(lem, lem->data[i]);
		else if (ft_strchr(lem->data[i], '-'))
			lem->links[lem->link++] = ft_strdup(lem->data[i]);
		else if (lem->data[i][0] != '#')
			ft_save_ants(lem, lem->data[i]);
		i++;
	}
	lem->links[lem->link] = NULL;
	lem->rm[lem->rooms].name = NULL;
	ft_swap_rooms(lem);
	return (1);
}

void	ft_swap_rooms(t_lem_in *lem)
{
	t_rm temp;
	if (lem->start != 0)
	{
		temp.name = lem->rm[0].name;
		temp.x = lem->rm[0].x;
		temp.y = lem->rm[0].y;
		lem->rm[0].name = lem->rm[lem->start].name;
		lem->rm[0].x = lem->rm[lem->start].x;
		lem->rm[0].y = lem->rm[lem->start].y;
		lem->rm[lem->start].name = temp.name;
		lem->rm[lem->start].x = temp.x;
		lem->rm[lem->start].y = temp.y;
	}
	if (lem->end != lem->rooms - 1)
	{
		temp.name = lem->rm[lem->rooms - 1].name;
		temp.x = lem->rm[lem->rooms - 1].x;
		temp.y = lem->rm[lem->rooms - 1].y;
		lem->rm[lem->rooms - 1].name = lem->rm[lem->end].name;
		lem->rm[lem->rooms - 1].x = lem->rm[lem->end].x;
		lem->rm[lem->rooms - 1].y = lem->rm[lem->end].y;
		lem->rm[lem->end].name = temp.name;
		lem->rm[lem->end].x = temp.x;
		lem->rm[lem->end].y = temp.y;
	}
}

void ft_save_room(t_lem_in *lem, char *str)
{
	char **s;

	s = ft_strsplit(str, ' ');
	lem->rm[lem->rooms].name = ft_strdup(s[0]);
	lem->rm[lem->rooms].x = ft_atoi(s[1]);
	lem->rm[lem->rooms++].y = ft_atoi(s[2]);
}

void ft_save_ants(t_lem_in *lem, char *str)
{
	if (((lem->ants = ft_atoi(str)) == 0) || (ft_strcmp(str, "0")
		|| ft_strcmp(str, "-0"))) //not actually equal to 0
		//error
		write(1, "ants #\n", 7);
	//else
		//ok
}