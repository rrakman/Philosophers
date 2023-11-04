CC = gcc
NAME = philo
SRC = philo.c ft_atoi.c
CFLAG = -Wall -Werror -Wextra -pthread #-fsanitize=thread
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):$(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all