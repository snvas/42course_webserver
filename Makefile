NAME = webserv

CC = c++
#CC = clang++

RM = rm -rf

INC = -I include

CFLAGS = -Wall -Wextra -Werror -std=c++98 -g

SRCS = 	main.cpp \
		Parser.cpp \
		Server.cpp \
		RequestParser.cpp \
		ResponseHandler.cpp \
		StatusCode.cpp \
		ResponseHandlerGET.cpp \
		ResponseHandlerDELETE.cpp \
		ResponseHandlerPOST.cpp \
		ResponseHandlerCGI.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "created $(NAME) exec file!"
	
%.o:%.cpp
		$(CC) $(CFLAGS) $(INC) -c $< -o $@
		@echo "Compile "$<" successully!"

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) config/config.conf

clean:
		$(RM) $(OBJS)
		@echo "Cleanup successully!"
	
fclean: clean
		$(RM) $(NAME)
		$(RM) $(OBJS)

re: fclean all
