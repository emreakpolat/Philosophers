/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:16:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/07/02 21:18:42 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



void take_fork_and_eat(t_philo *philo)
{
    if ((philo->id % 2) == 0)
    {
        pthread_mutex_lock(&philo->left_fork);
        printf_function("has taken a fork", philo);
        pthread_mutex_lock(&philo->right_fork);
        printf_function("has taken a fork", philo);
    }
    else
    {
        pthread_mutex_lock(&philo->right_fork);
        printf_function("has taken a fork", philo);
        pthread_mutex_lock(&philo->left_fork);
        printf_function("has taken a fork", philo);
    }
    pthread_mutex_unlock(&philo->right_fork);
    pthread_mutex_unlock(&philo->left_fork);
    printf_function("is eating", philo);
    wait_function(philo->t_data, philo->t_data->time_to_eat);
    pthread_mutex_lock(&philo->meal_lock);
    philo->meal_count++;
    pthread_mutex_unlock(&philo->meal_lock);
    
}













/* loop

take();
eat();
sleep();
think();

*/