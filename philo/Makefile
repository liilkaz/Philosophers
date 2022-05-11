NAME	=	philo

SRC		=	philo.c philo_threads.c philo_time.c philo_utils.c

HEADER		=	philo.h

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

OFF_COLOR		=	\033[0m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
L_BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
L_BLUE			=	\033[0;36m

all		:	$(NAME)

$(NAME)	:	$(SRC) $(HEADER)
	@$(CC) $(CFLAGS) $(SRC) -o $(NAME)
	@echo "$(GREEN)🍝 Simulation of philosophers compiled! 🍝 $(OFF_COLOR)"

clean:
	@echo "$(RED)🤷 Object files are absent! 🤷$(OFF_COLOR)"

fclean:	clean
	@$(RM) $(NAME) $(NAME)
	@echo "${RED}🗑 Program deleted!${OFF_COLOR}"

re:		fclean all

.PHONY	:	all clean fclean re

