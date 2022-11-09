NAME = philo

FLAGS = -Wall -Wextra -Werror -g -pthread

CC = cc

SRC_DIR = ./src/

SRCS = dinner.c stop.c lifetime.c ft_atoi.c philosophers.c

FUNCS = $(addprefix $(SRC_DIR), $(SRCS))

RM = rm -rf

all:		$(NAME)

$(NAME):	$(FUNCS)
			@$(CC) $(FLAGS) $(FUNCS) -o $(NAME)
			@echo "\033[32m 💯 | Philosophers created."

clean: 
			@${RM} ${NAME}.dSYM
			@echo "\033[33m 🧹  | Philosophers cleaned."

fclean: 	clean
			@$(RM) $(NAME)
			@echo "\033[33m 🌪️  | Philosophers all cleaned."

re:			fclean all

.PHONY:		all clean fclean re
