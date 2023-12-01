/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxpelle <maxpelle@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 10:45:11 by maxpelle          #+#    #+#             */
/*   Updated: 2023/12/01 11:13:32 by maxpelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int mrt_error_message(int error)
{
	write(2, "Error\n", 6); 
	if (error == ERR_ARGC)
		write(2, "Invalid number of arguments\n", 28);
	if (error == ERR_FILE_FORMAT)
		write(2, "Invalid file format\n", 20);
	if (error == ERR_NO_FILE)
		write(2, "File does not exist\n", 20);
	return (1);
}
