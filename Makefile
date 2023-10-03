# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmoudach <bmoudach@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/01 04:23:10 by bmoudach          #+#    #+#              #
#    Updated: 2023/10/03 15:46:46 by bmoudach         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR			=		srcs
SRC_BONUS_DIR	=		srcs_bonus
OBJ_DIR			=		obj
OBJ_BONUS_DIR	=		obj_bonus
LIBFT_DIR		=		libft

NAME			=		pipex
NAME_BONUS		=		pipex_bonus
SRC				=		srcs/check_cmds.c srcs/check_files.c srcs/error_handler.c srcs/exec.c srcs/get_cmds_path.c srcs/main.c
SRC_BONUS		=		srcs_bonus/check_cmds_bonus.c srcs_bonus/check_files_bonus.c srcs_bonus/error_handler_bonus.c srcs_bonus/exec_bonus.c srcs_bonus/get_cmds_path_bonus.c srcs_bonus/main_bonus.c
OBJ				=		$(SRC:$(SRC)/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS		=		$(SRC_BONUS:$(SRC_BONUS)/%.c=$(OBJ_BONUS_DIR)/%.o)
LIBFT			=		libft/libft.a

CPPFLAGS		=		-I./include -I./libft/include
CFLAGS			=		-Wall -Werror -Werror -g3

$(NAME):				$(OBJ)
							$(MAKE) -C $(LIBFT_DIR)
							cc $(CFLAGS) $(CPPFLAGS) $(OBJ) -o $(NAME) $(LIBFT)

$(NAME_BONUS):			$(OBJ_BONUS)
							$(MAKE) -C $(LIBFT_DIR)
							$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS) $(LIBFT)
					
$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all:					$(NAME)

bonus:					$(NAME_BONUS)

clean:
						$(MAKE) fclean -C $(LIBFT_DIR)
							rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean:					clean
							rm -f $(NAME) $(NAME_BONUS)

re:						fclean all

.PHONY:					all clean fclean re