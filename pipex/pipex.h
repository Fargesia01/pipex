/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slott <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:25:51 by slott             #+#    #+#             */
/*   Updated: 2022/02/01 16:51:54 by slott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(const char *s, char ch);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(const char *pre, const char *su);
char	*get_path(char *envp[], char *cmd);
int		ft_strlen(const char *str);
void	ft_free2(char ***paths);
int		openfile(char *filename, int m);

#endif
