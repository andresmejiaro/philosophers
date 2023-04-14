/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 23:11:58 by amejia            #+#    #+#             */
/*   Updated: 2023/04/14 23:13:15 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_memory(t_parameters *params, t_philo_params *philo_params)
{
	free(params->threads);
	free(params->forks);
	free(params->lights);
	free(philo_params);
}
void	join_threads(t_parameters *params)
{
	int	k;

	k = 0;
	while (k < params->n_fork + 3)
	{
		pthread_join(params->threads[k], NULL);
		k++;
	}
}
