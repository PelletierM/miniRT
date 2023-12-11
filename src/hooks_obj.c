/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 09:54:24 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/11 15:09:44 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_keyhook_move_obj(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_MV_LEFT;
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_MV_LEFT;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_MV_RIGHT;
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_MV_RIGHT;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_MV_FORWARD;
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_MV_FORWARD;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_MV_BACK;
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_MV_BACK;
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_MV_DOWN;
	if (keydata.key == MLX_KEY_Q && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_MV_DOWN;
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_MV_UP;
	if (keydata.key == MLX_KEY_E && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_MV_UP;
}

void	ft_keyhook_rotate_obj(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_ROT_LEFT;
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_ROT_LEFT;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_ROT_RIGHT;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_ROT_RIGHT;
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_ROT_UP;
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_ROT_UP;
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_ROT_DOWN;
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_ROT_DOWN;
}

void	ft_keyhook_scale_obj(mlx_key_data_t keydata, t_data *data)
{
	if (keydata.key == MLX_KEY_P && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_SCALE_UP;
	if (keydata.key == MLX_KEY_P && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_SCALE_UP;
	if (keydata.key == MLX_KEY_O && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_SCALE_DOWN;
	if (keydata.key == MLX_KEY_O && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_SCALE_DOWN;
	if (keydata.key == MLX_KEY_I && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_SCALE_UP_B;
	if (keydata.key == MLX_KEY_I && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_SCALE_UP_B;
	if (keydata.key == MLX_KEY_U && (keydata.action == MLX_PRESS))
		data->nav_flag += OBJ_SCALE_DOWN_B;
	if (keydata.key == MLX_KEY_U && (keydata.action == MLX_RELEASE))
		data->nav_flag = data->nav_flag &~OBJ_SCALE_DOWN_B;
}

int	check_cam_hook(t_data *data, int i)
{
	if (i <= 32 && data->nav_flag & i)
	{
		move_cam(data, i);
		return (1);
	}
	if (i <= 512 && data->nav_flag & i)
	{
		rot_cam(data, i);
		return (1);
	}
	if (i <= 2048 && data->nav_flag & i)
	{
		zoom_cam(data, i);
		return (1);
	}
	return (0);
}

int	check_obj_hook(t_data *data, int i)
{
	if (i <= 32 && data->nav_flag & i)
	{
		move_obj(data, i);
		return (1);
	}
	if (i <= 512 && data->nav_flag & i)
	{
		rot_obj(data, i);
		return (1);
	}
	if (i <= 8192 && data->nav_flag & i)
	{
		scale_obj(data, i);
		return (1);
	}
	return (0);
}
