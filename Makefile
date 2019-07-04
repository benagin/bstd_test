# Configuration options ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

debug ?= 0

# Component/target names ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

BSTD_TEST ?= bstd_test
EXAMPLES  ?= examples
INSTALL   ?= install

# Directory Layout ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# TODO: make this configurable and/or work on other machines.
INSTALL_DIR ?= /usr/local/lib

$(shell mkdir -p bin)
BIN_DIR ?= ./bin

SRC_DIR           ?= ./src
EXAMPLES_SRC_DIR  ?= ./examples

$(shell mkdir -p build/dependencies)
BUILD_DIR      ?= ./build
DEPENDENCY_DIR := $(BUILD_DIR)/dependencies
DEPENDENCIES   := $(DEPENDENCY_DIR)/dependencies
D_FILES        := $(DEPENDENCY_DIR)/$*.d

INC  := -Iinclude/

# Compiler Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

CXX 	  = g++
CXXFLAGS  = -std=c++2a -Wall -Werror -pedantic
LDFLAGS   = -shared
LINK      = -Lbin -L$(HOME)/Projects/bstd_test/bin
LINK_TEST = $(LINK) -lbstdtest


ifeq ($(debug), 1)
	CXXFLAGS += -g
endif

DEPS = -MMD -MF $(D_FILES)

# File Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#


EXAMPLES_SRCS      := $(shell find $(EXAMPLES_SRC_DIR) -path "*.cpp")
EXAMPLES_BASENAMES := $(basename $(EXAMPLES_SRCS))

SRCS := $(shell find $(SRC_DIR) -path "*.cpp")
OBJS := $(SRCS:.cpp=.o)
LIB  := $(BIN_DIR)/libbstdtest.so

# Object File Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.cpp.o: $(SRCS)
	@echo Compiling $<...
	@$(CXX) -c $(CXXFLAGS) $(DEPS) $(INC) $< -o $@
	@cat $(D_FILES) >> $(DEPENDENCIES)

# Target Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

all:	$(BSTD_TEST) $(EXAMPLES)

# Build bstd::test library.
.PHONY: $(BSTD_TEST)
$(BSTD_TEST):	$(LIB)
$(LIB):		$(OBJS)
	@echo Linking $<...
	@$(CXX) $(LDFLAGS) -o $@ $^
	@rm -f $(OBJS)

# Build all examples.
.PHONY: $(EXAMPLES)
$(EXAMPLES):            $(EXAMPLES_BASENAMES)
$(EXAMPLES_BASENAMES):	%: %.cpp $(LIB)
	@echo Compiling $<...
	@$(CXX) $(CXXFLAGS) $(DEPS) $(LINK_TEST) $(INC) $< -o $@
	@cat $(D_FILES) >> $(DEPENDENCIES)

# Install the library to $(INSTALL_DIR).
.PHONY: $(INSTALL)
$(INSTALL):	$(LIB)
	@echo Installing...
	@cp $(LIB) $(INSTALL_DIR)

# Cleanup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.PHONY: clean
clean:
	@echo Cleaning...
	@rm -f $(shell find $(DEPENDENCY_DIR) -path "*.d")
	@rm -f $(shell find . -path "*.o")
	@rm -f $(EXAMPLES_BASENAMES)
	@rm -f $(DEPENDENCIES)
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)

# Other stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# Include automatically generated dependencies.
-include $(DEPENDENCIES)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
