CXX      = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g

INCLUDES = -I../inc -I../src/http_request_parser

SRCS = \
	main.cpp \
	../src/Server.cpp \
	../src/ServerResponse.cpp \
	../src/http_request_parser/ControlData.cpp \
	../src/http_request_parser/Headers.cpp \
	../src/http_request_parser/Request.cpp \
	HeadersStub.cpp

OBJS = $(SRCS:.cpp=.o)

NAME = server_test

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
