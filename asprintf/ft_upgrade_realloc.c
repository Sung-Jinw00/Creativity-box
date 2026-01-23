/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upgrade_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <locagnio@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:32:39 by locagnio          #+#    #+#             */
/*   Updated: 2026/01/23 01:50:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_asprintf.h"

/**
 * @brief Allocates zero-initialized memory like calloc.
 * 
 * @param nmemb Number of elements.
 * @param size Size of each element.
 * 
 * @return Pointer to the allocated memory or NULL if allocation fails.
 */
void	*ft_calloc_(size_t nmemb, size_t size)
{
	void	*tab;
	size_t	i;

	i = 0;
	if (size != 0 && nmemb > (-1 / size))
		return (NULL);
	tab = (void *)malloc(nmemb * size);
	if (!tab)
		return (NULL);
	while (i < nmemb * size)
	{
		*(char *)(tab + i) = 0;
		i++;
	}
	return (tab);
}

/**
 * @brief Resizes a memory block, similar to realloc but with custom behavior.
 * 
 * If ptr is NULL, behaves like calloc. If size is 0, frees ptr. Copies the
 * old content into the new memory if needed.
 * 
 * @param ptr Pointer to existing memory.
 * @param size New size for the memory block.
 * 
 * @return Pointer to the resized memory block or NULL on failure.
 */
void	*ft_upgrade_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	i;

	i = 0;
	if (size == 0 && ptr)
		return (free(ptr), NULL);
	new_ptr = (void *)ft_calloc_(sizeof(void *), size);
	if (!new_ptr)
		return (NULL);
	while ((char *)ptr && i < size)
	{
		*(char *)(new_ptr + i) = *(char *)(ptr + i);
		i++;
	}
	if (ptr)
		free(ptr);
	return (new_ptr);
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	void *ptr = strdup("Hello World");
	void *cpy = ft_upgrade_realloc(ptr, 5);

	printf("result : %s\n", (char *)cpy);
	free(cpy);
	return(0);
} */