/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:52:51 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/01 13:46:33 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void 	init_values(t_data *data);
int		get_data(char *file, t_data *data);
int		parse_line(char *line, t_data *data);
int		check_data(t_data *data);

int	mrt_parser(char *file, t_data *data)
{
	init_values(data);
	return (get_data(file, data));
}

void init_values(t_data *data)
{
	data->ambient.ratio = 0;
	data->camera.fov = 0;
	data->light.ratio = 0;
}

int	get_data(char *file, t_data *data)
{
	int		fd;
	char	*line;
	int		i;
	int		retval;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	line = get_next_line(fd);
	while (line && i < MAX_LINES)
	{
		retval = parse_line(line, data);
		free(line);
		if (!retval)
		{
			mrt_error_message(ERR_LINE_FORMAT, i);
			break ;
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (retval);
}

int	parse_line(char *line, t_data *data)
{
	if (!check_line(line))
	{
		if (set_values(line, data))
			return (1);
		if (check_data(data))
			return (1);
	}
	else
		return (1);
	return (0);
}

int		check_data(t_data *data)
{
	(void) data;
	return (0);
}
