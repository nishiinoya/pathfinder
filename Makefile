NAME = pathfinder

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

SRC = ./src
INC = ./inc
OBJ = ./obj
LIB = ./libmx

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)
LIBMX = $(LIB)/libmx.a
LIB_INC = $(LIB)/inc

all: $(NAME)

$(NAME): $(LIBMX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBMX) -o $(NAME)

$(LIBMX):
	@$(MAKE) -C $(LIB)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -I$(INC) -I$(LIB_INC) -c $< -o $@

$(OBJ):
	mkdir -p $(OBJ)

clean:
	@$(MAKE) -C $(LIB) clean
	rm -rf $(OBJ)
	rm -f $(LIBMX)

uninstall:
	@$(MAKE) -C $(LIB) uninstall
	rm -f $(NAME)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall
