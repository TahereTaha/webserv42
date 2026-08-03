# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: capapes <capapes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 09:52:48 by tatahere          #+#    #+#              #
#    Updated: 2026/08/03 10:43:28 by taha             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOT_DIR	=	./

BIN_DIR		=	bin/
SRC_DIR		=	src/
INC_DIR		=	inc/
TEST_DIR	=	test/
TEST_BIN_DIR	=	test/bin/

RM		=	rm -rf
CXX		=	g++

VPATH	= $(ROOT_DIR):
VPATH	+= $(SRC_DIR):
VPATH	+= $(SRC_DIR)containers:
VPATH	+= $(SRC_DIR)containers/tree:
VPATH	+= $(SRC_DIR)configuration_parser:
VPATH	+= $(SRC_DIR)configuration_parser/lexer:
VPATH	+= $(SRC_DIR)configuration_parser/parser:
VPATH	+= $(SRC_DIR)configuration_parser/parser/rules:
VPATH	+= $(SRC_DIR)configuration_parser/symbol:
VPATH	+= $(SRC_DIR)configuration_parser/symbol/non_terminal:
VPATH	+= $(SRC_DIR)configuration_parser/symbol/non_terminal/server_body_subtrees:
VPATH	+= $(SRC_DIR)configuration_parser/symbol/terminal:
VPATH	+= $(SRC_DIR)configuration_parser/symbol/terminal/character_lexeme:
VPATH	+= $(SRC_DIR)configuration_parser/symbol/terminal/keywords:
VPATH	+= $(SRC_DIR)configuration_parser/symbol/terminal/literals:
VPATH	+= $(SRC_DIR)exceptions:
VPATH	+= $(SRC_DIR)URI_parsing:
VPATH	+= $(SRC_DIR)URI_parsing/utils:
VPATH	+= $(SRC_DIR)connection_manager:
VPATH	+= $(SRC_DIR)http_request_parser:
VPATH	+= $(SRC_DIR)Server

CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -MMD -g

CINC		:=	-I$(BIN_DIR)
CINC		+=	-I$(INC_DIR)
CINC		+=	-I$(subst : , -I,$(VPATH))
CXXFLAGS	+=	$(CINC)

CDEBUG		:=	-g -fsanitize=address 
CXXFLAGS	+=	$(CDEBUG)

CXXFLAGS	+= $(CXXMACROS)

NAME	=	webserv

OBJ		:=	main.o						\
										\
			Args.o						\
			IR_printing_functions.o		\
			ConfigurationParser.o		\
										\
			parse_exception.o			\
			multy_parse_exception.o		\
										\
			ASymbol.o					\
			ATerminal.o					\
			ANonTerminal.o				\
			AEvaluable.o				\
										\
			ALexer.o					\
			ConfigFileLexer.o			\
										\
			ATerminalFactory.o			\
			ConfigFileTerminalFactory.o	\
										\
			Number.o					\
			TextConfigFile.o			\
			WhiteSpace.o				\
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
			KeySemicolon.o				\
			KeyLeftCurlyBracket.o		\
			KeyRightCurlyBracket.o		\
										\
			AParser.o					\
			AParsingRule.o				\
			ParsingRuleSymbol.o			\
			ParsingRuleAnd.o			\
			ParsingRuleOr.o				\
			ParsingRuleRepetition.o		\
										\
			SymbolConfigContext.o		\
			SymbolServer.o				\
			SymbolServerName.o			\
			SymbolListen.o				\
			SymbolClientMaxBodySize.o	\
			SymbolErrorPage.o			\
			SymbolLocation.o			\
			SymbolLimitExcept.o			\
			SymbolReturn.o				\
			SymbolRoot.o				\
			SymbolAutoIndex.o			\
			SymbolIndex.o				\
										\
			tokenize.o					\
			percent_encoding_utils.o	\
			utils.o						\
										\
			Scheme.o					\
			UserInfo.o					\
			IpLiteral.o					\
			Host.o						\
			Authority.o					\
			Path.o						\
			Query.o						\
			Fragment.o					\
			URI.o						\
										\
			EpollConnectionManager.o	\
			Log.o						\
			Socket.o					\
			setUpSockets.o				\
										\
			ControlData.o				\
			FieldValidators.o			\
			Headers.o					\
			ReqScanner.o				\
			Request.o					\
			Schemas.o					\
										\
			Server.o					\
			ServerManager.o				\
			ServerResponse.o			\


TESTS_SRCS	:=	$(notdir $(shell find . -name "*.test.cpp"))

TESTS_OBJ	:=	$(patsubst %.cpp, $(TEST_BIN_DIR)%.o,$(TESTS_SRCS))

TESTS		:=	$(patsubst %.cpp, $(TEST_DIR)%.o,$(TESTS_SRCS))

OBJ		:=	$(addprefix $(BIN_DIR), $(OBJ))

DEP		:=	$(OBJ:.o=.d) $(TESTS_OBJ:.o=.d)

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

demo:
	rm -rf /tmp/http_server
	cp -r ./demos/complet_example/http_server /tmp/http_server/
	./webserv ./demos/complet_example/parser_rules_test_7.conf
	

test : build_test
	@echo //
	@echo //	runing all the tests
	@echo //
	zsh run_tests.sh

build_test: $(TEST_DIR) $(TEST_OBJ_DIR) $(TESTS)

$(TEST_DIR):
	mkdir -p $(TEST_DIR)

$(TEST_OBJ_DIR):
	mkdir -p $(TEST_OBJ_DIR)

$(TEST_DIR)%.run: $(TEST_OBJ_DIR)%.o $(NAME) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

run : all
	bash setup.sh
	./webserv test/parser_rules_test_7.conf


-include $(DEP)

.PHONY:	all clean fclean re test debug test_debug
