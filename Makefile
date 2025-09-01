# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tatahere <tatahere@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 09:52:48 by tatahere          #+#    #+#              #
#    Updated: 2025/09/01 19:41:48 by tatahere         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT_DIR	=	./

BIN_DIR		=	bin/
SRC_DIR		=	src/
INC_DIR		=	inc/

RM		=	rm -rf
CXX		=	c++

VPATH	= $(ROOT_DIR):
VPATH	+= $(SRC_DIR):
VPATH	+= $(SRC_DIR)containers:
VPATH	+= $(SRC_DIR)containers/tree:
VPATH	+= $(SRC_DIR)configuration_parser:
VPATH	+= $(SRC_DIR)configuration_parser/lexer:
VPATH	+= $(SRC_DIR)configuration_parser/symbol:
VPATH	+= $(SRC_DIR)configuration_parser/symbol/non_terminal:
VPATH	+= $(SRC_DIR)configuration_parser/symbol/terminal:
VPATH	+= $(SRC_DIR)configuration_parser/symbol/terminal/character_lexeme:
VPATH	+= $(SRC_DIR)configuration_parser/symbol/terminal/keywords:
VPATH	+= $(SRC_DIR)configuration_parser/symbol/terminal/literals:
VPATH	+= $(SRC_DIR)exceptions

CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -MMD -g

CINC		:=	-I$(BIN_DIR)
CINC		+=	-I$(INC_DIR)
CINC		+=	-I$(subst : , -I,$(VPATH))
CXXFLAGS	+=	$(CINC)

CDEBUG		:=	-g
CXXFLAGS	+=	$(CDEBUG)

CXXFLAGS	+= $(CXXMACROS)

NAME	=	webserv

OBJ		:=	main.o						\
										\
			ASymbol.o					\
			ATerminal.o					\
			ATerminalFactory.o			\
			ConfigFileTerminalFactory.o	\
										\
			Number.o					\
			TextConfigFile.o			\
			WhiteSpace.o				\
										\
			KeySemicolon.o				\
			KeyLeftCurlyBracket.o		\
			KeyRightCurlyBracket.o		\
										\
			AKeyWord.o					\
			KeyWordServer.o				\
			KeyWordServerName.o			\
			KeyWordListen.o				\
			KeyWordClientMaxBodySize.o	\
			KeyWordErrorPage.o			\
			KeyWordLocation.o			\
			KeyWordReturn.o				\
			KeyWordLimitExept.o			\
			KeyWordRoot.o				\
			KeyWordAutoIndex.o			\
			KeyWordIndex.o				\
										\
			ANonTerminal.o				\
			ServerSymbol.o				\
										\
			parse_exception.o			\
			multy_parse_exception.o		\
										\
			Args.o						\
			Parser.o					\
			ALexer.o					\
			ConfigFileLexer.o			\


OBJ		:=	$(addprefix $(BIN_DIR), $(OBJ))

DEP		:=	$(OBJ:.o=.d)


all	:	$(BIN_DIR) $(NAME)

$(BIN_DIR)		:
	mkdir $(BIN_DIR)

$(NAME) : $(OBJ) Makefile
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

$(BIN_DIR)%.o : %.cpp	Makefile 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	echo $(CINC)
	$(RM) $(BIN_DIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all

-include $(DEP)

.PHONY:	all clean fclean re
