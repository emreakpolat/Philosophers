/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:16:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/07/06 18:36:38 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_state(t_philo *philo)
{
	if ((philo->id % 2) == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf_function("has taken a fork", philo);
		pthread_mutex_lock(philo->right_fork);
		printf_function("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf_function("has taken a fork", philo);
		pthread_mutex_lock(philo->left_fork);
		printf_function("has taken a fork", philo);
	}
}

static void	philo_eating(t_philo *philo)
{
	if (get_end_flag(philo->t_data) == false)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	printf_function("is eating", philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_lock);
	wait_function(philo->t_data, philo->t_data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (get_end_flag(philo->t_data) == false)
		return ;
	printf_function("is sleeping", philo);
	wait_function(philo->t_data, philo->t_data->time_to_sleep);
	printf_function("is thinking", philo);
}

void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_end_flag(philo->t_data))
	{
		philo_state(philo);
		philo_eating(philo);
	}
	return (NULL);
}

void	*check_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_end_flag(philo->t_data) == true)
	{
		check_death(philo);
		check_meals(philo);
	}
	return (NULL);
}

void	creat_thread(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->t_data->philo_count)
	{
		if (pthread_create(&philo[i].philo, NULL, philo_loop, &philo[i]) != 0)
			return ;
		i++;
	}
	if (pthread_create(&philo->t_data->check_simulation,
			NULL, check_simulation, philo))
		return ;
	i = 0;
	while (i < philo->t_data->philo_count)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	pthread_join(philo->t_data->check_simulation, NULL);
}
