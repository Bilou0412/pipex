/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 02:07:14 by bmoudach          #+#    #+#             */
/*   Updated: 2023/09/26 03:51:59 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_path_cmds(t_data *data, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = NULL;
	while (data->dir_path[j])
	{
		tmp = ft_strjoin(data->dir_path[j], data->cmds_args[i][0]);
		if (!tmp)
			return (-1);
		if (!access(tmp, F_OK | X_OK))
		{
			if (copy_path(i, tmp, data))
				return (free(tmp), -1);
			return (free(tmp), 0);
		}
		else
			j++;
		free(tmp);
	}
	data->cmds_path[i] = ft_strdup(data->cmds_args[i][0]);
	if (!data->cmds_path[i])
		return (-1);
	data->args_error = 1;
	return (0);
}

int	is_args_cmds_path(t_data *data)
{
	int	i;

	i = 0;
	data->cmds_path = ft_calloc((data->nb_cmd + 1), sizeof(char **));
	if (!data->cmds_path)
		return (-1);
	while (data->cmds_args[i])
	{
		if (!access(data->cmds_args[i][0], F_OK | X_OK))
		{
			if (args_is_path(data, i))
				return (-1);
		}
		else
		{
			if (init_path_cmds(data, i))
				return (-1);
		}
		i++;
	}
	return (ft_free_tab(data->dir_path), 0);
}

int	check_cmds(t_data *data)
{
	if (init_dir_path(data))
		return (-1);
	if (init_cmds_args(data))
		return (-1);
	if (is_args_cmds_path(data))
		return (-1);
	return (0);
}
