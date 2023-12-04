/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:10:58 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/04 17:06:01 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		ft_mlx_init(t_data *data);
void	ft_keyhook(mlx_key_data_t keydata, void *param);

int	main(int argc, char *argv[])
{
	t_data	data;

	if (mrt_check_argv(argc, argv))
		return (1);
	if (mrt_parser(argv[1], &data))
		return (1);
	if (ft_mlx_init(&data) == 1)
		return (mrt_error_message(ERR_MLX_INIT, 0));
	ft_fill_bg(&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}

int	ft_mlx_init(t_data *data)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "fdf", true);
	data->mlx = mlx;
	mlx_set_window_limit(data->mlx, WIN_WIDTH, WIN_HEIGHT,
		WIN_WIDTH, WIN_HEIGHT);
	img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT); 
	data->img = img;
	if (!(data->img) 
		|| (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		return (1);
	mlx_key_hook(data->mlx, &ft_keyhook, data);
	return (0);
}

void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}
