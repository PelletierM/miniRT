/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:48:22 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/06 16:38:40 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	ft_keyhook_move_camera(keydata, data);
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

void	ft_keyhook_move_camera(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		data->camera.mv_flag +=1;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -=1;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		data->camera.mv_flag +=2;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -=2;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		data->camera.mv_flag +=4;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -=4;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		data->camera.mv_flag +=8;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -=8;
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_PRESS))
		data->camera.mv_flag +=16;
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -=16;
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_PRESS))
		data->camera.mv_flag +=32;
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -=32;
}

void	ft_gen_hook(void *ptr)
{
	char	change;
	t_data	*data;
	
	data = (t_data *) ptr;
	change = 0;
	if (data->camera.mv_flag & 1)
	{
		data->camera.position = vsub(data->camera.position, data->camera.x_axis);
		change = 1;
	}
	if (data->camera.mv_flag & 2)
	{
		data->camera.position = vadd(data->camera.position, data->camera.x_axis);
		change = 1;
	}
	if (data->camera.mv_flag & 4)
	{
		data->camera.position = vadd(data->camera.position, data->camera.z_axis);
		change = 1;
	}
	if (data->camera.mv_flag & 8)
	{
		data->camera.position = vsub(data->camera.position, data->camera.z_axis);
		change = 1;
	}
	if (data->camera.mv_flag & 16)
	{
		data->camera.position = vadd(data->camera.position, data->camera.y_axis);
		change = 1;
	}
	if (data->camera.mv_flag & 32)
	{
		data->camera.position = vsub(data->camera.position, data->camera.y_axis);
		change = 1;
	}
	if (change)
		render(data);
}

