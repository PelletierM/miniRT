/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:48:22 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/08 11:11:05 by maxpelle         ###   ########.fr       */
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

void	ft_keyhook_move_camera(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_MV_LEFT;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_MV_LEFT;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_MV_RIGHT;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_MV_RIGHT;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_MV_FORWARD;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_MV_FORWARD;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_MV_BACK;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_MV_BACK;
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_MV_DOWN;
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_MV_DOWN;
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_MV_UP;
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_MV_UP;
}

void	ft_keyhook_rotate_camera(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_ROT_LEFT;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_ROT_LEFT;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_ROT_RIGHT;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_ROT_RIGHT;
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_ROT_UP;
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_ROT_UP;
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_ROT_DOWN;
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_ROT_DOWN;
}

void	ft_keyhook_zoom_camera(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_P && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_ZOOM_IN;
	if (keydata.key == MLX_KEY_P && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_ZOOM_IN;
	if (keydata.key == MLX_KEY_O && (keydata.action == MLX_PRESS))
		data->camera.mv_flag += CAM_ZOOM_OUT;
	if (keydata.key == MLX_KEY_O && (keydata.action == MLX_RELEASE))
		data->camera.mv_flag -= CAM_ZOOM_OUT;
}

void	ft_gen_hook(void *ptr)
{
	char	change;
	t_data	*data;
	int		i;
	
	data = (t_data *) ptr;
	change = 0;
	i = 1;
	while (i <= 32)
	{
		if (data->camera.mv_flag & i)
		{
			move_camera(data, i);
			change = 1;
		}
		i *= 2;
	}
	while (i <= 512)
	{
		if (data->camera.mv_flag & i)
		{
			rotate_camera(data, i);
			change = 1;
		}
		i *= 2;
	}
	while (i <= 2048)
	{
		if (data->camera.mv_flag & i)
		{
			zoom_camera(data, i);
			change = 1;
		}
		i *= 2;
	}
	if (change)
		render(data);
}

