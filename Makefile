#******************************************************************************#
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: pacovali <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/01 00:42:00 by pacovali      #+#    #+#                  #
#    Updated: 2019/01/01 00:42:01 by pacovali      ########   odam.nl          #
#                                                                              #
#******************************************************************************#

NAME = fdf
SRCS = main.c get_map.c set_grid.c man_grid.c keyboard.c display1.c \
display2.c
OBJS = main.o get_map.o set_grid.o man_grid.o keyboard.o display1.o \
display2.o
MKOBJ = @gcc -Wall -Wextra -Werror -c
LFTHDR = -I libft
LFT = -L libft/ -lft
MKLFT = @make -C libft/ fclean && make -C libft/ && make -C libft/ clean
MLXHDR = -I lmlx
MLX = -L lmlx/ -lmlx -framework OpenGL -framework AppKit 
MKMLX = @make -C lmlx/ clean && make -C lmlx/
MKEXE = @gcc -o


all: $(NAME)
$(NAME):
	$(MKLFT)
	$(MKMLX)
	$(MKOBJ) $(SRCS) $(LFTHDR) $(MLXHDR)
	$(MKEXE) $(NAME) $(OBJS) $(HDRS) $(LFT) $(MLX)

clean:
	@rm -f $(OBJS) *~

fclean: cleanlib clean
	@rm -f $(NAME)

cleanlib:
	@make -C libft/ fclean
	@make -C lmlx/ clean

re: fclean all