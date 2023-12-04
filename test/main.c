/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:10:58 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/04 15:14:06 by eguefif          ###   ########.fr       */
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
	if (data.flag & 1)
		ft_printf("ratio %f, color: %f,%f,%f\n", data.ambient.ratio, data.ambient.color.x, data.ambient.color.y, data.ambient.color.z);
	if (data.flag & 2)
		ft_printf("positioin %f %f %f, orientation: %f,%f,%f FOV: %f\n", data.camera.position.x, data.camera.position.y, data.camera.position.z, 
				data.camera.orientation.x, data.camera.orientation.y, data.camera.orientation.z, data.camera.fov);
	if (data.flag & 4)
		ft_printf("position: %f %f %f, ratio %f, color: %f,%f,%f\n", data.light.position.x, data.light.position.y, data.light.position.z, data.light.ratio,
				data.light.color.x, data.light.color.y, data.light.color.z);

	int	i = 0;
	while (i < data.num_spheres)
	{
		ft_printf("position %f %f %f, color: %f,%f,%f diameter: %f\n", data.spheres[i].position.x, data.spheres[i].position.y, data.spheres[i].position.z, 
				data.spheres[i].color.x, data.spheres[i].color.y, data.spheres[i].color.z, data.spheres[i].diameter);
		i++;
	}
	return (0);
}
