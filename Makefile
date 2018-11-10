# Configuration options ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

debug ?= 0

# Project and tool names ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

BSTD  	 ?= bstd
JSON  	 ?= json
ERROR 	 ?= error
TEST  	 ?= test
EXAMPLES ?= examples
TESTS    ?= tests

# Directory Layout ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

$(shell mkdir -p bin)
BIN_DIR ?= ./bin

JSON_SRC  ?= ./src/json
ERROR_SRC ?= ./src/error
TEST_SRC  ?= ./src/test

JSON_EXAMPLES_SRC  ?= ./examples/json
TEST_EXAMPLES_SRC  ?= ./examples/test

JSON_TESTS_SRC  ?= ./test/json

$(shell mkdir -p build/dependencies)
DEPENDENCY_DIR ?= ./build/dependencies
DEPENDENCIES   := $(DEPENDENCY_DIR)/dependencies
D_FILES        := $(DEPENDENCY_DIR)/$*.d

JSON_INC  ?= -Iinclude/json
ERROR_INC ?= -Iinclude/error
TEST_INC  ?= -Iinclude/test
PROJ_INC  := $(JSON_INC) $(ERROR_INC) $(TEST_INC) -I$(JSON_SRC) -I$(ERROR_SRC) \
	     -I$(TEST_SRC)

INC_DIRS ?= $(PROJ_INC)

# Compiler Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

CXX 	  = g++
CXXFLAGS  = -std=c++17 -Wall -Werror -pedantic -fPIC
LDFLAGS   = -shared
LINK      = -Lbin
LINK_JSON = $(LINK) -lbstdjson
LINK_TEST = $(LINK) -lbstdtest
LINK_ALL = $(LINK_JSON) $(LINK_TEST)


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
JSON_LIB  := $(BIN_DIR)/libbstdjson.so

JSON_EXAMPLE_SRCS := $(shell find $(JSON_EXAMPLES_SRC) -path "*.cpp")
JSON_EXAMPLES     := $(basename $(JSON_EXAMPLE_SRCS))
JSON_TEST_SRCS    := $(shell find $(JSON_TESTS_SRC) -path "*.cpp")
JSON_TESTS        := $(basename $(JSON_TEST_SRCS))
JSON_TEST_EXEC    := $(BIN_DIR)/$(JSON_TEST)

TEST_SRCS := $(shell find $(TEST_SRC) -path "*.cpp")
TEST_OBJS := $(TEST_SRCS:.cpp=.o)
TEST_LIB  := $(BIN_DIR)/libbstdtest.so

TEST_EXAMPLE_SRCS := $(shell find $(TEST_EXAMPLES_SRC) -path "*.cpp")
TEST_EXAMPLES     := $(basename $(TEST_EXAMPLE_SRCS))

TESTS_EXEC := $(BIN_DIR)/$(TESTS)

SRCS := $(JSON_SRCS) $(ERROR_SRCS) $(TEST_SRCS)
OBJS := $(JSON_OBJS) $(ERROR_OBJS) $(TEST_OBJS)
LIBS := $(ERROR_LIB) $(JSON_LIB) $(TEST_LIB)

# Object File Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

.cpp.o: $(SRCS)
	@echo Compiling $<...
	@$(CXX) -c $(CXXFLAGS) $(DEPS) $(INC_DIRS) $< -o $@
	@cat $(D_FILES) >> $(DEPENDENCIES)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# Executable Recipes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

all:	$(BSTD) $(EXAMPLES) $(TESTS)

# Build bstd library.
$(BSTD):	$(BSTD_LIB)
$(BSTD_LIB):    $(LIBS)
		@echo Linking $@...
		@$(CXX) $(LDFLAGS) $(LIBS) -o $@
		@rm -f $(OBJS)

# Build bstd::json library.
$(JSON):	$(JSON_LIB)
$(JSON_LIB):	$(JSON_OBJS)
		@echo Linking $@...
		@$(CXX) $(LDFLAGS) -o $@ $^

# Build bstd::error library.
$(ERROR):	$(ERROR_LIB)
$(ERROR_LIB):	$(ERROR_OBJS)
		@echo Linking $@...
		@$(CXX) $(LDFLAGS) -o $@ $^
		@rm -f $(ERROR_OBJS)

# Build bstd::test library.
$(TEST):	$(TEST_LIB)
$(TEST_LIB):	$(TEST_OBJS)
		@echo Linking $@...
		@$(CXX) $(LDFLAGS) -o $@ $^
		@rm -f $(TEST_OBJS)

# Build all examples.
$(EXAMPLES): $(JSON_EXAMPLES) $(TEST_EXAMPLES)

# Build bstd::json examples.
json_examples:	   $(JSON_EXAMPLES)
$(JSON_EXAMPLES):  $(JSON_EXAMPLE_SRCS) $(JSON_LIB)
		    @echo Compiling $<...
		    @$(CXX) $(CXXFLAGS) $(DEPS) $(LINK_JSON) $(INC_DIRS) $< -o $@
		    @cat $(D_FILES) >> $(DEPENDENCIES)

# Build bstd::test examples.
test_examples:	   $(TEST_EXAMPLES)
$(TEST_EXAMPLES):  $(TEST_EXAMPLE_SRCS) $(TEST_LIB)
		    @echo Compiling $<...
		    @$(CXX) $(CXXFLAGS) $(DEPS) $(LINK_TEST) $(INC_DIRS) $< -o $@
		    @cat $(D_FILES) >> $(DEPENDENCIES)

# Build all tests.
$(TESTS):      $(JSON_TESTS)

# Build bstd::json tests.
json_tests:	$(JSON_TESTS)
$(JSON_TESTS):	$(JSON_TEST_SRCS) $(TEST_LIB) $(JSON_LIB)
		@echo Compiling $<...
		@$(CXX) $(CXXFLAGS) $(DEPS) $(LINK_ALL) $(INC_DIRS) $< -o $@
		@cat $(D_FILES) >> $(DEPENDENCIES)



# Cleanup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# TODO: clean examples and test
.PHONY: clean
clean:
	@echo Cleaning...
	@rm -f $(shell find $(DEPENDENCY_DIR) -path "*.d")
	@rm -f $(shell find . -path "*.o")
	@rm -f $(JSON_EXAMPLES) $(TEST_EXAMPLES)
	@rm -f $(JSON_TESTS)
	@rm -f $(DEPENDENCIES)
	@rm -f $(BIN_DIR)/*

# Other Stuff ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#

# include automatically generated dependencies
-include $(DEPENDENCIES)

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
