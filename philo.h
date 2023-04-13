/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:25:22 by amejia            #+#    #+#             */
/*   Updated: 2023/04/13 15:19:22 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_parameters {
	int				n_fork;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				n_eat;
	struct timeval	time_start;
	struct timeval	actual_time;
	pthread_mutex_t	*lights;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	int				stop;
}	t_parameters;

typedef struct s_philo_params {
	t_parameters	*params;
	struct timeval	time_ate;
	struct timeval	time_slept;
	struct timeval	time_thought;
	int				id;
	int				state;
	int				n_ate;
}	t_philo_params;


// aux vars
int		ft_atoi(char *str);
int		timediff(struct timeval tim1, struct timeval tim2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(char *s1, char *s2, unsigned int n);

// params
void 	check_params(t_parameters *params);
void	start_params(int argc, char **argv, t_parameters *params, \
			t_philo_params **philo_params);

// treads
void 	*chronos(void *params);
void	*philosopher(void *params);


#endif
