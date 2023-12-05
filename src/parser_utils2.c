/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:25:33 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/05 09:37:53 by eguefif          ###   ########.fr       */
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

char	*skip_float(char *line)
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
	line = skip_float(line);
	line++;
	line = skip_float(line);
	line++;
	line = skip_float(line);
	return (line);
}
