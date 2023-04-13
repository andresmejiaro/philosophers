/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:27:25 by amejia            #+#    #+#             */
/*   Updated: 2023/04/13 15:30:00 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_state_start(t_philo_params *params)
{
	params->state = 0;
	params->n_ate = 0;
}

void	philo_think(t_philo_params *truep)
{
	int	k;
	int	next;

	//pthread_mutex_lock(&(truep->params->lights[truep->id -1]));
	k = timediff(truep->params->actual_time, truep->params->time_start);
	next = truep->id;
	if (truep->id == truep->params->n_fork)
		next = 0;
	//pthread_mutex_lock(&(truep->params->forks[truep->id - 1]));
	printf("%d ms philo %d took a fork\n", k, truep->id);
	if (truep->params->n_fork == 1)
		usleep((truep->params->time_die + 1) * 990);
	if (truep->params->n_fork > 1)
	{
	//	pthread_mutex_lock(&(truep->params->forks[next]));
		printf("%d ms philo %d took a fork\n", k, truep->id);
		printf("%d ms philo %d is eating\n", k, truep->id);
		truep->time_ate = truep->params->actual_time;
		truep->state = 2;
		truep->n_ate++;
		usleep((truep->params->time_eat)*1000);
	}	
}


void	philo_eat(t_philo_params *truep)
{
	int	k;
	int	next;

	k = timediff(truep->params->actual_time, truep->time_ate);
	if (k > truep->params->time_eat)
	{
		next = truep->id;
		if (truep->id == truep->params->n_fork)
			next = 0;
		pthread_mutex_unlock(&(truep->params->forks[truep->id - 1]));
		pthread_mutex_unlock(&(truep->params->forks[next]));
		pthread_mutex_unlock(&(truep->params->lights[truep->id - 1]));
		k = timediff(truep->params->actual_time, truep->params->time_start);
		printf("%d ms philo %d is sleeping\n", k, truep->id);
		truep->time_slept = truep->params->actual_time;
		truep->state = 1;
	}
}

void	philo_sleep(t_philo_params *truep)
{
	int	k;

	k = timediff(truep->params->actual_time, truep->time_slept);
	if (k > truep->params->time_sleep)
	{
		k = timediff(truep->params->actual_time, truep->params->time_start);
		printf("%d ms philo %d is thinking\n", k, truep->id);
		truep->time_thought = truep->params->actual_time;
		truep->state = 0;
	}
}

void	*philosopher(void *params)
{
	t_philo_params	*truep;

	truep = (t_philo_params *)params;
	philo_state_start(params);
	while (1)
	{
		if (truep->state == 0)
			philo_think(truep);
		if (truep->state == 1)
			philo_sleep(truep);
		if (truep->state == 2)
			philo_eat(truep);
	}
	return (NULL);
}
