/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:27:25 by amejia            #+#    #+#             */
/*   Updated: 2023/04/19 18:53:20 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_think2(t_philo_params *truep, int next)
{
	int	k[3];

	if (truep->params->n_fork > 1)
	{
		if (truep->params->n_fork == 1)
		{
			usleep(truep->params->time_die * 1000);
			return ;
		}
		pthread_mutex_lock(&(truep->params->forks[next]));
		if (stop_checker(truep->params) == 1)
			return ;
		truep->time_ate = truep->params->actual_time;
		truep->state = 2;
		pthread_mutex_lock(&(truep->params->counter[truep->id -1]));
		truep->n_ate++;
		pthread_mutex_unlock(&(truep->params->counter[truep->id -1]));
		k[1] = truep->id;
		k[2] = 0;
		muted_print("%d ms philo %d took a fork\n", k, truep->params);
		muted_print("%d ms philo %d is eating\n", k, truep->params);
		usleep((truep->params->time_eat) * 990);
	}	
}

void	philo_think(t_philo_params *truep)
{
	int	k[3];
	int	next;

	pthread_mutex_lock(&(truep->params->lights[truep->id -1]));
	if (stop_checker(truep->params) == 1)
		return ;
	next = truep->id;
	if (truep->id == truep->params->n_fork)
		next = 0;
	pthread_mutex_lock(&(truep->params->forks[truep->id - 1]));
	if (stop_checker(truep->params) == 1)
		return ;
	k[1] = truep->id;
	k[2] = 0;
	muted_print("%d ms philo %d took a fork\n", k, truep->params);
	if (truep->params->n_fork == 1)
	{
		usleep((truep->params->time_die) * 1100);
		return ;
	}
	philo_think2(truep, next);
}

void	philo_eat(t_philo_params *truep)
{
	int	k[3];
	int	next;

	k[0] = timediffs(truep->params, truep->time_ate);
	if (k[0] > truep->params->time_eat && stop_checker(truep->params) == 0)
	{
		pthread_mutex_unlock(&(truep->params->lights[truep->id - 1]));
		next = truep->id;
		if (truep->id == truep->params->n_fork)
			next = 0;
		pthread_mutex_unlock(&(truep->params->forks[truep->id - 1]));
		pthread_mutex_unlock(&(truep->params->forks[next]));
		k[1] = truep->id;
		k[2] = 0;
		muted_print("%d ms philo %d is sleeping\n", k, truep->params);
		truep->time_slept = truep->params->actual_time;
		truep->state = 1;
		usleep(truep->params->time_sleep * 1000);
	}
}

void	philo_sleep(t_philo_params *truep)
{
	int	k[3];

	k[0] = timediffs(truep->params, truep->time_slept);
	if (k[0] > truep->params->time_sleep && stop_checker(truep->params) == 0)
	{
		k[1] = truep->id;
		k[2] = 0;
		muted_print("%d ms philo %d is thinking\n", k, truep->params);
		truep->time_thought = truep->params->actual_time;
		truep->state = 0;
	}
}

void	*philosopher(void *params)
{
	t_philo_params	*truep;
	int				next;

	truep = (t_philo_params *)params;
	while (start_checker(truep->params) == 0)
		usleep(100);
	while (stop_checker(truep->params) == 0)
	{
		if (truep->state == 0)
			philo_think(truep);
		if (truep->state == 1)
			philo_sleep(truep);
		if (truep->state == 2)
			philo_eat(truep);
		usleep(300);
	}
	next = truep->id;
	if (truep->id == truep->params->n_fork)
		next = 0;
	pthread_mutex_unlock(&(truep->params->lights[truep->id - 1]));
	pthread_mutex_unlock(&(truep->params->forks[truep->id - 1]));
	pthread_mutex_unlock(&(truep->params->forks[next]));
	return (NULL);
}
