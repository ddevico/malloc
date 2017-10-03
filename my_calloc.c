/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tktorza <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 12:04:39 by tktorza           #+#    #+#             */
/*   Updated: 2017/10/03 12:04:40 by tktorza          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/malloc.h"

void		*exec_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	new_size;

	if (!nmemb || !size)
		return (NULL);
	new_size = nmemb * size;
	if (size != new_size / nmemb)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	if (ptr)
		ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void		*calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	malloc_init();
	pthread_mutex_lock(&g_mutex);
	ptr = exec_calloc(nmemb, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

int			busy_increment(int busy)
{
	while (g_page_one->block)
	{
		busy += g_page_one->block->busy;
		g_page_one->block = g_page_one->block->next;
	}

	return (busy);
}