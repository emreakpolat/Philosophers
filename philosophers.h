/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:08:34 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/24 17:08:29 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H


# include <pthread.h>
# include <stdlib.h>


typedef struct s_philo{

    int number_of_philo;
    int philo_eat_time;
    int philo_dead_time;
    int philo_think_time;
    int philo_sleep_time;

    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
} t_philo;









#endif