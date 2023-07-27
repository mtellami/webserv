NAME = webserv
INC = -I include -I src/parse

NONE = '\033[0m'
GREEN = '\033[0;32m'
GRAY = '\033[2;37m'

CPPFLAGS = -Wall -Wextra -Werror -std=c++98 $(INC)

SRC = src/multiplex/webserv.cpp\
	src/multiplex/Server.cpp\
	src/multiplex/Cluster.cpp\
	src/multiplex/Client.cpp\
	src/parse/main.cpp src/parse/parsing.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o: %.cpp
	@echo $(GRAY) "Making .. $< " $(NONE)
	@c++ $(CPPFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir $(OBJDIR)

$(NAME): $(OBJ)
	@c++ $(CPPFLAGS) $^ -o $(NAME)
	@echo $(GREEN) "Compiled ..." $(NONE)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
