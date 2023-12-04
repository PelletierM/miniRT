/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:25:33 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/04 16:29:46 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*skip_spaces(char *line)
{
	while (*line && *line == ' ')
		line++;
	return (line);
}

char	*skip_digits(char *line)
{
	while (*line && ft_isdigit(*line))
		line++;
	return (line);
}

char	*skip_double(char *line)
{
	if (*line && (*line == '+' || *line == '-'))
		line++;
	line = skip_digits(line);
	if (*line && *line != '.')
		return (line);
	line++;
	line = skip_digits(line);
	return (line);
}

char	*skip_coord(char *line)
{
	if (*line == '+' || *line == '-')
		line++;
	line = skip_double(line);
	line++;
	line = skip_double(line);
	line++;
	line = skip_double(line);
	return (line);
}