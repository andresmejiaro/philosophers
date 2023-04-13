/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amejia <amejia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 23:50:38 by amejia            #+#    #+#             */
/*   Updated: 2023/04/12 19:48:02 by amejia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	if (c == '\n' || c == '\f' || c == '\r')
		return (1);
	if (c == '-')
		return (2);
	if (c == '+')
		return (3);
	return (0);
}

void	sign_space_control(char **str, int	*cumulative_sign, int	*sign_found)
{
	while (check_space(**str) == 1)
		if (check_space(**str))
		(*str)++;
	while (check_space(**str) == 2 || check_space(**str) == 3)
	{
		if (check_space(**str) == 2)
			(*cumulative_sign)++;
		(*sign_found)++;
		(*str)++;
	}
}

int	ft_atoi(char *str)
{
	int	cumulative_sign;
	int	cumulative_sum;
	int	sign_found;

	cumulative_sign = 0;
	cumulative_sum = 0;
	sign_found = 0;
	sign_space_control(&str, &cumulative_sign, &sign_found);
	if (sign_found > 1)
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		cumulative_sum = 10 * cumulative_sum + *str - '0';
		str++;
	}
	if (cumulative_sign % 2 == 1)
		cumulative_sum = -cumulative_sum;
	return (cumulative_sum);
}

size_t	ft_strlen(const char *s)
{
	unsigned int	counter;

	counter = 0;
	while (*(s + counter) != '\0')
	{
		counter++;
	}
	return (counter);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	counter;

	counter = 0;
	while (counter < n)
	{
		if (*(s1 + counter) != *(s2 + counter) || *(s1 + counter) == '\0' || \
		*(s2 + counter) == '\0')
			return (*((unsigned char *)(s1 + counter)) - \
			*((unsigned char *)(s2 + counter)));
		counter++;
	}
	return (0);
}