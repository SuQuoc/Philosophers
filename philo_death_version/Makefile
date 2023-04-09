NAME		= philo
ARGV		= 4 200 400 200
#n_philos, t_die, t_eat, t_sleep,
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -pthread -g
#-pthread

SRC_PATH 	= src
OBJ_PATH 	= obj

SRC			= 	main.c \
				init.c \
				ft_atoi.c \
				ft_strlen.c \
				routine.c \
				input_check.c \
				threads_and_mutex.c \
				death_things.c \
				time_utils.c 

SRCS 		= $(addprefix $(SRC_PATH)/, $(SRC))
OBJ 		= $(SRC:.c=.o)
OBJS 		= $(addprefix $(OBJ_PATH)/, $(OBJ))


.PHONY: all bonus clean fclean re aa va seelib norm normb
all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) 
	@echo "$(GREEN)Executable \"$(NAME)\" succesfully created.$(NC)"

#General
clean:
	rm -rf $(OBJ_PATH)
	@echo "$(MAGENTA)Obj directory removed.$(NC)"
#	$(MAKE) -C $(LIBFT_DIR) clean
#	@echo "$(MAGENTA)Make clean in directory "$(LIBFT_DIR)" invoked.$(NC)"

fclean: clean
	rm -f $(NAME)
	@echo "$(MAGENTA)Deleted executable named: $(NAME)$(NC)"
#	$(MAKE) -C $(LIBFT_DIR) fclean
#	@echo "$(MAGENTA)Make fclean in directory "$(LIBFT_DIR)" invoked.$(NC)"

re: fclean all
	@echo "$(GREEN)Recompilation successfully done!$(NC)"

aa: re
	@echo "$(GREEN)Executing programm with \"TEST_INPUT\" of the Makefile.$(NC)"
	./$(NAME) $(ARGV)

va: re
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	./$(NAME) $(ARGV)


hel: re
	valgrind -s --tool=helgrind --show-below-main=yes ./$(NAME) $(ARGV)
#valgrind \
#--tool=helgrind \
#-s \
#./$(NAME) $(ARGV)

debug : CFLAGS += -g
debug : fclean all

seelib:
	@ar -t $(NAME)

norm: $(SRCS)
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(NAME).h
	@echo "$(BWHITE)All source files checked with norminette.$(NC)"









#--------COLORS---------------------------------#
RED			=	\033[0;31m
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
BLUE 		=	\033[0;34m
MAGENTA 	=	\033[0;35m
CYAN 		=	\033[0;36m
WHITE		=	\033[0;37m
NC			=	\033[0m


#-------BOLD COLORS-----------------------------#
BRED		=	\033[1;31m
BGREEN		=	\033[1;32m
BYELLOW		=	\033[1;33m
BBLUE 		=	\033[1;34m
BMAGENTA 	=	\033[1;35m
BCYAN 		=	\033[1;36m
BWHITE		=	\033[1;37m
