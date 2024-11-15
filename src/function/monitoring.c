/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarret <tbarret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:25:10 by tbarret           #+#    #+#             */
/*   Updated: 2024/03/08 12:52:38 by tbarret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

static int	is_dead(t_philo *p)
{
	pthread_mutex_lock(&p->prop->m_eat);
	if ((ft_date() - p->l_eat) > p->prop->t_dead && !p->eating)
		return (pthread_mutex_unlock(&p->prop->m_eat), 1);
	pthread_mutex_unlock(&p->prop->m_eat);
	return (0);
}

static int	check_dead(t_ctx *ctx)
{
	int		i;

	i = 0;
	while (i < ctx->prop.total)
	{
		if (is_dead(&ctx->philo[i]))
		{
			ft_print(&ctx->philo[i], "died\n");
			pthread_mutex_lock(&ctx->prop.m_dead);
			ctx->prop.dead++;
			pthread_mutex_unlock(&ctx->prop.m_dead);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_meal(t_ctx *ctx)
{
	int		i;
	int		e;

	i = 0;
	e = 0;
	if (ctx->prop.max_eat == -1)
		return (0);
	while (i < ctx->prop.total)
	{
		pthread_mutex_lock(&ctx->prop.m_eat);
		if (ctx->philo[i].eaten >= ctx->prop.max_eat)
			e++;
		pthread_mutex_unlock(&ctx->prop.m_eat);
		i++;
	}
	if (e == ctx->prop.total)
	{
		pthread_mutex_lock(&ctx->prop.m_dead);
		ctx->prop.dead++;
		pthread_mutex_unlock(&ctx->prop.m_dead);
		return (1);
	}
	return (0);
}

void	*checker(t_ctx *ctx)
{
	while (1)
		if (check_dead(ctx) || check_meal(ctx))
			break ;
	return (ctx);
}

void	*action(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	if ((p->id + 1) % 2 == 0)
		usleep(1);
	while (!dead_exit(p))
	{
		eating(p);
		if (dead_exit(p))
			break ;
		sleeping(p);
		if (dead_exit(p))
			break ;
		thinking(p);
	}
	return (ptr);
}
