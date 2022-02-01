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
#define STDIN 0
#define STDOUT 1
#define STDERR 2

int	main(int argc, char *argv[], char *envp[])
{
	char	*cmd;
	char	**args;
	int		p[2];
	int		fdout;
	int		fdin;
	pid_t	pid;
	pid_t	pid2;

	if (argc != 5)
	{
		printf("Nombres incorrects d'arguments\n");
		return (0);
	}
	fdin = openfile(argv[1], STDIN);
	fdout = openfile(argv[4], STDOUT);
	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		dup2(fdin, STDIN);
		dup2(p[1], STDOUT);
		close(p[0]);
		close(p[1]);
		args = ft_split(argv[2], ' ');
		cmd = get_path(envp, args[0]);
		execve(cmd, args, envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fdout, STDOUT);
		dup2(p[0], STDIN);
		close(p[0]);
		close(p[1]);
		args = ft_split(argv[3], ' ');
		cmd = get_path(envp, args[0]);
		execve(cmd, args, envp);
	}
	close(p[0]);
	close(p[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

int	openfile(char *filename, int m)
{
	int	fd;

	if (m == STDIN)
	{
		if (access(filename, F_OK))
		{
			write(1, "INFILE fichier introuvable", 26);
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
