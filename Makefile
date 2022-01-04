ifneq (,$(findstring xterm,${TERM}))
	BLACK        := $(shell tput -Txterm setaf 0)
	RED          := $(shell tput -Txterm setaf 1)
	GREEN        := $(shell tput -Txterm setaf 2)
	YELLOW       := $(shell tput -Txterm setaf 3)
	LIGHTPURPLE  := $(shell tput -Txterm setaf 4)
	PURPLE       := $(shell tput -Txterm setaf 5)
	BLUE         := $(shell tput -Txterm setaf 6)
	WHITE        := $(shell tput -Txterm setaf 7)
	RESET := $(shell tput -Txterm sgr0)
else
	BLACK        := ""
	RED          := ""
	GREEN        := ""
	YELLOW       := ""
	LIGHTPURPLE  := ""
	PURPLE       := ""
	BLUE         := ""
	WHITE        := ""
	RESET        := ""
endif

NAME = philo

MAKE = make

CC = gcc

CFLAGS += -Wall -Wextra -Werror

CFLAGS += -I ./inc

CCFLAGS += -pthread

SRC_FOLDER = src
OBJ_FOLDER = obj
INC_FOLDER = inc

SRC_FILES =	main.c \
		args_check.c \
		utils.c	\
		minilibft.c \
		message.c \
		thread_execute.c

SRC = $(addprefix $(SRC_FOLDER)/, $(SRC_FILES))
OBJ_FILES = $(SRC_FILES:%.c=%.o)
OBJ = $(addprefix $(OBJ_FOLDER)/, $(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(CCFLAGS)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c | $(OBJ_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_FOLDER):
	@tput setaf 3
	mkdir -p $(OBJ_FOLDER) 2> /dev/null
	@tput setaf 2

clean:
	@tput setaf 1
	rm -rf $(OBJ_FOLDER)
	@tput setaf 2

fclean: clean
	@tput setaf 1
	rm -rf $(NAME)
	@tput setaf 2

re: fclean all

.PHONY: all clean fclean re
