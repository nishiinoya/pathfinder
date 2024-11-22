NAME = libmx.a

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -Iinc -o $@ -c $<

uninstall:
	rm -f $(NAME)

reinstall: uninstall all

clean:
	rm -rf obj

.PHONY: all uninstall reinstall clean
