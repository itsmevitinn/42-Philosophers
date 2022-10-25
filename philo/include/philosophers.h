/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:08:40 by Vitor             #+#    #+#             */
/*   Updated: 2022/10/25 12:50:29 by vsergio          ###   ########.fr       */
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
	pthread_t			*philo_th;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	long int			times_must_eat;
	long int			*last_meal;
	int					*meals_eaten;
	int					guests;
	int					all_eaten;
	int					pos;
	int					*killer_ret;
}						t_data;

typedef struct	s_philo
{
	t_data	data;
}			t_philo;

long int	get_current_time(void);
long int	ft_atoi(char *str);
void		destroy_mutexes(t_data *data);
void		create_content(t_data *content, char **argv, int argc);
void		detach_threads(t_data *data);
void		print_exit(void);
void		*lifetime(void *philo);
void		free_all(t_data *data);
int			check_atoi_numbers(char *string);
void		create_philo_threads(t_data *content);

#endif
