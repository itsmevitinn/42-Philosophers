/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:08:40 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/22 12:49:55 by Vitor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct	s_data
{
	struct timeval		*time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*meal_access;
	int					guests;
	long int			time_to_eat;
	long int			*last_meal;
	int					pos;
}						t_data;

typedef struct	s_philo
{
	pthread_t			philo_th;
	t_data				data_control;
	int					pos;
}						t_philo;

long int	ft_atoi(char *str);
int			check_atoi_numbers(char *string);
long int	get_current_time(t_data *data);
void		free_all(t_data *data);
void		*lifetime(void *philo);
void		destroy_mutexes(t_data *data);

#endif
