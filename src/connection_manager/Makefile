# ============================================
#            AUTO-GENERATED MAKEFILE
# ============================================

CXX      := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -MMD -g

# Directories where .cpp and .hpp live
SRCDIRS  := ./ ../http_request_parser ../URI_parsing
BUILDDIR := build
TARGET   := connection_manager

# Allow <header.hpp> everywhere by adding ALL subdirectories
INCLUDES := -I. -I./ -I./build -I./http_request_parser -I./http_request_parser/test -I./URI_parsing -I./URI_parsing/utils -I../http_request_parser -I../URI_parsing -I../URI_parsing/utils

# Recursively find all .cpp files
SRC := $(shell find $(SRCDIRS) -name '*.cpp')

# Mirror directory tree into build/
OBJ := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRC))
DEPS := $(OBJ:.o=.d)

all: $(BUILDDIR) $(TARGET)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -lpthread -o $@

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BUILDDIR) $(TARGET)

.PHONY: all clean
