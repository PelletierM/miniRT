PROGNAME = miniRT 
PROGNAME_BONUS = miniRT_bonus

CFLAGS = -Wall -Wextra -Werror -lm -O3

LIB_DIR = ./lib
LIBFT = libft.a
LIBFT_DIR = $(LIB_DIR)/libft
MLX42 = libmlx42.a
MLX42_DIR = $(LIB_DIR)/MLX42/build

IDIR = include

SRCDIR = ./src
SRC = main_bonus.c parser_bonus.c parser_check_bonus.c parser_checker_line_bonus.c parser_value_setter_bonus.c \
	  errors_bonus.c parser_utils_bonus.c parser_ambient_bonus.c color_bonus.c parser_camera_bonus.c \
	  parser_light_bonus.c parser_sphere_bonus.c parser_plane_bonus.c parser_cylinder_bonus.c init_bonus.c parser_value_checker_bonus.c \
	  parser_value_checker2_bonus.c parser_utils2_bonus.c mrt_renderer_bonus.c hit_sphere_bonus.c \
	  op_vectors1_bonus.c op_vectors2_bonus.c camera_bonus.c hooks_bonus.c vect_utils1_bonus.c hit_cylinder_bonus.c \
	  quadratic_bonus.c cylinder_utils_bonus.c color2_bonus.c object_hit_bonus.c hit_plane_bonus.c \
	  object_normal_hit_bonus.c light_bonus.c camera_utils_bonus.c camera_mvmt_bonus.c \
	  vect_utils2_bonus.c hooks_obj_bonus.c hooks_mouse_bonus.c obj_mvmt_bonus.c hooks_mode_bonus.c \
	  perpixel_bonus.c sampling_bonus.c parser_material_bonus.c material1_bonus.c material2_bonus.c random_bonus.c \
	  texture_bonus.c texture_plane_bonus.c texture_sphere_bonus.c parser_triangle_bonus.c hit_triangle_bonus.c

SRC_BONUS = 

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
SRCS_BONUS = $(addprefix $(SRCDIR)/, $(SRC_BONUS))

all: $(PROGNAME)

$(PROGNAME): $(LIB_DIR)/$(MLX42) $(LIB_DIR)/$(LIBFT) $(SRCS) $(IDIR)/miniRT_bonus.h 
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
