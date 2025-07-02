/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:08:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/07/02 22:23:54 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool start_forks(t_data *data)
{
    int i = 0;

    data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
    if (!data->forks)
        return (printf("Malloc error\n", false));
    while (i < data->philo_count)
    {
        if (pthread_mutex_init(&data->forks[i], NULL) != 0)
            return (printf("Mutex error\n"), false);
        i++;
    }
    return (true);
}

static bool  init_data(int argc, char **argv, t_data *data)
{
    if(argc < 5 || argc > 6)
    return (printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"), 1);
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
    philo = (t_philo *)malloc(sizeof(t_philo));
    if (!philo)
        return (NULL);
    i = 0;
    while (i < data->philo_count)
    {
        philo[i].last_meal_time = get_time();
        philo[i].id = (i + 1);
        if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
            return (NULL);
        philo[i].left_fork = data->forks[i];
        philo[i].right_fork = data->forks[(i + 1) % data->philo_count];
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

    if (init_data(argc, argv, &data) == false)
    return (1);
    // printf("OOOOOOOO\n");
    philo = philo_init(&data);
    if (philo == NULL)
        return (1);
    creat_thread(philo);
    philo_state(philo);
    check_simulation(philo);
    return (0);
}
