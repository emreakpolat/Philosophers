/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:08:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/27 12:39:39 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


size_t  ft_strlen(char *str)
{
    size_t  i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}




// void philo_start(int argc, char **argv)
// {
//     t_data *philo;
//     if(argc < 5 || argc > 6)
//         return(printf("Usage: ./philo n_philo time_to_die time_to_eat time_to_sleep [must_eat]\n"), 1);

//     philo = (t_data *)malloc(sizeof(t_data));
//     if (!philo)
//         return(printf("Malloc error\n"));
        
//     philo->philo_count = ft_atoi(argv[1]);
//     philo->time_to_die = ft_atoi(argv[2]);
//     philo->time_to_eat = ft_atoi(argv[3]);
//     philo->time_to_sleep = ft_atoi(argv[4]);
//     if (argc == 6)
//         philo->meal_count = ft_atoi(argv[5]);
//     else
//         philo->meal_count = -2;

//     if (philo->philo_count == -1 || philo->time_to_die == -1 || philo->time_to_eat == -1
//         || philo->time_to_sleep == -1 || philo->meal_count == -1)
//     {
//         return (1);
//     }
// }



void *thread_function()
{
    printf("thread 1 başladı\n");
    usleep(100);
    printf("thread 1 bitti\n");
    //return (NULL);
}
void *thread_function_two()
{
    //int id = *((int *)arg);
    write(1, "thread 2 başladı\n", ft_strlen("thread 2 başladı\n"));
    write(1, "thread 2 bitti\n", ft_strlen("thread 2 bitti\n"));
    //printf("thread 2 bitti\n");
    //return (NULL);
}



int main(int argc, char **argv)
{

    pthread_t thread;
    pthread_t thread2;
    int id = 1;
    if (argv[1] == '1')
    {
        printf("çatalı aldı\n");
        printf("öldü knk\n");
        return(0);
    }
    
    
    pthread_create(&thread,NULL, thread_function,&id);
    //usleep(10);
    pthread_create(&thread2, NULL, thread_function_two, &id);
    //thread_function();
    //thread_function_two();
    //pthread_join(thread, NULL);
    usleep(100000);
    printf("Main thread bitti\n");
    return 0;
    (void)argc;
    (void)argv;






    
   //philo_start(argc, argv);
    

}
