NAME	= so_long
HEADER	= so_long.h

LIST		= GNL/get_next_line.c GNL/get_next_line_utils.c so_long.c secondary_functions.c map_initialization.c \
				buttons.c parser.c

OBJ			= $(LIST:.c=.o)

FLAGS       = -Wall -Wextra -Werror

%.o:%.c		$(HEADER)
		    gcc $(FLAGS) -Imlx -c $< -o $@

$(NAME) :	$(OBJ) $(HEADER)
			gcc $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

#bonus :		$(OBJ) $(OBJ_B) $(HEADER)
#			gcc $(OBJ_B) -o $(NAME_B)

all :		$(NAME)

clean :
			rm -f $(OBJ)

fclean :	clean
			rm -f $(NAME) $(OBJ)

re :		fclean all

.PHONY :	all clean fclean re
