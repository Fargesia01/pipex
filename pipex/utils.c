/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slott <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:25:30 by slott             #+#    #+#             */
/*   Updated: 2022/02/10 14:11:37 by slott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n && s1[count] == s2[count] && s1[count] && s2[count])
		count++;
	if (count == n)
		return (0);
	return ((unsigned char)s1[count] - (unsigned char)s2[count]);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	x;

	x = 0;
	if (size > 0)
	{
		while (x < size - 1 && src[x])
		{
			dst[x] = src[x];
			x++;
		}
		dst[x] = '\0';
	}
	x = 0;
	while (src[x])
		x++;
	return (x);
}

char	*ft_strjoin(const char *pre, const char *su)
{
	char	*tab;
	int		c;
	int		c2;

	c2 = 0;
	c = 0;
	if (!(pre) || !(su))
		return (NULL);
	tab = malloc((ft_strlen(pre) + ft_strlen(su)) * sizeof(char) + 1);
	if (!(tab))
		return (NULL);
	while (pre[c])
	{
		tab[c] = pre[c];
		c++;
	}
	while (su[c2])
	{
		tab[c] = su[c2];
		c++;
		c2++;
	}
	tab[c] = 0;
	return (tab);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	close_pipe(t_pipe *stru)
{
	close(stru->p[0]);
	close(stru->p[1]);
}
