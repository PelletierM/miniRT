/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:00:04 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/05 10:11:51 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	fill_bg(t_data *data)
{
	int	x;
	int	y;
	int	red;
	int	green;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			red = x * 255 / WIN_WIDTH;
			green = y * 255 / WIN_HEIGHT;
			put_pixel(data, x, y, get_rgba(red, green, 0, 255));
			y++;
		}
		x++;
	}
}

void	put_pixel(t_data *data, float x, float y, unsigned int color)
{
	if (x >= WIN_WIDTH || x < 0 || y >= WIN_HEIGHT || y < 0)
		return ;
	mlx_put_pixel(data->img, x, y, color);
}
