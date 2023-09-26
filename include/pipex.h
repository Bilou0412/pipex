/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:00:34 by bmoudach          #+#    #+#             */
/*   Updated: 2023/09/26 06:18:21 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	char	***cmds_args;
	char	**cmds_path;
	char	**dir_path;
	int		nb_cmd;
	int		cmd_round;
	int		fd_in;
	int		fd_out;
	int		tmp_fd;
	int		pipe_fd[2];
	int		args_error;
	int		file_error;
	char	**argv;
	char	**envp;
	int		status;
	int		pid;
}			t_data;

int			check_files(t_data *data, int argc, char **argv, char **envp);
int			check_cmds(t_data *data);
int			init_dir_path(t_data *data);
int			init_cmds_args(t_data *data);
int			args_is_path(t_data *data, int i);
int			copy_path(int i, char *tmp, t_data *data);
int			error_handler(t_data *data);
int			exec(t_data *data);
#endif