/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keys1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:07:53 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/08 12:10:50 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

int	check_camera_hook(t_data *data, int i)
{
	if (i <= 32 && data->camera.mv_flag & i)
	{
		move_cam(data, i);
		return (1);
	}
	if (i <= 512 && data->camera.mv_flag & i)
	{
		rot_cam(data, i);
		return (1);
	}
	if (i <= 2048 && data->camera.mv_flag & i)
	{
		zoom_cam(data, i);
		return (1);
	}
	return (0);
}
