/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:07:53 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/11 10:09:39 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_keyhook_move(mlx_key_data_t keydata, t_data *data)
{
	if (data->nav_mode.obj == OBJ_CAM)
		ft_keyhook_move_cam(keydata, data);
}

void	ft_keyhook_rotate(mlx_key_data_t keydata, t_data *data)
{
	if (data->nav_mode.obj == OBJ_CAM)
		ft_keyhook_rotate_cam(keydata, data);
}

void	ft_keyhook_scale(mlx_key_data_t keydata, t_data *data)
{
	if (data->nav_mode.obj == OBJ_CAM)
		ft_keyhook_zoom_cam(keydata, data);
}
