/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:32:19 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/14 08:44:03 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	set_light2(char *line, t_data *data);

int	set_light(char *line, t_data *data)
{
	if (data->flag & 4)
		return (4);
	line++;
	if (*line != ' ')
		return (1);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->light.position))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	return (set_light2(line, data));
}

int	set_light2(char *line, t_data *data)
{
	if (!*line)
		return (1);
	if (!ft_isdigit(*line) && *line != '-' && *line != '+')
		return (1);
	data->light.ratio = get_float(line);
	line = skip_float(line);
	line = skip_spaces(line);
	if (get_color(line, &data->light.color))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (*line != '\n')
		return (1);
	data->flag += 4;
	return (0);
}
