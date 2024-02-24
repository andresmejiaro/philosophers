/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepros3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 23:10:42 by amejia            #+#    #+#             */
/*   Updated: 2023/04/15 23:49:03 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_params3(t_parameters *params, t_philo_params *philo_params)
{
	int				ct;
	struct timeval	time;

	ct = 1;
	gettimeofday(&time, NULL);
	while (ct <= params->n_fork && philo_params != NULL \
		&& params->lights != NULL && params->forks != NULL && \
		params->counter != NULL)
	{
		pthread_mutex_init(&(params->counter[ct - 1]), NULL);
		pthread_mutex_init(&(params->lights[ct - 1]), NULL);
		pthread_mutex_init(&(params->forks[ct - 1]), NULL);
		philo_params[ct - 1].id = ct ;
		philo_params[ct - 1].params = params;
		philo_params[ct - 1].state = 0;
		philo_params[ct - 1].n_ate = 0;
		philo_params[ct - 1].time_ate = time;
		ct++;
	}
}

void	start_params2(t_parameters *params, t_philo_params *philo_params)
{
	params->counter = malloc(params->n_fork * sizeof(pthread_mutex_t));
	params->print = 1;
	params->stop = 0;
	params->start = 0;
	params->philo_params = philo_params;
	pthread_mutex_init(&(params->time_mutex), NULL);
	pthread_mutex_init(&(params->start_mutex), NULL);
	pthread_mutex_init(&(params->stop_mutex), NULL);
	pthread_mutex_init(&(params->write_mutex), NULL);
	pthread_mutex_init(&(params->print_mutex), NULL);
	start_params3(params, philo_params);
}

void	start_params(int argc, char **argv, t_parameters *params, \
		t_philo_params **philo_params)
{
	if (check_valid(argc, argv) != 0)
	{
		exit_error_read(1, params);
		return ;
	}
	params->n_fork = ft_atoi(argv[1]);
	params->time_die = ft_atoi(argv[2]);
	params->time_eat = ft_atoi(argv[3]);
	params->time_sleep = ft_atoi(argv[4]);
	if (argc >= 6)
		params->n_eat = ft_atoi(argv[5]);
	else
		params->n_eat = INT32_MAX;
	if (params->n_fork <= 0 || params->time_die <= 0 || params->time_eat <= 0 \
		|| params->time_sleep <= 0 || params->n_eat <= 0)
	{
		exit_error_read(1, params);
		return ;
	}
	params->threads = malloc((params->n_fork + 4) * sizeof(pthread_t));
	params->forks = malloc(params->n_fork * sizeof(pthread_mutex_t));
	params->lights = malloc(params->n_fork * sizeof(pthread_mutex_t));
	*philo_params = (t_philo_params *)malloc(params->n_fork * \
		sizeof(t_philo_params));
	start_params2(params, *philo_params);
}
