/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 15:10:58 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/04 16:18:05 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	i = 0;
	t_data	data;
	if (mrt_check_argv(argc, argv))
		return (1);
	if (mrt_parser(argv[1], &data))
		return (1);
	if (data.flag & 1)
		printf("ratio %f, color: %f,%f,%f\n", data.ambient.ratio, data.ambient.color.x, data.ambient.color.y, data.ambient.color.z);
	if (data.flag & 2)
		printf("positioin %f %f %f, orientation: %f,%f,%f FOV: %f\n", data.camera.position.x, data.camera.position.y, data.camera.position.z, 
				data.camera.orientation.x, data.camera.orientation.y, data.camera.orientation.z, data.camera.fov);
	if (data.flag & 4)
		printf("position: %f %f %f, ratio %f, color: %f,%f,%f\n", data.light.position.x, data.light.position.y, data.light.position.z, data.light.ratio,
				data.light.color.x, data.light.color.y, data.light.color.z);

	printf("Spheres\n");
	while (i < data.num_spheres)
	{
		printf("position %f %f %f, color: %f,%f,%f diameter: %f\n", data.spheres[i].position.x, data.spheres[i].position.y, data.spheres[i].position.z, 
				data.spheres[i].color.x, data.spheres[i].color.y, data.spheres[i].color.z, data.spheres[i].diameter);
		i++;
	}
	i = 0;
	printf("Cylinders\n");
	while (i < data.num_cylinders)
	{
		printf("position %f %f %f, vector normalized: %f,%f,%f diameter: %f, height: %f, color: %f %f %f\n",
				data.cylinders[i].position.x, data.cylinders[i].position.y, data.cylinders[i].position.z, 
				data.cylinders[i].orientation.x, data.cylinders[i].orientation.y, data.cylinders[i].orientation.z, 
				data.cylinders[i].diameter, data.cylinders[i].height,
				data.cylinders[i].color.x, data.cylinders[i].color.y, data.cylinders[i].color.z);
		i++;
	}
	i = 0;
	printf("Planes\n");
	while (i < data.num_planes)
	{
		printf("position %f %f %f, orientation: %f,%f,%f color: %f %f %f\n",
				data.planes[i].position.x, data.planes[i].position.y, data.planes[i].position.z, 
				data.planes[i].orientation.x, data.planes[i].orientation.y, data.planes[i].orientation.z, 
				data.planes[i].color.x, data.planes[i].color.y, data.planes[i].color.z);
		i++;
	}
	return (0);
}
