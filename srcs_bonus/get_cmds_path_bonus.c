/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds_path_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 01:55:26 by bmoudach          #+#    #+#             */
/*   Updated: 2023/10/03 15:45:44 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	copy_path(int i, char *tmp, t_data *data)
{
	data->cmds_path[i] = ft_strdup(tmp);
	if (!data->cmds_path[i])
		return (-1);
	return (0);
}

int	args_is_path(t_data *data, int i)
{
	char	**tmp;

	tmp = NULL;
	data->cmds_path[i] = ft_strdup(data->cmds_args[i][0]);
	if (!data->cmds_path)
		return (-1);
	tmp = ft_split(data->cmds_args[i][0], '/');
	if (!tmp)
		return (-1);
	free(data->cmds_args[i][0]);
	data->cmds_args[i][0] = ft_strdup(tmp[ft_last_index(tmp)]);
	if (!data->cmds_args[i][0])
		return (ft_free_tab(tmp), -1);
	return (ft_free_tab(tmp), 0);
}

int	init_cmds_args(t_data *data)
{
	int	i;

	i = 0;
	data->cmds_args = malloc((data->nb_cmd + 1) * sizeof(char **));
	if (!data->cmds_args)
		return (-1);
	while (i < data->nb_cmd)
	{
		data->cmds_args[i] = ft_split(data->argv[i + 2], ' ');
		if (!data->cmds_args)
			return (-1);
		i++;
	}
	data->cmds_args[i] = NULL;
	return (0);
}

int	add_backslash_dir_path(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->dir_path[i])
	{
		tmp = ft_strjoin(data->dir_path[i], "/");
		if (!tmp)
			return (-1);
		free(data->dir_path[i]);
		data->dir_path[i] = ft_strdup(tmp);
		if (!data->dir_path[i])
			return (free(tmp), -1);
		free(tmp);
		i++;
	}
	return (0);
}

int	init_dir_path(t_data *data)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	j = 0;
	while (data->envp[j])
	{
		if (!ft_strncmp(data->envp[j], "PATH=", 5))
		{
			tmp = ft_substr(data->envp[j], 5, ft_strlen(data->envp[j]));
			if (!tmp)
				return (-1);
			data->dir_path = ft_split(tmp, ':');
			if (!data->dir_path)
				return (free(tmp), -1);
			free(tmp);
			if (add_backslash_dir_path(data))
				return (-1);
			return (0);
		}
		else
			j++;
	}
	return (-1);
}
