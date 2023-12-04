/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:10:58 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/04 11:04:57 by eguefif          ###   ########.fr       */
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
	ft_printf("ratio %f, color: %f,%f,%f\n", data.ambient.ratio, data.ambient.color.x, data.ambient.color.y, data.ambient.color.z);
	return (0);
}
