/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:31:07 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/11 14:48:43 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_keyhook_mode(mlx_key_data_t keydata, t_data *data)
{
	if (data->nav_mode.obj != OBJ_CAM && keydata.key == MLX_KEY_C 
		&& (keydata.action == MLX_PRESS))
	{
		data->nav_mode.obj = OBJ_CAM;
		data->nav_mode.i = 0;
		data->nav_flag = 0;
	}
	if (data->nav_mode.obj != OBJ_LIGHT && keydata.key == MLX_KEY_L 
		&& (keydata.action == MLX_PRESS))
	{
		data->nav_mode.obj = OBJ_LIGHT;
		data->nav_mode.i = 0;
		data->nav_flag = 0;
	}

}

