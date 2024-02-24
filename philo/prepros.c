/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepros.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:46:01 by amejia            #+#    #+#             */
/*   Updated: 2023/04/19 18:07:46 by amejia           ###   ########.fr       */
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

int	check_valid2(int argc)
{
	if (argc < 5 || argc > 6)
		return (1);
	return (0);
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
		if (signs > 1 || !check_digit_str(argv[cnt[0]]))
			return (1);
	}
	return (check_valid2(argc));
}

void	exit_error_read(int mem_param, t_parameters *params)
{
	params->stop = 1;
	params->error = 1;
	if (mem_param == 1)
		printf("Error: Invalid parameter.\n");
	if (mem_param == 0)
		printf("Error: Memory Error.\n");
}
