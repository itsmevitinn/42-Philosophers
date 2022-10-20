/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:08:40 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/20 16:42:11 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct	s_data
{
	pthread_mutex_t	*forks;
	int				guests;
	int				time_to_eat;
	int				pos;
}				t_data;

typedef struct	s_philo
{
	pthread_mutex_t	*forks;
	pthread_t		philo_th;
	int				guests;
	int				time_to_eat;
	int				pos;
}				t_philo;

long int	ft_atoi(char *str);
int			check_atoi_numbers(char *string);

#endif
