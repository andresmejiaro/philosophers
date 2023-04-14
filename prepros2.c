/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepros2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:33:03 by amejia            #+#    #+#             */
/*   Updated: 2023/04/15 00:42:07 by amejia           ###   ########.fr       */
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

void muted_print(char *str, int *numb, t_parameters *gparams)
{
	pthread_mutex_lock(&(gparams->print_mutex));
	if (gparams->print == 1)
		printf(str, numb[0], numb[1]);
	if (numb[3] == 1)
		gparams->print = 0;
	pthread_mutex_unlock(&(gparams->print_mutex));
}
