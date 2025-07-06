/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:33:27 by makpolat          #+#    #+#             */
/*   Updated: 2025/07/06 18:27:52 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	wait_function(t_data *data, long time)
{
	long	curr_time;

	curr_time = get_time();
	while ((get_time() - curr_time) < time)
	{
		if (get_end_flag(data) == false)
			break ;
		usleep(100);
	}
}

void	printf_function(char *str, t_philo *philo)
{
	if (ft_strcmp(str, "is died") == 0)
	{
		pthread_mutex_lock(&philo->t_data->print);
		printf("%ld %d %s\n", (get_time() - philo->t_data->start_time),
			philo->id, str);
		pthread_mutex_unlock(&philo->t_data->print);
		return ;
	}
	else if (get_end_flag(philo->t_data) == true)
	{
		pthread_mutex_lock(&philo->t_data->print);
		printf("%ld %d %s\n", (get_time() - philo->t_data->start_time),
			philo->id, str);
		pthread_mutex_unlock(&philo->t_data->print);
	}
}

bool	get_end_flag(t_data *data)
{
	bool	temp;

	pthread_mutex_lock(&data->dead);
	temp = data->end_flag;
	pthread_mutex_unlock(&data->dead);
	return (temp);
}

void	free_philo(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->dead);
	pthread_mutex_destroy(&data->print);
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&philo[i].meal_lock);
		i++;
	}
	free(data->forks);
	free(philo);
}
