NAME	= philo_bonus
SRC		= main.c run_philos_bonus.c run_philos_bonus_utils.c utils_bonus.c
CC		= @cc
CFLAGS	= -Wall -Werror -Wextra -g3 -lpthread -lrt

all:		$(NAME)

$(NAME):	$(SRC)
			$(CC) $(CFLAGS) $(^) -o $(@) 
#-fsanitize=address
#$(CC) $(CFLAGS) $(^) -o $(@) -fsanitize=thread

clean:
			@rm -f *.o

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re