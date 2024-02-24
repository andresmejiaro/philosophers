/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chronos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:27:02 by amejia            #+#    #+#             */
/*   Updated: 2023/04/15 17:20:04 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timediff(struct timeval tim1, struct timeval tim2)
{
	long	w;

	w = 1000000 * (tim1.tv_sec - tim2.tv_sec) + tim1.tv_usec - tim2.tv_usec;
	return (w / 1000);
}

int	timediffexact(struct timeval tim1, struct timeval tim2)
{
	long	w;

	w = 1000000 * (tim1.tv_sec - tim2.tv_sec) + tim1.tv_usec - tim2.tv_usec;
	return (w);
}

void	*chronos(void *params)
{
	t_parameters	*gparams;

	gparams = (t_parameters *)params;
	while (start_checker(gparams) == 0)
	{
		gettimeofday(&(gparams->actual_time), NULL);
		gparams->time_start = gparams->actual_time;
	}
	while (stop_checker(gparams) == 0)
	{
		pthread_mutex_lock(&(gparams->time_mutex));
		gettimeofday(&(gparams->actual_time), NULL);
		pthread_mutex_unlock(&(gparams->time_mutex));
		usleep(300);
	}
	return (NULL);
}

int	timediffs(t_parameters *gparams, struct timeval time)
{
	struct timeval	stime;

	pthread_mutex_lock(&(gparams->time_mutex));
	stime = gparams->actual_time;
	pthread_mutex_unlock(&(gparams->time_mutex));
	return (timediff(stime, time));
}
