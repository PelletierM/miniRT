/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:00:57 by eguefif           #+#    #+#             */
/*   Updated: 2023/12/04 16:30:05 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	get_decimal_for_double(char *line);

int	get_ratio(char *line, double *ratio)
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
	double	neg;

	neg = 1;
	if (*line == '-')
		neg = -1;
	integer = ft_atoi(line);
	if (integer < 0)
		integer *= -1;
	if (*line && (*line == '+' || *line == '-'))
		line++;
	while (*line && ft_isdigit(*line))
		line++;
	if (*line != '.')
		return (neg * (double) integer);
	line++;
	retval = get_decimal_for_double(line);
	return (neg * ((double) integer + retval));
}

static double	get_decimal_for_double(char *line)
{
	double	retval;
	int		div;

	div = 10;
	retval = 0;
	while (ft_isdigit(*line) && div < 10000)
	{
		retval += (double)(*line - '0') / div;
		line++;
		div *= 10;
	}
	return (retval);
}

int	get_coord(char *line, t_vector *vector)
{
	int				i;
	double			v[3];

	i = 0;
	while (i < 3)
	{
		if (!ft_isdigit(*line) && *line != '-' && *line != '+')
			return (1);
		v[i] = get_double(line);
		if (*line == '+')
			line++;
		line = skip_double(line);
		if (*line != ',' && i < 2)
			return (1);
		if (i < 2)
			line++;
		i++;
	}
	vector->x = v[0];
	vector->y = v[1];
	vector->z = v[2];
	return (0);
}
