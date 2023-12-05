/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:42:07 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/05 14:10:44 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	mrt_init_data(t_data *data)
{
	data->ambient.ratio = 0;
	data->ambient.color.x = 0;
	data->ambient.color.y = 0;
	data->ambient.color.z = 0;
	data->camera.position.x = 0;
	data->camera.position.y = 0;
	data->camera.position.z = 0;
	data->camera.orientation.x = 0;
	data->camera.orientation.y = 0;
	data->camera.orientation.z = 0;
	data->camera.fov = 55;
	data->light.position.x = 0;
	data->light.position.y = 0;
	data->light.position.z = 0;
	data->light.ratio = 0;
	data->light.color.x = 0;
	data->light.color.y = 0;
	data->light.color.z = 0;
	data->flag = 0;
	data->num_spheres = 0;
	data->num_planes = 0;
	data->num_cylinders = 0;
	data->width = WIN_WIDTH;
	data->height = WIN_HEIGHT;
	data->ratio = (float) data->width / (float) data->height;
}

int	ft_mlx_init(t_data *data)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx = mlx_init(data->width, data->height, "fdf", true);
	data->mlx = mlx;
	mlx_set_window_limit(data->mlx, 0, 0, RES_MAX_WIDTH, RES_MAX_HEIGHT);	
	img = mlx_new_image(data->mlx, RES_MAX_WIDTH, RES_MAX_HEIGHT); 
	data->img = img;
	if (!(data->img) 
		|| (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		return (1);
	mlx_key_hook(data->mlx, &ft_keyhook, data);
	mlx_resize_hook(data->mlx, &ft_resize_hook, data);
	return (0);
}

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

void	ft_resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;
	
	data = (t_data *) param;
	data->width = width;
	data->height = height;
	data->ratio = (float) width / (float) height;
}
