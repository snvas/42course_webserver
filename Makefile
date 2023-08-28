NAME = webserv

CC = clang++

RM = rm -rf

INC = -I include

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRCS = 	main.cpp \
		Parser.cpp \
		Server.cpp \
		Request.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "created $(NAME) exec file!"
	
%.o:%.cpp
		$(CC) $(CFLAGS) $(INC) -c $< -o $@
		@echo "Compile "$<" successully!"

clean:
		$(RM) $(OBJS)
		@echo "Cleanup successully!"
	
fclean: clean
		$(RM) $(NAME)
		$(RM) $(OBJS)

re: fclean all
