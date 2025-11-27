# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile_generator.py                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: capapes <capapes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/27 13:52:21 by capapes           #+#    #+#              #
#    Updated: 2025/11/27 14:42:33 by capapes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#!/usr/bin/env python3
# Example call: 
# MAKEFILE CONNECTION MANAGER
# python3 makefile_generator.py connection_manager  ./ ../http_request_parser ../URI_parsing
# MAKEFILE HTTP REQUEST HANDLER
# python3 makefile_generator.py connection_manager  ./ ../http_request_parser ../URI_parsing

import sys
from pathlib import Path
import textwrap
import os

def collect_all_subdirs(dir_list):
    """Return all directories recursively under each given root folder."""
    all_dirs = []
    for root in dir_list:
        root_path = Path(root)
        if root_path.is_dir():
            for d, _, _ in os.walk(root):
                all_dirs.append(d)
    return all_dirs


def make_template(src_dirs, include_dirs, target):
    # Turn include dirs into Make syntax:  -I dir1 -I dir2 ...
    include_paths = " ".join(f"-I{d}" for d in include_dirs)

    return textwrap.dedent(f"""
        # ============================================
        #            AUTO-GENERATED MAKEFILE
        # ============================================

        CXX      := c++
        CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -MMD -g

        # Directories where .cpp and .hpp live
        SRCDIRS  := {src_dirs}
        BUILDDIR := build
        TARGET   := {target}

        # Allow <header.hpp> everywhere by adding ALL subdirectories
        INCLUDES := -I. {include_paths}

        # Recursively find all .cpp files
        SRC := $(shell find $(SRCDIRS) -name '*.cpp')

        # Mirror directory tree into build/
        OBJ := $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRC))
        DEPS := $(OBJ:.o=.d)

        all: $(BUILDDIR) $(TARGET)

        $(BUILDDIR):
        \tmkdir -p $(BUILDDIR)

        $(TARGET): $(OBJ)
        \t$(CXX) $(CXXFLAGS) $(OBJ) -lpthread -o $@

        $(BUILDDIR)/%.o: %.cpp
        \tmkdir -p $(dir $@)
        \t$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

        -include $(DEPS)

        clean:
        \trm -rf $(BUILDDIR) $(TARGET)

        .PHONY: all clean
    """).strip() + "\n"


def main():
    if len(sys.argv) < 3:
        print("Usage:")
        print("  python3 makefile_generator.py <target> <src_dirs...>")
        print("\nExample:")
        print("  python3 makefile_generator.py server src modules")
        return

    args = sys.argv[1:]
    target = args.pop(0)
    src_dirs = args

    # Collect ALL subdirectories for -I flags
    include_dirs = collect_all_subdirs(src_dirs)

    Path("build").mkdir(exist_ok=True)

    makefile_contents = make_template(
        src_dirs=" ".join(src_dirs),
        include_dirs=include_dirs,
        target=target
    )

    with open("Makefile", "w") as f:
        f.write(makefile_contents)

    print("Makefile generated successfully with recursive include paths!")


if __name__ == "__main__":
    main()
