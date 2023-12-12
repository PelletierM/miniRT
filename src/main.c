/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:10:58 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/12 09:06:45 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void		display_delta(struct timeval t_start);
long int	get_time_in_micro(struct timeval t);

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
	return (0);
}

void	render(t_data *data)
{
	int			i;
	t_thread	threads[THREAD_MAX];
	struct timeval	start;

	i = 0;
	gettimeofday(&start, NULL);
	while (i < THREAD_MAX)
	{
		threads[i].id = i;
		threads[i].data = data;
		if (pthread_create(&threads[i].thread,
				NULL, render_thread, &threads[i]) != 0)
		{
			printf("Error thread\n");
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
	display_delta(start);
}

void	display_delta(struct timeval t_start)
{
	struct timeval	t_end;
	long int		start;	
	long int		end;	
	float			delta;

	gettimeofday(&t_end, NULL);
	start = get_time_in_micro(t_start);
	end = get_time_in_micro(t_end);
	delta = (end - start) / 1000;
	ft_printf("Rendered in : %fms\n", delta);
}

long int	get_time_in_micro(struct timeval t)
{
	return (t.tv_sec * 1000 * 1000 + t.tv_usec);
}
