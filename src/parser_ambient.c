/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:56:52 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/01 14:12:19 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_ambient(char *line, t_data *data)
{
	line = skip_spaces(line);
	if (!*line && get_ratio(line, &data->ambient.ratio))
		return (1);
	get_ratio(line, &data->ambient.ratio);
	line = skip_double(line);
	skip_spaces(line);
	if (!*line && get_color(line, &data->ambient.color))
		return (1);
	line = skip_color(line);
	skip_spaces(line);
	if (*line != '\n')
		return (1);
	return (0);
}
