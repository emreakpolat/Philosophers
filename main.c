/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:08:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/28 16:07:16 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



int philo_parse(int argc, char **argv, t_data *philo)
{
    if(argc < 5 || argc > 6)
        return(printf("Usage: ./philo filozof sayısı ölme_zamanı time_to_eat time_to_sleep [must_eat]\n"), 1);
    philo->philo_count = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]);
    philo->time_to_eat = ft_atoi(argv[3]);
    philo->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        philo->meal_count = ft_atoi(argv[5]);
    else
        philo->meal_count = -2;

    if (philo->philo_count == -1 || philo->time_to_die == -1 || philo->time_to_eat == -1
        || philo->time_to_sleep == -1 || philo->meal_count == -1)
    {
        return (1);
    }
    return (0);
}

int create_mutex(t_data*philo)
{
    int i;
    
    philo->forks = malloc(sizeof(pthread_mutex_t) * philo->philo_count);
    if (!philo->forks)
    {
        return(printf("Malloc Error\n"), 1);
    }
    i = 0;
    while (i < philo->philo_count)
    {
        if (pthread_mutex_init(&philo->forks[i], NULL) != 0)
            return(printf("Mutex init error\n"), 1);
        i++;
    }
    return (0);
}

void join_threads(t_data *data)
{
    int i = 0;

    while (i < data->philo_count)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
    
}

void *thread_function(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->data->printf_lock);
    printf("Philosophers %d threadi başladı\n", philo->id);
    pthread_mutex_unlock(&philo->data->printf_lock);
    return (NULL);
}


int start_threads(t_data *data)
{
    int i;

    data->start_time = get_time();
    i = 0;
    while (i < data->philo_count)
    {
        if (pthread_create(&data->philos[i].thread, NULL, thread_function, &data->philos[i]) != 0)
        {
            exit(EXIT_FAILURE);
        }
        i++;
        
    }
    return (0);
}


int main(int argc, char **argv)
{
    t_data *philo;

    philo = (t_data *)malloc(sizeof(t_data));
    if (!philo)
        return(printf("Malloc error\n"), 1);

    if (philo_parse(argc, argv, philo)!= 0)
        return (1);

    if(create_mutex(philo) == 1)
        return (1);

    if (init_philosophers(philo) != 0)
        return (1);
    start_threads(philo);
    join_threads(philo);
    return (0);
}
    