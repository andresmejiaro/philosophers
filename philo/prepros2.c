/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepros2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:33:03 by amejia            #+#    #+#             */
/*   Updated: 2023/04/15 23:58:20 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_params(t_parameters *params)
{
	int	k;

	if (params->threads == 0 || params->forks == 0 || params->lights == 0 || \
		params->n_fork == 0 || params->counter == 0)
	{
		if (params->counter != 0)
			free(params->counter);
		if (params->threads != 0)
			free(params->threads);
		if (params->forks != 0)
			free(params->forks);
		if (params->lights != 0)
			free(params->lights);
		exit_error_read(0, params);
	}
	k = 0;
}

void	muted_print(char *str, int *numb, t_parameters *gparams)
{
	int	auth;

	auth = 0;
	pthread_mutex_lock(&(gparams->print_mutex));
	if (gparams->print == 1)
		auth = 1;
	if (numb[2] == 1)
		gparams->print = 0;
	if (auth == 1)
	{
		numb[0] = timediffs(gparams, gparams->time_start);
		printf(str, numb[0], numb[1]);
	}
	pthread_mutex_unlock(&(gparams->print_mutex));
}
