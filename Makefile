# Configuration options ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

debug ?= 0

# Project and tool names ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

BSTD  := bstd
JSON  := json
ERROR := error
TEST  := test

# Directory Layout ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

$(shell mkdir -p bin)
BIN_DIR := ./bin

JSON_SRC  ?= ./src/json
ERROR_SRC ?= ./src/error
TEST_SRC  ?= ./src/test

$(shell mkdir -p build/dependencies)
DEPENDENCY_DIR := ./build/dependencies
DEPENDENCIES   := $(DEPENDENCY_DIR)/dependencies
D_FILES        := $(DEPENDENCY_DIR)/$*.d

JSON_INC  ?= -Iinclude/json
ERROR_INC ?= -Iinclude/error
TEST_INC  ?= -Iinclude/test
PROJ_INC  ?= $(JSON_INC) $(ERROR_INC) $(TEST_INC) -I$(JSON_SRC) -I$(ERROR_SRC) \
	     -I$(TEST_SRC)

INC_DIRS ?= $(PROJ_INC)

# Compiler Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

CXX 	 = g++
CXXFLAGS = -stdlib=libc++ -std=c++1z -Wall -Werror -pedantic -fPIC
LDFLAGS  = -shared

ifeq ($(debug), 1)
	CXXFLAGS += -g
endif

DEPS = -MMD -MF $(D_FILES)

# File Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BSTD_LIB := $(BIN_DIR)/libbstd.so

ERROR_SRCS := $(shell find $(ERROR_SRC) -path "*.cpp")
ERROR_OBJS := $(ERROR_SRCS:.cpp=.o)
ERROR_LIB := $(BIN_DIR)/libbstderror.so

JSON_SRCS := $(shell find $(JSON_SRC) -path "*.cpp")
JSON_OBJS := $(JSON_SRCS:.cpp=.o)
JSON_EXEC := $(BIN_DIR)/json
JSON_LIB  := $(BIN_DIR)/libbstdjson.so

TEST_SRCS := $(shell find $(TEST_SRC) -path "*.cpp")
TEST_OBJS := $(TEST_SRCS:.cpp=.o)
TEST_LIB  := $(BIN_DIR)/libbstdtest.so

BOOST_LIB :=

SRCS := $(JSON_SRCS) $(ERROR_SRCS) $(TEST_SRCS)
OBJS := $(JSON_OBJS) $(ERROR_OBJS) $(TEST_OBJS)
LIBS := $(ERROR_LIB) $(JSON_LIB) $(TEST_LIB)

LFLAGS := $(BOOST_LIB)

# Object File Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.cpp.o: $(SRCS)
	@echo Compiling $<...
	@$(CXX) -c $(CXXFLAGS) $(DEPS) $(INC_DIRS) $< -o $@
	@cat $(D_FILES) >> $(DEPENDENCIES)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# Executable Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

all:	$(ERROR) $(JSON) $(TEST) $(BSTD)

# bstd

# Library
bstd:	$(BSTD_LIB)
$(BSTD_LIB):    $(LIBS)
		@echo Linking $@...
		@$(CXX) $(CXXFLAGS) $(LIBS) -o $@
		@rm -f $(JSON_OBJS)

# bstd::json

# Executable
json:	$(JSON_EXEC)
$(JSON_EXEC):	$(JSON_LIB) $(JSON_OBJS)
		@echo Linking $@...
		@$(CXX) $(JSON_OBJS) $(LFLAGS) -o $@
		@rm -f $(JSON_OBJS)

# Library
$(JSON_LIB):	$(JSON_OBJS)
		@echo Linking $@...
		@$(CXX) $(LDFLAGS) $(LFLAGS) -o $@ $^

# bstd::error

# Library
error:	$(ERROR_LIB)
$(ERROR_LIB):	$(ERROR_OBJS)
		@echo Linking $@...
		@$(CXX) $(LDFLAGS) -o $@ $^
		@rm -f $(ERROR_OBJS)

# bstd::test

# Library
test:	$(TEST_LIB)
$(TEST_LIB):	$(TEST_OBJS)
		@echo Linking $@...
		@$(CXX) $(LDFLAGS) -o $@ $^
		@rm -f $(TEST_OBJS)


# Cleanup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.PHONY: clean
clean:
	@echo Cleaning...
	@rm -f $(shell find $(DEPENDENCY_DIR) -path "*.d")
	@rm -f $(shell find . -path "*.o")
	@rm -f $(DEPENDENCIES)
	@rm -f $(BIN_DIR)/*

# Other Stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# include automatically generated dependencies
-include $(DEPENDENCIES)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
