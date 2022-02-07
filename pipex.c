/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slott <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:44:01 by slott             #+#    #+#             */
/*   Updated: 2022/02/01 17:25:31 by slott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipe	stru;
	int	check;

	if (argc != 5)
	{
		printf("Nombres incorrects d'arguments\n");
		return (0);
	}
	stru.fdin = openfile(argv[1], STDIN);
	stru.fdout = openfile(argv[4], STDOUT);
	pipe(stru.p);
	check = execution(&stru, argv, envp);
	if (check == 0)
	{
		write(STDERR, "Erreur\n", 7);
		return (0);
	}
	return (1);
}

int	execution(t_pipe *stru, char *argv[], char *envp[])
{
	stru->pid = fork();
	if (stru->pid == 0)
	{
		dup2(stru->fdin, STDIN);
		dup2(stru->p[1], STDOUT);
		close(stru->p[0]);
		close(stru->p[1]);
		stru->args = ft_split(argv[2], ' ');
		stru->cmd = get_path(envp, stru->args[0]);
		execve(stru->cmd, stru->args, envp);
	}
	stru->pid = fork();
	if (stru->pid == 0)
	{
		dup2(stru->fdout, STDOUT);
		dup2(stru->p[0], STDIN);
		close(stru->p[0]);
		close(stru->p[1]);
		stru->args = ft_split(argv[3], ' ');
		stru->cmd = get_path(envp, stru->args[0]);
		execve(stru->cmd, stru->args, envp);
	}
	close(stru->p[0]);
	close(stru->p[1]);
	waitpid(stru->pid, NULL, 0);
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
		fd = open(filename, O_CREAT | O_RDWR);
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
