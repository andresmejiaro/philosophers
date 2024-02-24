/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:25:22 by amejia            #+#    #+#             */
/*   Updated: 2023/04/19 18:25:10 by amejia           ###   ########.fr       */
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
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	start_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*lights;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*counter;
	pthread_t		*threads;
	int				start;
	int				stop;
	int				print;
	void			*philo_params;
	int				error;
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

//mutex funcs
int		start_checker(t_parameters *gparams);
int		stop_checker(t_parameters *gparams);
int		timediffs(t_parameters *gparams, struct timeval time);
void	muted_print(char *str, int *numb, t_parameters *gparams);
int		check_food(t_parameters *gparams, t_philo_params *philo_params);
int		n_ate_checker(t_parameters *gparams, t_philo_params philo_params);

// params
void	check_params(t_parameters *params);
void	start_params(int argc, char **argv, t_parameters *params, \
			t_philo_params **philo_params);
void	exit_error_read(int mem_param, t_parameters *params);
void	join_threads(t_parameters *params);
void	free_memory(t_parameters *params, t_philo_params *philo_params);
int		check_valid(int argc, char **argv);

// treads
void	*chronos(void *params);
void	*philosopher(void *params);
void	*ganymede(void *params);
void	*kharon(void *params);

#endif
