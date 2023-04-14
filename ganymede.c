/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ganymede.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:27:08 by amejia            #+#    #+#             */
/*   Updated: 2023/04/14 22:13:44 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	light_turner(t_parameters *gparams, int *ct, \
	t_philo_params *philo_params)
{
	int	izq_der[2];

	izq_der[0] = *ct - 1;
	izq_der[1] = *ct + 1;
	if (*ct == gparams->n_fork - 1)
		izq_der[1] = 0;
	if (*ct == 0)
		izq_der[0] = gparams->n_fork - 1;
	if (((philo_params[izq_der[0]].n_ate < philo_params[*ct].n_ate) || \
		(philo_params[izq_der[1]].n_ate < philo_params[*ct].n_ate)))
		pthread_mutex_lock(&(gparams->lights[*ct - 1]));
	else
		pthread_mutex_unlock(&(gparams->lights[*ct - 1]));
	(*ct)++;
}

void	*ganymede(void *params)
{
	t_parameters	*gparams;
	t_philo_params	*philo_params;
	int				ct;

	gparams = (t_parameters *)params;
	philo_params = (t_philo_params *)gparams->philo_params;
	ct = 1;
	while (ct <= gparams->n_fork)
	{
		if (ct % 2 == 0)
			pthread_mutex_lock(&(gparams->lights[ct - 1]));
		ct++;
	}
	pthread_mutex_lock(&(gparams->start_mutex));
	gparams->start = 1;
	pthread_mutex_unlock(&(gparams->start_mutex));
	usleep(gparams->time_eat * 500);
	ct = 1;
	while (ct <= gparams->n_fork)
	{
		if (ct % 2 == 0)
			pthread_mutex_unlock(&(gparams->lights[ct -1]));
		ct++;
	}
	return (NULL);
}

int	start_checker(t_parameters *gparams)
{
	int k;
	
	pthread_mutex_lock(&(gparams->start_mutex));
	k = gparams->start;
	pthread_mutex_unlock(&(gparams->start_mutex));
	return (k);
}

int	stop_checker(t_parameters *gparams)
{
	int k;
	
	pthread_mutex_lock(&(gparams->stop_mutex));
	k = gparams->stop;
	pthread_mutex_unlock(&(gparams->stop_mutex));
	return (k);
}