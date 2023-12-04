PROGNAME = test_parsing 

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIB_DIR = ../lib
LIBFT = libft.a
LIBFT_DIR = $(LIB_DIR)/libft

IDIR = ../include

SRCDIR = ../src
SRC = parser.c parser_check.c parser_checker_line.c parser_value_setter.c \
	  errors.c parser_utils.c parser_ambient.c color.c parser_camera.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))


all: $(PROGNAME)

$(PROGNAME): $(LIB_DIR)/$(LIBFT) $(SRCS) main.c 
	$(CC) $(CFLAGS) -I$(IDIR) -L$(LIB_DIR) -lft $(SRCS) main.c -o $(PROGNAME)

clean:
	rm -f main.o

fclean: clean
	rm -f test

re: fclean all

.PHONY: dependencies dep_msg brew 42homebrew cmake glfw clean fclean re
