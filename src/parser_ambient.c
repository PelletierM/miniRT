/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:56:52 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/04 11:27:40 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_ambient(char *line, t_data *data)
{
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
	return (0);
}
