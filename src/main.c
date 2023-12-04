/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:10:58 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/04 12:47:49 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (mrt_check_argv(argc, argv))
		return (1);
	mrt_init_data(&data);
	if (mrt_parser(argv[1], &data))
		return (1);
	return (0);
}
