/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:05:58 by bmoudach          #+#    #+#             */
/*   Updated: 2023/09/26 03:51:40 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_files(t_data *data, int argc, char **argv, char **envp)
{
	data->argv = argv;
	data->nb_cmd = argc - 3;
	data->envp = envp;
	data->args_error = 0;
	data->file_error = 0;
	if (access(data->argv[1], F_OK | R_OK))
		data->file_error = 1;
	return (0);
}
