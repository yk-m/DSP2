PROGRAM_NAME := dsp2-4

INPUT_DIR := ./files/input
OUTPUT_DIR := ./files/output

INPUT_FILE := $(INPUT_DIR)/3_1.txt
INPUT_FILE_EX := $(INPUT_DIR)/ex.txt

DWT_DATA := $(INPUT_DIR)/3_1.txt
DWT_OUTPUT := $(OUTPUT_DIR)/3_1.txt

APPROXIMATE_OUTPUT := $(OUTPUT_DIR)/app.txt
ERROR_OUTPUT := $(OUTPUT_DIR)/error.txt

RECOVERED_DWT_DATA := $(OUTPUT_DIR)/recovered.txt

NOISE_INPUT := $(INPUT_DIR)/noise.txt
NOISE_REMOVED_DWT := $(OUTPUT_DIR)/noise_dwt.txt
NOISE_REMOVED_DFT := $(OUTPUT_DIR)/noise_dft.txt

SIN_OUTPUT := $(OUTPUT_DIR)/sin.txt
SQUARE_OUTPUT := $(OUTPUT_DIR)/square.txt

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

.PHONY : run00
run00:
	@./$(PROGRAM_NAME) 0 0 $(DWT_DATA) $(DWT_OUTPUT)

.PHONY : run01
run01:
	@./$(PROGRAM_NAME) 0 1 $(DWT_DATA) $(APPROXIMATE_OUTPUT)

.PHONY : run02
run02:
	@./$(PROGRAM_NAME) 0 2 $(DWT_DATA) $(ERROR_OUTPUT)

.PHONY : run1
run1:
	@./$(PROGRAM_NAME) 1 $(DWT_OUTPUT) $(RECOVERED_DWT_DATA)

.PHONY : run2
run2:
	@./$(PROGRAM_NAME) 2 $(NOISE_INPUT) $(NOISE_REMOVED_DWT)

.PHONY : run3
run3:
	@./$(PROGRAM_NAME) 3 $(NOISE_INPUT) $(NOISE_REMOVED_DFT)

.PHONY : run4
run4:
	@./$(PROGRAM_NAME) 4 $(SIN_OUTPUT)

.PHONY : run5
run5:
	@./$(PROGRAM_NAME) 5 $(SQUARE_OUTPUT)

.PHONY : info
info:
	@./$(PROGRAM_NAME)


.PHONY : clean
clean:
	$(RM) -r $(OUT_DIR)