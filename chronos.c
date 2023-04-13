/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:27:02 by amejia            #+#    #+#             */
/*   Updated: 2023/04/13 15:24:45 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timediff(struct timeval tim1, struct timeval tim2)
{
	long	w;

	w = 1000000 * (tim1.tv_sec - tim2.tv_sec) + tim1.tv_usec - tim2.tv_usec;
	return (w / 1000);
}

void *chronos(void *params)
{
	t_parameters *gparams;
	
	gparams = (t_parameters *)params;
	gettimeofday(&(gparams->actual_time), NULL);
	gparams->time_start = gparams->actual_time;
	while (gparams->stop == 0)
	{
		gettimeofday(&(gparams->actual_time), NULL);
		usleep(3333);
	}
	return (NULL);
}