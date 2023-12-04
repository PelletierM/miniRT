/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:45:11 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/04 09:00:43 by eguefif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int mrt_error_message(int error, int line)
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
	return (1);
}
