/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:52:51 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/18 15:50:18 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int		get_data(char *file, t_data *data);
int		parse_line(char *line, t_data *data);
int		check_unicity(t_data *data);

int	mrt_parser(char *file, t_data *data)
{
	int		retval;

	mrt_init_data(data);
	retval = get_data(file, data);
	if (retval)
		return (1);
	return (check_unicity(data));
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
	if (!ft_strncmp(line, "\n", 1) || !ft_strncmp(line, "#", 1))
		return (0);
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

int	check_unicity(t_data *data)
{
	if (data->flag == 7)
		return (0);
	mrt_error_message(ERR_ELEM, 0);
	return (1);
}
