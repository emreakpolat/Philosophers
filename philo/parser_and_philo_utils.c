/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_and_philo_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 20:55:18 by makpolat          #+#    #+#             */
/*   Updated: 2025/07/08 11:46:01 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	char_check(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z'))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_atoi(const char *str)
{
	long	k;
	int		sign;

	k = char_check(str);
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+' || k == 1)
		return (printf("Wrong argument\n"), -1);
	while (*str >= '0' && *str <= '9')
	{
		if (*str == '-' || *str == '+')
			return (printf("Wrong argument\n"), -1);
		k = k * 10 + (*str - 48);
		if ((k > 2147483647) || (k < -2147483648))
			return (printf("Wrong argument use integer\n"), -1);
		str++;
	}
	return (sign * k);
}

void	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->t_data->philo_count)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		if ((get_time() - philo[i].last_meal_time) > philo->t_data->time_to_die)
		{
			pthread_mutex_lock(&philo->t_data->dead);
			philo->t_data->end_flag = false;
			pthread_mutex_unlock(&philo->t_data->dead);
			pthread_mutex_unlock(&philo[i].meal_lock);
			printf_function("died", &philo[i]);
			return ;
		}
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	usleep(100);
}

void	check_meals(t_philo *philo)
{
	int	count;
	int	i;

	if (philo->t_data->total_meal_count == -2)
		return ;
	i = 0;
	count = 0;
	while (i < philo->t_data->philo_count)
	{
		pthread_mutex_lock(&philo[i].meal_lock);
		if (philo[i].meal_count >= philo->t_data->total_meal_count)
			count++;
		pthread_mutex_unlock(&philo[i].meal_lock);
		i++;
	}
	if (count == philo->t_data->philo_count)
	{
		pthread_mutex_lock(&philo->t_data->dead);
		philo->t_data->end_flag = false;
		pthread_mutex_unlock(&philo->t_data->dead);
	}
}
