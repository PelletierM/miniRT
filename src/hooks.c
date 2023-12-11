/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:48:22 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/11 11:10:03 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_keyhook_move_camera(mlx_key_data_t keydata, t_data *data);
void	ft_keyhook_rotate_camera(mlx_key_data_t keydata, t_data *data);
void	ft_keyhook_zoom_camera(mlx_key_data_t keydata, t_data *data);
int		check_camera_hook(t_data *data, int i);

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	ft_keyhook_move_camera(keydata, data);
	ft_keyhook_rotate_camera(keydata, data);
	ft_keyhook_zoom_camera(keydata, data);
}

void	ft_resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	data->width = width;
	data->height = height;
	data->ratio = (float) width / (float) height;
	render(data);
}

void	ft_gen_hook(void *ptr)
{
	char	change;
	t_data	*data;
	int		i;

	data = (t_data *) ptr;
	change = 0;
	i = 1;
	while (i <= 2048)
	{
		if (check_camera_hook(data, i))
			change = 1;
		i *= 2;
	}
	if (change)
		render(data);
}
