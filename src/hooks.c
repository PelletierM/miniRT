/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:48:22 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/18 08:56:05 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
	ft_keyhook_move_obj(keydata, data);
	ft_keyhook_rotate_obj(keydata, data);
	ft_keyhook_scale_obj(keydata, data);
	ft_keyhook_mode(keydata, data);
}

void	ft_mouse_hook(enum mouse_key mouse_key, enum action action,
		enum modifier_key modifier_key, void *param)
{
	t_data	*data;

	(void) modifier_key;
	data = (t_data *) param;
	if (mouse_key == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		ft_get_click_target(data);
	return ;
}

void	ft_resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	data->width = width;
	data->height = height;
	data->ratio = (float) width / (float) height;
	data->samples = 1;
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
	while (i <= 32768)
	{
		if ((data->nav_mode.obj == OBJ_CAM && check_cam_hook(data, i))
			|| (data->nav_mode.obj >= OBJ_SPHERE
				&& data->nav_mode.obj <= OBJ_LIGHT && check_obj_hook(data, i)))
			change = 1;
		i *= 2;
	}
	if (change)
		data->samples = 1;
	render(data);
}
