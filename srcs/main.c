/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:59:59 by bmoudach          #+#    #+#             */
/*   Updated: 2023/09/26 06:13:11 by bmoudach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc < 5 || argc > 1024)
		return (ft_printf("parse error near `|'"), 0);
	if (check_files(&data, argc, argv, envp))
		return (0);
	if (check_cmds(&data))
		return (0);
	if (exec(&data))
		return (0);
	if (error_handler(&data))
		return (0);
	return (ft_free_tab(data.cmds_path), ft_free_third_tab(data.cmds_args), 0);
}
