/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kharon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:27:17 by amejia            #+#    #+#             */
/*   Updated: 2023/04/15 00:53:56 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	n_ate_checker(t_parameters *gparams, t_philo_params philo_params)
{
	int k;
	
	pthread_mutex_lock(&(gparams->counter[philo_params.id - 1]));
	k = philo_params.n_ate;
	pthread_mutex_unlock(&(gparams->counter[philo_params.id - 1]));
	return (k);
}

int	check_food(t_parameters *gparams, t_philo_params *philo_params)
{
	int	ct;
	int	count;

	ct = 1;
	count = 0;
	while (ct <= gparams->n_fork)
	{
		if (n_ate_checker(gparams,philo_params[ct - 1]) >= gparams->n_eat)
			count++;
		ct++;
	}
	if (count >= gparams->n_fork)
	{
		pthread_mutex_lock(&(gparams->stop_mutex));
		gparams->stop = 1;
		pthread_mutex_unlock(&(gparams->stop_mutex));
		return (1);
	}
	return (0);
}

int	check_died(t_parameters *gparams, t_philo_params *philo_params)
{
	int	ct[3];

	ct[1] = 1;
	while (ct[1] <= gparams->n_fork)
	{
		if (timediffs(gparams, philo_params[ct[1] - 1].time_ate) > \
			gparams->time_die)
		{
			pthread_mutex_lock(&(gparams->stop_mutex));
			gparams->stop = 1;
			pthread_mutex_unlock(&(gparams->stop_mutex));
			ct[0] = timediffs(gparams, gparams->time_start);
			ct[2] = 1;
			muted_print("%d ms philo %d has died\n", ct, gparams);
			break ;
		}	
		ct[1]++;
	}
	if (stop_checker(gparams) == 1)
		return (1);
	return (0);
}

void	*kharon(void *params)
{
	t_parameters	*gparams;
	t_philo_params	*philo_params;

	gparams = (t_parameters *)params;
	philo_params = (t_philo_params *)gparams->philo_params;
	while (stop_checker(gparams) == 0)
	{
		if (check_died(gparams, philo_params) == 1)
			break ;
		if (gparams->n_eat != INT32_MAX && \
			check_food(gparams, philo_params) == 1)
			break ;
		usleep(2000);
	}
	return (NULL);
}
