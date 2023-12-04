/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:52:51 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/04 16:28:35 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		get_data(char *file, t_data *data);
int		parse_line(char *line, t_data *data);

int	mrt_parser(char *file, t_data *data)
{
	mrt_init_data(data);
	return (get_data(file, data));
}

int	get_data(char *file, t_data *data)
{
	int		fd;
	char	*line;
	int		i;
	int		retval;

	retval = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	line = get_next_line(fd);
	while (line && i < MAX_LINES)
	{
		retval = parse_line(line, data);
		free(line);
		if (retval)
		{
			mrt_error_message(ERR_LINE_FORMAT, i + 1);
			break ;
		}
		line = get_next_line(fd);
		i++;
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
		if (check_data(*data))
			return (1);
	}
	else
		return (1);
	return (0);
}
