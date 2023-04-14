/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:23:58 by amejia            #+#    #+#             */
/*   Updated: 2023/04/14 20:00:02 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_threads(t_parameters *params, t_philo_params *philo_params)
{
	int	ct;

	pthread_create(&(params->threads[params->n_fork]), NULL, chronos, \
		(void *)params);
	pthread_create(&(params->threads[params->n_fork + 1]), NULL, ganymede, \
		(void *)params);
	pthread_create(&(params->threads[params->n_fork + 2]), NULL, kharon, \
		(void *)params);
	ct = 1;
	while (ct <= params->n_fork)
	{
		pthread_create(&(params->threads[ct - 1]), NULL, philosopher, \
			(void *)&(philo_params[ct - 1]));
		ct++;
	}
}

int	main(int argc, char **argv)
{
	t_parameters	params;
	t_philo_params	*philo_params;

	philo_params = NULL;
	start_params(argc, argv, &params, &philo_params);
	if (params.stop == 0)
		check_params(&params);
	if (params.stop == 0)
		launch_threads(&params, philo_params);
	while (params.stop == 0)
		usleep(1000);
	if (params.error != 1)
	{
		join_threads(&params);
		free_memory(&params, philo_params);
	}	
	return (0);
}
