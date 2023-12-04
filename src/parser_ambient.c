/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:56:52 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/04 16:22:41 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_ambient(char *line, t_data *data)
{
	if (data->flag & 1)
		return (1);
	line++;
	if (*line != ' ')
		return (1);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_ratio(line, &data->ambient.ratio))
		return (1);
	line = skip_double(line);
	line = skip_spaces(line);
	if (!*line)
		return (1);
	if (get_coord(line, &data->ambient.color))
		return (1);
	line = skip_coord(line);
	line = skip_spaces(line);
	if (*line != '\n')
		return (1);
	data->flag += 1;
	return (0);
}
