
########################################
#                LIB NAME               #
#########################################

NAME = philo

#########################################
#              COMPILATOR               #
#########################################

CC = gcc

#########################################
#           COMPILATOR FLAGS            #
#########################################

FLAGS = -Wall -Wextra -Werror
SAN = -fsanitize=address -g3 -O3

#########################################
#           LIB FUNCTIONS               #
#########################################

SRC = src/atoi.c src/philo.c src/utils.c  src/utils2.c \
	src/utils3.c src/forks.c \


#########################################
#               OBJECTS                 #
#########################################

OBJ = $(patsubst src/%.c, $(ODIR)/%.o, $(SRC))

#########################################
#               OBJECTS                 #
#########################################

ODIR := odir

#########################################
#            CLEAN FUNCTION             #
#########################################

CLEAN = rm -rf

#########################################
#              COMPILE ALL              #
#########################################

all: $(NAME)

#########################################
#         COMPILE PHILOSOPHER           #
#########################################

$(NAME): $(OBJ)
	@echo "#########################################"
	@echo "#          Compiling Philo...           #"
	@echo "#########################################"
	@$(CC) $(FLAGS) $^ -o $@

#########################################
#                 MKDIR                 #
#########################################

$(ODIR) :
	@mkdir -p $(ODIR)

#########################################
#           COMPILE .c to .o            #
#########################################

$(ODIR)/%.o : src/%.c | $(ODIR)
	$(CC) $(FLAGS) -c $< -o $@

#########################################
#              DELETE .o                #
#########################################

clean:
	@$(MAKE) clean -s -C
	@$(CLEAN) $(OBJ)
	@echo "files deleted"

#########################################
#              DELETE ALL               #
#########################################

fclean: clean
	@$(MAKE) fclean -s -C
	@$(CLEAN) $(NAME) $(ODIR)
	@echo "program deleted"

#########################################
#         DELETE ALL & REMAKE           #
#########################################

re: fclean all

.PHONY: all re clean fclean
