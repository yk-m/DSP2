PROGRAM_NAME := dsp2-3

INPUT_DIR := ./files/input
OUTPUT_DIR := ./files/output

INPUT_FILE1 := $(INPUT_DIR)/1-4-1.txt
INPUT_FILE2 := $(INPUT_DIR)/1-4-2.txt
INPUT_FILE := $(INPUT_DIR)/input.txt

SIGMA := $(INPUT_DIR)/sigma/sigma31.txt

# compiler
CXX := gcc
CXXFLAGS := -Wextra -std=c99 -g -O0
LIBS :=

# out
OUT_DIR := out

# program
PROGRAM_DIR := .
PROGRAM := $(PROGRAM_DIR)/$(PROGRAM_NAME)

# sources
SOURCE_DIR := src
SOURCES := $(wildcard $(SOURCE_DIR)/*.c)
SOURCE_NAMES = $(notdir $(SOURCES))

# headers
HEADER_DIR := include
HEADERS := $(wildcard $(HEADER_DIR)/*.h)

# objs
OBJ_DIR := $(OUT_DIR)/obj
OBJS := $(addprefix $(OBJ_DIR)/,$(SOURCE_NAMES:.c=.o))

# dependencies
DEPEND_DIR := $(OUT_DIR)/depend
DEPENDS := $(addprefix $(DEPEND_DIR)/,$(SOURCE_NAMES:.c=.depend))

.PHONY: all
all: $(DEPENDS) $(PROGRAM)
$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) $^ -o $(PROGRAM)

$(DEPEND_DIR)/%.depend: $(SOURCE_DIR)/%.c $(HEADERS)
	@echo "generating $@"
	@mkdir -p $(DEPEND_DIR)
	@$(CXX) $(CXXFLAGS) $(LIBS) -I $(HEADER_DIR) -MM $< > $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(LIBS) -I $(HEADER_DIR) -c $^ -o $@


ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPENDS)
endif

.PHONY : run
run:
	@./$(PROGRAM_NAME) $(INPUT_FILE)

.PHONY : run141
run141:
	@./$(PROGRAM_NAME) $(INPUT_FILE1)

.PHONY : run142
run142:
	@./$(PROGRAM_NAME) $(INPUT_FILE2)

.PHONY : sigma
sigma:
	@./$(PROGRAM_NAME) $(SIGMA)

.PHONY : info
info:
	@./$(PROGRAM_NAME)


.PHONY : clean
clean:
	$(RM) -r $(OUT_DIR)