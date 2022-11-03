/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Vitor <vsergio@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:08:40 by Vitor             #+#    #+#             */
/*   Updated: 2022/11/03 17:38:44 by vsergio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_global
{
	int *end;
}				t_global;

typedef struct s_data
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		*meal_access;
	pthread_mutex_t		print;
	pthread_t			*ph_thread;
	struct s_data		*ph_data;
	long int			guests;
	long int			time_to_die;
	long int			time_to_eat;
	long int			time_to_sleep;
	long int			times_must_eat;
	long int			*lst_meal;
	int					*meals;
	int					all_eaten;
	int					id;
}						t_data;

long int	get_current_time(void);
long int	ft_atoi(char *str);
long int	exit_atoi(void);
void		destroy_mutexes(t_data *data);
int			create_data(t_data *data, char **argv, int argc);
void		print_status(t_data *data, char type, int pos);
void		*lifetime(void *philo);
void		free_all(t_data *data);
void		create_philo_threads(t_data *data);
void		init_mutexes(t_data *data);
void		eat(t_data *data);
void		return_forks(t_data *data);
void		sleep_time(t_data *data);
void		take_forks(t_data *data);
void		*dinner(void *data);
int			check_values(t_data *data);
int			invalid_args(void);
int			invalid_values(void);
int			check_atoi_numbers(char *string);
int			death_time(t_data *data, int i);
int			monitor(t_data *data, int i);

#endif
