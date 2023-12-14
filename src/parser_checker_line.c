/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 11:33:08 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/14 13:20:14 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		check_characters(char *line);
char	*is_valid_identifier(char *line);

int	check_line(char *line)
{
	if (ft_strncmp(line, "tx", 2) == 0)
		return (0);
	if (check_characters(line))
		return (1);
	return (0);
}

int	check_characters(char *line)
{
	line = is_valid_identifier(line);
	if (!line)
		return (1);
	while (*line)
	{
		if (!ft_strchr(VALID_CHARS, *line))
			return (1);
		line++;
	}
	return (0);
}

char	*is_valid_identifier(char *line)
{
	int	i;

	i = 0;
	line = skip_spaces(line);
	if (!*line || !*(line + 1))
		return (0);
	if (line[i] == 'A' || line[i] == 'C' || line[i] == 'L')
		line++;
	else if (!ft_strncmp(&line[i], "sp", 2)
		|| !ft_strncmp(&line[i], "cy", 2)
		|| !ft_strncmp(&line[i], "pl", 2)
		|| !ft_strncmp(&line[i], "tx", 2)
		|| !ft_strncmp(&line[i], "mt", 2))
		line += 2;
	else
		return (0);
	line = skip_spaces(line);
	return (line);
}
