NAME	= so_long
NAME_B	= so_long_bonus
HEADER	= so_long.h

LIST		= GNL/get_next_line.c GNL/get_next_line_utils.c main_part/so_long.c main_part/secondary_functions_0.c \
				main_part/secondary_functions_1.c main_part/buttons.c main_part/parser.c main_part/map_initialization.c

LIST_B		= GNL/get_next_line.c GNL/get_next_line_utils.c bonus_part/so_long.c bonus_part/secondary_functions_0.c \
				bonus_part/secondary_functions_1.c bonus_part/buttons.c bonus_part/parser.c bonus_part/map_initialization.c

OBJ			= $(LIST:.c=.o)
OBJ_B		= $(LIST_B:.c=.o)

FLAGS       = -Wall -Wextra -Werror

%.o:%.c		$(HEADER)
		    gcc $(FLAGS) -Imlx -c $< -o $@

$(NAME) :	$(OBJ) $(HEADER)
			gcc $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

bonus :		$(OBJ_B) $(HEADER)
			gcc $(OBJ_B) -lmlx -framework OpenGL -framework AppKit -o $(NAME_B)

all :		$(NAME) bonus

clean :
			rm -f $(OBJ) $(OBJ_B)

fclean :	clean
			rm -f $(NAME) $(NAME_B)

re :		fclean all

.PHONY :	all clean fclean re bonus
