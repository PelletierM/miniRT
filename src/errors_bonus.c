/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:45:11 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/05 10:02:37 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	mrt_error_message(int error, int line)
{
	write(2, "Error\n", 6); 
	if (error == ERR_ARGC)
		write(2, "Invalid number of arguments\n", 28);
	if (error == ERR_FILE_FORMAT)
		write(2, "Invalid file format\n", 20);
	if (error == ERR_NO_FILE)
		write(2, "File does not exist\n", 20);
	if (error == ERR_LINE_FORMAT)
		ft_dprintf(2, "Invalid line format (%d)\n", line);
	if (error == ERR_MLX_INIT)
		ft_dprintf(2, "Could not initiate MLX image\n");
	if (error == ERR_DIV_ZERO)
		ft_dprintf(2, "Division by zero\n");
	return (1);
}
