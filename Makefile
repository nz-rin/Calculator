# Compiler
CXX 			= g++
CXXFLAGS 		= -g -Wall -Wextra -Iinclude
CXXDBFLAG 		= -DDEBUG

# Directories
DIR_ROOT		= $(PWD)
DIR_BUILD 		= $(DIR_ROOT)/build
DIR_SRC 		= $(DIR_ROOT)/src

# Files
# Source code files
SRC_FILES		= $(wildcard $(DIR_SRC)/*.cxx)

# Main object files
MAIN_O_FILES 	= $(patsubst $(DIR_SRC)/%.cxx, $(DIR_BUILD)/%.o, $(SRC_FILES))


# Main
MAIN_ELF 		= $(DIR_BUILD)/main


build-clean:
	rm -rf $(DIR_BUILD)/*

build-run: $(MAIN_ELF)
	$(MAIN_ELF) $(ARGS)

build-main: $(MAIN_ELF)

# Link object files for build main
$(MAIN_ELF): $(MAIN_O_FILES)
	$(CXX) $(CXXFLAGS) -o $(MAIN_ELF) $(MAIN_O_FILES)

# Compile object files for build main
$(DIR_BUILD)/%.o: $(DIR_SRC)/%.cxx | $(DIR_BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@
