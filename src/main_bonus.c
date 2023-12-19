/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:10:58 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/18 14:06:25 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void		display_delta(struct timeval t_start);
long int	get_time_in_micro(struct timeval t);
void		delete_textures(t_data data);
void		launch_threads(t_data *data);

int	main(int argc, char *argv[])
{
	t_data	data;

	if (mrt_check_argv(argc, argv))
		return (1);
	if (mrt_parser(argv[1], &data))
		return (1);
	if (ft_mlx_init(&data) == 1)
		return (mrt_error_message(ERR_MLX_INIT, 0));
	render(&data);
	mlx_loop_hook(data.mlx, ft_gen_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	if (data.accumulator)
		free(data.accumulator);
	delete_textures(data);
	return (0);
}

void	render(t_data *data)
{
	if (data->samples == 1)
	{
		ft_bzero(data->accumulator, sizeof(t_vector)
			* data->width * data->height);
		mrt_create_cam(data);
	}
	launch_threads(data);
	update_image(data);
	data->samples++;
}

void	launch_threads(t_data *data)
{
	t_thread		threads[THREAD_MAX];
	int				i;

	i = 0;
	while (i < THREAD_MAX)
	{
		threads[i].id = i;
		threads[i].data = data;
		if (pthread_create(&threads[i].thread,
				NULL, render_thread, &threads[i]) != 0)
		{
			write(2, "Error thread\n", 13);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < THREAD_MAX)
	{
		pthread_join(threads[i].thread, NULL);
		i++;
	}
}

void	delete_textures(t_data data)
{
	int		i;

	i = 0;
	while (i < data.num_materials)
	{
		if (data.materials[i].texture_flag == 1)
		{
			mlx_delete_texture(data.materials[i].img);
			mlx_delete_texture(data.materials[i].norm_img);
		}
		i++;
	}
}
