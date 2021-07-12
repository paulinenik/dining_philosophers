SRCS	= 	srcs/main.c \
			srcs/utils.c \
			srcs/data_management.c

HDRS	= ./includes

NAME	= philo

CC		= gcc

OBJS	= ${SRCS:c=o}

RM		= rm -f

CFLAGS = -Wall -Wextra -Werror

$(NAME):	$(OBJS) $(HDRS) $(SRCS)
			$(CC) $(CFLAGS)  -I$(HDRS) $(OBJS) -o $(NAME)
			@echo "\033[36mphilosophers by rgordon are compiled successfully\nmade with norminette 3.3.0\033[0m"

$(OBJS):	%.o:%.c
			$(CC) $(CFLAGS) -I$(HDRS) -c $< -o $@
		
all:		$(NAME)

clean:	
			$(RM) $(NAME) $(OBJS) 

test_1:		$(NAME)
			@echo "\033[36;1mA philosopher should die!\n\033[0m"
			./$(NAME) 1 800 200 200

test_2:		$(NAME)
			@echo "\033[36;1mNo one should die!\n\033[0m"
			./$(NAME) 5 800 200 200

test_3:		$(NAME)
			@echo "\033[36;1mThe simulation should stop after each philosohper eats at least 7 times!\n\033[0m"
			./$(NAME) 5 800 200 200 7

test_4:		$(NAME)
			@echo "\033[36;1mNo one should die!\n\033[0m"
			./$(NAME) 4 410 200 200

test_5:		$(NAME)
			@echo "\033[36;1mA philosopher should die!\n\033[0m"
			./$(NAME) 4 310 200 100
			
fclean:		clean
			@echo "\033[36mDone!\n\033[0m"

re:			fclean all

norm:
			norminette *

.PHONY:		all clean fclean re norm