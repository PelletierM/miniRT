/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eguefif <eguefif@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:00:57 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/01 14:19:27 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	get_double(char *line);

int		get_ratio(char *line, double *ratio)
{
	double	value;

	if (!*line && !*(line + 1))
		return (1);
	value = get_double(line);
	if (value >= 0 && value <= 1)
		*ratio = value;
	else
		return (1);
	return (0);
}

double	get_double(char *line)
{
	int		integer;
	double	retval;
	int		div;
	
	integer = ft_atoi(line);
	if (*line && (*line == '+' || *line == '-'))
		line++;
	while (*line && ft_isdigit(*line))
		line++;
	if (*line != '.')
		return ((double) integer);
	line++;
	div = 10;
	retval = 0;
	while (ft_isdigit(*line) && div < 10000)
	{
		retval += (double)(*line - '0') / div;
		line++;
		div *= 10;
	}
	return ((double) integer + retval); 
}

int		get_color(char *line, unsigned int *color)
{
	int				i;
	unsigned int	clr[3];

	i = 0;
	while (i < 3)
	{
		clr[i] = ft_atoi(line);
		if (clr[i] < 0 || clr[i] > 255)
			return (1);
		if (*line == '+')
			line++;
		line = skip_digits(line);
		if (*line != ',' && i < 2)
			return (1);
		i++;
	}
	*color = get_rgba(clr[0], clr[1], clr[2], 255);
	return (0);
}

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

char	*skip_color(char *line)
{
	if (*line == '+')
		line++;
	line = skip_digits(line);
	line++;
	line = skip_digits(line);
	line++;
	line = skip_digits(line);
	return (line);
}
