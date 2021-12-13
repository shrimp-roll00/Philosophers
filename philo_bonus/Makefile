MAKEFLAGS += -s

NAME = philo_bonus

CC = gcc
CFLAGS = -Wall -Werror -Wextra

INC = $(shell find inc -name '*.h')
INC_DIR = inc

SRC = $(shell find src -name '*.c')
OBJ = $(SRC:%.c=%.o)

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	printf "\n🌸 \e[38;5;211mcompiling...\e[m\n"
	$(CC) $(CFLAGS) -I $(INC_DIR) $^ -o $@
	printf "🌸 \e[38;5;211mdone!\e[m\n"

%.o: %.c $(INC)
	printf "🌸 \e[38;5;211m$<\e[m\n"
	$(CC) $(CFLAGS) -I $(INC_DIR) $< -c -o $@

clean:
	$(RM) $(OBJ)
	printf "🌸 \e[38;5;211mobjects removed.\e[m\n"

fclean: clean
	$(RM) $(NAME)
	printf "🌸 \e[38;5;211m./$(NAME) removed.\e[m\n"

re: fclean all

.PHONY: all clean fclean re
