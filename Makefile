# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tatahere <tatahere@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 09:52:48 by tatahere          #+#    #+#              #
#    Updated: 2025/07/03 12:30:47 by tatahere         ###   ########.fr        #
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
VPATH	+= $(SRC_DIR)/containers/:
VPATH	+= $(SRC_DIR)/configuration_parser/:
VPATH	+= $(SRC_DIR)/configuration_parser/symbol/:
VPATH	+= $(SRC_DIR)/configuration_parser/symbol/terminal/:
VPATH	+= $(SRC_DIR)/configuration_parser/symbol/terminal/character_tokens/:
VPATH	+= $(SRC_DIR)/configuration_parser/symbol/terminal/keywords/:
VPATH	+= $(SRC_DIR)/configuration_parser/symbol/terminal/literals/

CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -MMD

CINC		:=	-I$(BIN_DIR)
CINC		+=	-I$(INC_DIR)
CINC		+=	-I$(subst : , -I,$(VPATH))
CXXFLAGS	+=	$(CINC)

CDEBUG		:=	-g
CXXFLAGS	+=	$(CDEBUG)

NAME	=	test

OBJ		:=	main.o						\
			ALexer.o					\
			ConfigFileLexer.o			\
			ATerminal.o					\
			ATerminalFactory.o			\
			Number.o					\
			TextCharSetConfigFile.o		\
			WhiteSpace.o				\
			KeyColon.o					\
			KeyLeftCurlyBracket.o		\
			KeyRightCurlyBracket.o		\
			KeyWordServer.o				\
			KeyWordServerName.o			\

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
