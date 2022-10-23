/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:08:40 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/23 01:57:17 by Vitor            ###   ########.fr       */
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
	pthread_mutex_t		*forks;
	pthread_mutex_t		*meal_access;
	long int			*last_meal;
	int					guests;
	int					*meals_eaten;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	long int			times_must_eat;
	int					all_eaten;
	int					pos;
}						t_data;

typedef struct	s_philo
{
	pthread_t			philo_th;
	t_data				data_control;
}						t_philo;

long int	ft_atoi(char *str);
int			check_atoi_numbers(char *string);
long int	get_current_time(void);
void		free_all(t_data *data);
void		*lifetime(void *philo);
void		destroy_mutexes(t_data *data);
void		create_data(t_data *data, char **argv, int argc);
void		print_exit(void);

#endif
