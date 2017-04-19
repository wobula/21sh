/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_management                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 11:39:00 by rschramm          #+#    #+#             */
/*   Updated: 2017/03/23 09:28:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char ***input_management(char *line)
{
	char	**split_commands;
	char	***split_args;
	int		x;
	int		y;

	x = 0;
	split_commands = ft_strsplit(line, ';');
	while (split_commands[x])
		x++;
	split_args = (char ***)ft_memalloc(sizeof(char **) * (x + 1));
	split_args[x] = NULL;
	y = 0;
	while (y <= x)
	{
		split_args[y] = ft_strsplit(split_commands[y], ' ');
		ft_strdel(&split_commands[y]);
		y++;
	}
	free(split_commands);
	split_commands = NULL;
	return (split_args);
}