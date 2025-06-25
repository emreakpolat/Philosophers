/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makpolat <makpolat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:08:42 by makpolat          #+#    #+#             */
/*   Updated: 2025/06/25 20:58:41 by makpolat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


size_t  ft_strlen(unsigned char *str)
{
    size_t  i;

    i = 0;
    while(str[i])
        i++;
    return (i);
}

void error(char *message)
{
    write(1, message, ft_strlen(message));
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    if(argc < 5)
        error("Wrong argument count\n");
    
    ft_atoi(argv[0]);
    ft_atoi(argc[1]);
    ft_atoi(argc[2]);
    ft_atoi(argc[3]);
    ft_atoi(argc[4]);

        
}










//  sırasıyla
//  philo sayısı
//  yemek yemek
//  uyumak
//  düşünmek
//  tekrarlamak
