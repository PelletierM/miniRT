/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:10:58 by maxpelle          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/12/05 10:11:47 by eguefif          ###   ########.fr       */
=======
/*   Updated: 2023/12/05 10:37:09 by maxpelle         ###   ########.fr       */
>>>>>>> e17a80590e40dedf20d2533f954c09c7269a58a2
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (mrt_check_argv(argc, argv))
		return (1);
	if (mrt_parser(argv[1], &data))
		return (1);
	if (ft_mlx_init(&data) == 1)
		return (mrt_error_message(ERR_MLX_INIT, 0));
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
