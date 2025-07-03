/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:08:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/07/03 19:02:41 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	start_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (printf("Malloc error\n", false));
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (printf("Mutex error\n"), false);
		i++;
	}
	return (true);
}

static bool	init_data(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error\n./philo|philo_number die_time|eat_time sleep_time|philo_must_eat_time\n");
		return (false);
	}
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->total_meal_count = -2;
	if (argc == 6)
		data->total_meal_count = ft_atoi(argv[5]);
	if (data->philo_count == -1 || data->time_to_die == -1 || data->time_to_eat == -1
		|| data->time_to_sleep == -1 || data->total_meal_count == -1)
		return (false);
	data->start_time = get_time();
	data->end_flag = true;
	if (pthread_mutex_init(&data->dead, NULL) != 0)
		return (printf("Mutex error\n"), false);
	if (pthread_mutex_init(&data->print, NULL) != 0)
		return (printf("Mutex error\n"), false);
	if(start_forks(data) != true)
		return (false);
	return (true);
}

static t_philo *philo_init(t_data *data)
{
	t_philo *philo;
	int i;
	philo = (t_philo *)malloc(sizeof(t_philo) * data->philo_count);
	if (!philo)
		return (printf("Malloc error\n"), NULL);
	i = 0;
	while (i < data->philo_count)
	{
		philo[i].last_meal_time = get_time();
		philo[i].id = (i + 1);
		if (pthread_mutex_init(&philo[i].meal_lock, NULL) != 0)
			return (NULL);
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		philo[i].t_data = data;
		philo[i].meal_count = 0;
		i++;
	} 
	return (philo);
}

int main(int argc, char **argv)
{
	t_data data;
	t_philo *philo;
	int i = 0;

	if (init_data(argc, argv, &data) == false)
		return (1);
	philo = philo_init(&data);
	if (philo == NULL)
		return (1);
	creat_thread(philo);
	pthread_join(data.check_simulation, NULL);

	pthread_mutex_destroy(&data.dead);
	pthread_mutex_destroy(&data.print);
	while (i < data.philo_count)
	{
		pthread_mutex_destroy(&data.forks[i]);
		pthread_mutex_destroy(&philo[i].meal_lock);
		i++;
	}
	free(data.forks);
	free(philo);
	
	return (0);
}
