NAME = ft_ls

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = includes/

SRCS =         main.c\
			   parse_options.c\
			   util_cmp.c\
			   util_error.c\
			   util_file_stat.c\
			   util_fileds.c\
			   util_filling_spase.c\
			   util_list.c\
			   util_main_struct.c\
			   util_print.c\
			   util_print_l.c\
			   util_stack.c\
			   util_queue.c

OBJ = $(SRCS:.c=.o)

LIBFTDIR = srcs/libft/

all: $(NAME)

$(NAME) : $(OBJ) $(LIBFTDIR)libft.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./$(LIBFTDIR) -lft

%.o: srcs/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDES) -I $(LIBFTDIR)

$(LIBFTDIR)libft.a: srcs/libft/Makefile
	make -C srcs/libft/

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)

re: clean all

norm:
	norminette srcs/ includes/*.h