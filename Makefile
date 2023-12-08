PROGNAME = miniRT 
PROGNAME_BONUS = miniRT_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm -O3

LIB_DIR = ./lib
LIBFT = libft.a
LIBFT_DIR = $(LIB_DIR)/libft
MLX42 = libmlx42.a
MLX42_DIR = $(LIB_DIR)/MLX42/build

IDIR = include

SRCDIR = ./src
SRC = main.c parser.c parser_check.c parser_checker_line.c parser_value_setter.c \
	  errors.c parser_utils.c parser_ambient.c color.c parser_camera.c \
	  parser_light.c parser_sphere.c parser_plane.c parser_cylinder.c init.c parser_value_checker.c \
	  parser_value_checker2.c parser_utils2.c mrt_renderer.c hit_sphere.c \
	  op_vectors1.c op_vectors2.c camera.c hooks.c vect_utils1.c hit_cylinder.c \
	  quadratic.c cylinder_utils.c color2.c object_hit.c hit_plane.c \
	  object_normal_hit.c light.c camera_utils.c camera_mvmt.c hooks_keys1.c \
	  vect_utils2.c

SRC_BONUS = 

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
SRCS_BONUS = $(addprefix $(SRCDIR)/, $(SRC_BONUS))

all: $(PROGNAME)

$(PROGNAME): $(LIB_DIR)/$(MLX42) $(LIB_DIR)/$(LIBFT) $(SRCS)  
	$(CC) $(CFLAGS) -I$(IDIR) $(LIB_DIR)/$(MLX42) -lm -L"/Users/$(USER)/.brew/opt/glfw/lib/" -lglfw -framework Cocoa -framework OpenGL -framework IOKit -L$(LIB_DIR) -l$(patsubst lib%.a,%,$(LIBFT)) $(SRCS) -o $(PROGNAME)

bonus: $(LIB_DIR)/$(MLX42) $(LIB_DIR)/$(LIBFT) $(SRCS_BONUS)  
	$(CC) $(CFLAGS) -I$(IDIR) $(LIB_DIR)/$(MLX42) -lm -L"/Users/$(USER)/.brew/opt/glfw/lib/" -lglfw -framework Cocoa -framework OpenGL -framework IOKit -L$(LIB_DIR) -l$(patsubst lib%.a,%,$(LIBFT)) $(SRCS_BONUS) -o $(PROGNAME_BONUS)

$(LIB_DIR)/$(LIBFT):
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$(LIBFT) $(LIB_DIR)/$(LIBFT)
	cp $(LIBFT_DIR)/includes/$(patsubst %.a,%.h,$(LIBFT)) $(IDIR)/$(patsubst %.a,%.h,$(LIBFT))

$(LIB_DIR)/$(MLX42):
	@$(MAKE) dependencies
	@cd $(LIB_DIR); \
	if [ ! -d "MLX42" ] ; then \
		echo "git clone https://github.com/PelletierM/MLX42.git"; \
		git clone https://github.com/PelletierM/MLX42.git; \
	fi; \
	cd MLX42; \
	echo "cmake -B build"; \
	cmake -B build; \
	echo "cmake --build build -j4"; \
	cmake --build build -j4; \
	cd ../..; \
	cp $(MLX42_DIR)/$(MLX42) $(LIB_DIR)/$(MLX42)
	cp $(LIB_DIR)/MLX42/include/MLX42/MLX42.h $(IDIR)/MLX42.h

dependencies: dep_msg brew cmake glfw

dep_msg:
	@echo "Validating dependencies..."

brew:
	@if [ $(shell command -v brew | wc -l) -lt 1 ] ; then \
		echo "Homebrew is not installed, please execute \"make 42homebrew\" and restart shell"; \
		exit 1; \
	fi

42homebrew:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

cmake:
	@if [ $(shell brew list -1 | grep -w cmake | wc -l) -lt 1 ] ; then \
		echo "brew install cmake"; \
		brew install cmake; \
	fi

glfw:
	@if [ $(shell brew list -1 | grep -w glfw | wc -l) -lt 1 ] ; then \
		echo "brew install glfw"; \
		brew install glfw; \
	fi

test:
	make -C ./test/
	@cd test ; \
		bash ./test_parsing.sh ; \
		cd ..

render:
	make
	./miniRT map.rt


clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(LIB_DIR)/MLX42

fclean: clean
	rm -f $(LIBFT_DIR)/$(LIBFT)
	rm -f $(IDIR)/MLX42.h
	rm -f $(IDIR)/libft.h
	rm -f ./$(PROGNAME) ./$(PROGNAME_BONUS) $(LIB_DIR)/$(LIBFT) $(LIB_DIR)/$(MLX42)

re: fclean all

.PHONY: dependencies dep_msg brew 42homebrew cmake glfw clean fclean re test
