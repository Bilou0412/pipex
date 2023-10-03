/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 03:29:40 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/03 15:45:49 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_all(t_data *data)
{
	ft_free_tab(data->cmds_path);
	ft_free_third_tab(data->cmds_args);
}

void	cmd_not_found(t_data *data)
{
	int	i;

	i = 0;
	while (data->cmds_path[i])
	{
		if (access(data->cmds_path[i], F_OK | X_OK))
		{
			ft_printf("pipex: command not found: %s\n", data->cmds_args[i][0]);
			i++;
		}
		else
			i++;
	}
}

void	infile_not_found(t_data *data)
{	
	ft_printf("%s: %s\n", strerror(errno), data->argv[1]);
}

int	error_handler(t_data *data)
{
	if (data->args_error == 0 && data->file_error == 0)
		return (0);
	if (data->file_error == 1)
		infile_not_found(data);
	if (data->args_error == 1)
		cmd_not_found(data);
	return (0);
}
