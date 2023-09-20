#include "../include/pipex.h"

int	add_backslash_path(t_raw_data *r_data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (r_data->dir_path[i])
	{
		tmp = ft_strjoin(r_data->dir_path[i], "/");
		if (!tmp)
			return (-1);
		free(r_data->dir_path[i]);
		r_data->dir_path[i] = ft_strdup(tmp);
		if (!r_data->dir_path[i])
			return (-1);
		free(tmp);
		i++;
	}
	return (0);
}
/*
Stores all PATH paths in a double array
*/
int	init_path_dir(t_raw_data *r_data)
{
	char	*tmp;
	int		j;

	tmp = NULL;
	j = 0;
	while (r_data->envp[j])
	{
		if (!ft_strncmp(r_data->envp[j], "PATH=", 5))
		{
			tmp = ft_substr(r_data->envp[j], 5, ft_strlen(r_data->envp[j]));
			if (!tmp)
				return (-1);
			r_data->dir_path = ft_split(tmp, ':');
			if (!r_data->dir_path)
				return (-1);
			else
				return (free(tmp), add_backslash_path(r_data));
		}
		else
			j++;
	}
	return (0);
}
/*
Create 2d tables and put in order,
the command, and the arguments.
*/
int	init_cmds_args(t_raw_data *r_data, t_data *data)
{
	int	i;

	i = 0;
	data->cmds_args = malloc((data->nb_cmd + 1) * sizeof(char **));
	if (!data->cmds_args)
		return (-1);
	while (i < data->nb_cmd)
	{
		data->cmds_args[i] = ft_split(r_data->argv[i + 2], ' ');
		if (!data->cmds_args)
			return (-1);
		i++;
	}
	data->cmds_args[i] = NULL;
	return (0);
}
int	init_valid_path_cmds(t_raw_data *r_data, t_data *data)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (j < data->nb_cmd)
	{
		tmp = ft_strjoin(r_data->dir_path[i], data->cmds_args[j][0]);
		if(!tmp)
			return (-1);
		if (!access(tmp, F_OK | X_OK))
		{
			data->cmds_path[j] = ft_strdup(tmp);
			if (!data->cmds_path[j])
				return (-1);
			i = 0;
			j++;
		}
		else
			i++;
		free(tmp);
	}
	data->cmds_path[j] = NULL;
	return (0);
}
int init_data(t_data *data, int nb_cmd, char **argv, char **envp)
{
	t_raw_data r_data;

	r_data.argv = argv;
	r_data.envp = envp;
	data->nb_cmd = nb_cmd;
	data->cmds_path = malloc((data->nb_cmd + 1) * sizeof(char *));
	if (!data->cmds_path)
		return (-1);
	if(init_path_dir(&r_data))
		return (-1);
	if(init_cmds_args(&r_data, data))
		return (-1);
	if(init_valid_path_cmds(&r_data, data))
		return (-1);
	return (0);
}
