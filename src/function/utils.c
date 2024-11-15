/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:05:39 by tbarret           #+#    #+#             */
/*   Updated: 2024/03/08 12:26:07 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_date();
	while ((ft_date() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	only_one(t_ctx *ctx)
{
	ctx->prop.s_time = ft_date();
	printf("%lu %d has taken a fork\n", ft_date() - ctx->prop.s_time, 1);
	ft_usleep(ctx->prop.t_dead);
	printf("%lu %d died\n", ft_date() - ctx->prop.s_time, 1);
	return (0);
}

size_t	ft_date(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "Error !\ngettimeofday() error", 25);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_print(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->prop->m_write);
	if (!dead_exit(p))
		printf("%lu %d %s", ft_date() - p->prop->s_time, p->id + 1, str);
	pthread_mutex_unlock(&p->prop->m_write);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	r;

	i = 0;
	n = 1;
	r = 0;
	while ((str[i] > 7 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			n *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - 48);
		i++;
	}
	return (r * n);
}
