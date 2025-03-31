NAME := philo

CC := gcc

CFLAGS := -Wall -Werror -Wextra


SANITIZE := sanitize
SANITIZE_MEM := sanitize_mem

FSANITIZE := -fsanitize=thread -g3
FSANITIZE_MEM := -fsanitize=address -g
OBJDIR := obj


SRC = src/atoi.c src/philo.c src/utils.c  src/utils2.c \
	src/utils3.c src/forks.c \

all : $(NAME)


OBJ = $(patsubst src/%.c, $(OBJDIR)/%.o, $(SRC))

$(OBJDIR)/%.o : src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)PHILO COMPILED$(DEF_COLOR)"

clean :
	@echo "$(YELLOW)Deleting all object files....$(DEF_COLOR)"
	@rm -rf $(OBJDIR)
	@echo "$(RED)All object files were deleteated...$(DEF_COLOR)"

fclean : clean
	@echo "$(YELLOW)Deleting executable files....$(DEF_COLOR)"
	@rm -f $(NAME)
	@echo "$(RED)All executable files has been deleted.$(DEF_COLOR)"

re : fclean all

norm :
	@echo "$(CYAN)Norminette src/$(GREEN)"
	@norminette src/
	@echo "$(DEF_COLOR)"

$(SANITIZE) : $(OBJ)
	@$(CC) $(CFLAGS) $(FSANITIZE) $(OBJ) -o $(NAME)
	@echo "$(CYAN)Compiling philo with fsanitize$(DEF_COLOR)"


$(SANITIZE_MEM) : $(OBJ)
	@$(CC) $(CFLAGS) $(FSANITIZE_MEM) $(OBJ) -o $(NAME)
	@echo "$(CYAN)Compiling philo with fsanitize ADDRESS$(DEF_COLOR)"
# Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m