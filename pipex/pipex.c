/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slott <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:44:01 by slott             #+#    #+#             */
/*   Updated: 2022/02/10 14:29:00 by slott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	stru;

	if (argc != 5)
		return (write(STDERR, "Invalid number of arguments\n", 28));
	stru.fdin = openfile(argv[1], STDIN);
	if (stru.fdin < 0)
		return (write(STDERR, "Error while opening infile\n", 27));
	stru.fdout = openfile(argv[4], STDOUT);
	if (stru.fdout < 0)
		return (write(STDERR, "Error while opening outfile\n", 28));
	if (pipe(stru.p) < 0)
		return (write(STDERR, "Error while creating pipe\n", 26));
	stru.pid = fork();
	if (stru.pid == 0)
		if (!first_child(&stru, argv, envp))
			return (write(STDERR, "Error: command 1 not found\n", 27));
	waitpid(stru.pid, NULL, 0);
	stru.pid2 = fork();
	if (stru.pid2 == 0)
		if (!second_child(&stru, argv, envp))
			return (write(STDERR, "Error: command 2 not found\n", 27));
	close_pipe(&stru);
	waitpid(stru.pid2, NULL, 0);
	return (1);
}

int	first_child(t_pipe *stru, char *argv[], char *envp[])
{
	dup2(stru->fdin, STDIN);
	dup2(stru->p[1], STDOUT);
	close_pipe(stru);
	stru->args = ft_split(argv[2], ' ');
	stru->cmd = get_path(envp, stru->args[0]);
	if (!stru->cmd)
		return (0);
	execve(stru->cmd, stru->args, envp);
	return (1);
}

int	second_child(t_pipe *stru, char *argv[], char *envp[])
{	
	dup2(stru->fdout, STDOUT);
	dup2(stru->p[0], STDIN);
	close_pipe(stru);
	stru->args = ft_split(argv[3], ' ');
	stru->cmd = get_path(envp, stru->args[0]);
	if (!stru->cmd)
		return (0);
	execve(stru->cmd, stru->args, envp);
	return (1);
}

int	openfile(char *filename, int m)
{
	int	fd;

	if (m == STDIN)
	{
		if (access(filename, F_OK))
		{
			write(1, "INFILE fichier introuvable\n", 27);
			return (STDIN);
		}
		fd = open(filename, O_RDONLY);
		return (fd);
	}
	else
	{
		fd = open(filename, O_CREAT | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		return (fd);
	}
}

char	*get_path(char *envp[], char *cmd)
{
	int		i;
	char	**paths;
	char	*tmp;
	char	*command;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i], ':');
	i = 0;
	paths[i] += 5;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(command, F_OK))
		{
			free(paths);
			return (command);
		}
		free(command);
		i++;
	}
	return (NULL);
}
