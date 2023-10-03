/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 06:18:01 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/03 15:43:47 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	distrib_cmd(t_data *data)
{
	if (data->cmd_round == 0)
	{
		if (dup2(data->fd_in, STDIN_FILENO) == -1 || dup2(data->pipe_fd[1],
				STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (data->cmd_round == data->nb_cmd - 1)
	{
		if (dup2(data->tmp_fd, STDIN_FILENO) == -1 || dup2(data->fd_out,
				STDOUT_FILENO) == -1)
			return (-1);
	}
	else
	{
		if (dup2(data->tmp_fd, STDIN_FILENO) == -1 || dup2(data->pipe_fd[1],
				STDOUT_FILENO) == -1)
			return (-1);
	}
	if (close(data->pipe_fd[0]) == -1 || close(data->pipe_fd[1]) == -1)
		return (-1);
	if (execve(data->cmds_path[data->cmd_round],
			data->cmds_args[data->cmd_round], data->envp) == -1)
		return (-1);
	return (0);
}

int	open_files(t_data *data)
{
	data->fd_in = open(data->argv[1], O_RDONLY);
	if (data->fd_in == -1)
		return (-1);
	data->fd_out = open(data->argv[data->nb_cmd + 2],
			O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (data->fd_out == -1)
		return (-1);
	return (0);
}

int	exec(t_data *data)
{
	data->cmd_round = 0;
	while (data->cmd_round < data->nb_cmd)
	{
		if (pipe(data->pipe_fd))
			return (0);
		data->pid = fork();
		if (data->pid == -1)
			return (0);
		if (data->pid == 0)
		{
			if (open_files(data))
				return (-1);
			if (distrib_cmd(data))
				return (-1);
		}
		else
		{
			waitpid(data->pid, &data->status, 0);
			close(data->pipe_fd[1]);
			data->tmp_fd = data->pipe_fd[0];
			data->cmd_round++;
		}
	}
	close(data->tmp_fd);
	return (0);
}
