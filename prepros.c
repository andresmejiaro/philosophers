/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepros.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:46:01 by amejia            #+#    #+#             */
/*   Updated: 2023/04/13 15:13:44 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_digit_str(char *str)
{
	int	neg;

	neg = 0;
	if (*str == '-')
		neg = 1;
	if (*str == '-')
		str++;
	while (*str == ' ')
		str++;
	if (ft_strlen(str) > 10)
		return (0);
	else if (ft_strlen(str) < 10)
		return (1);
	else if (neg == 1 && (ft_strncmp(str, "2147483648", -1) > 0))
		return (0);
	else if (ft_strncmp(str, "2147483647", -1) > 0)
		return (0);
	return (1);
}

int	check_valid(int argc, char **argv)
{
	int	cnt[2];
	int	signs;

	cnt[0] = 0;
	while (cnt[0]++ < argc -1)
	{
		cnt[1] = 0;
		signs = 0;
		while (argv[cnt[0]][cnt[1]] != '\0')
		{
			if (argv[cnt[0]][cnt[1]] == '+' || argv[cnt[0]][cnt[1]] == '-')
			{
				signs ++;
				cnt[1]++;
			}
			else if (argv[cnt[0]][cnt[1]] == ' ' || argv[cnt[0]][cnt[1]] <= '9' \
				|| argv[cnt[0]][cnt[1]] >= '0')
				cnt[1]++;
			else
				return (1);
		}
		if (signs > 1 || !check_digit_str(argv[cnt[0]]) || argc < 5 || argc > 6)
			return (1);
	}
	return (0);
}

void exit_error_read(int mem_param, t_parameters *params)
{
	if (mem_param == 1)
		printf("Error: Invalid parameter.\n");
	params->stop = 1;
	if (mem_param == 0)
		printf("Error: Memory Error.\n");
}

void	start_params2(t_parameters *params, t_philo_params *philo_params)
{
	int ct;

	ct = 0;
	while(ct < params->n_fork)
	{
		pthread_mutex_init(&(params->lights[ct - 1]), NULL);
		philo_params[ct].id = ct;
	 	philo_params[ct].params = params;
	 	pthread_mutex_init(&(params->forks[ct - 1]), NULL);
	 	ct++;
	}
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
	if (params->n_fork <= 0 || params->time_die <= 0 || params->time_eat <= 0 || \
		params->time_sleep <= 0 || params->n_eat <= 0)
		{
		exit_error_read(1, params);
		return ;
		}
	params->threads = malloc((params->n_fork + 4) * sizeof(pthread_t));
	params->forks = malloc(params->n_fork * sizeof(pthread_mutex_t));
	params->lights = malloc(params->n_fork * sizeof(pthread_mutex_t));
	*philo_params = (t_philo_params *)malloc(params->n_fork * sizeof(t_philo_params));
	params->stop = 0;
	start_params2(params, *philo_params);
}

void check_params(t_parameters *params)
{
	int k;

	if (params->threads == 0 || params->forks == 0 || params->lights == 0 || \
		params->n_fork == 0)
	{
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
