PROGRAM_NAME := dsp2-2

BMPFILE := ./files/original/samp.bmp

DCT_1D_IN := ./files/input/1d.txt
DCT_1D_OUT := ./files/output/1d.txt
DCT_2D_IN := ./files/input/2d.txt
DCT_2D_OUT := ./files/output/2d.txt
IDCT_1D_OUT := ./files/input/1d_idct.txt
IDCT_2D_OUT := ./files/input/2d_idct.txt

OUTFILE := ./files/output/out

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

.PHONY : run0
run0:
	@./$(PROGRAM_NAME) 0 $(DCT_1D_IN) $(DCT_1D_OUT)

.PHONY : run1
run1:
	@./$(PROGRAM_NAME) 1 $(DCT_1D_OUT) $(IDCT_1D_OUT)

.PHONY : run2
run2:
	@./$(PROGRAM_NAME) 2 $(DCT_2D_IN) $(DCT_2D_OUT)

.PHONY : run3
run3:
	@./$(PROGRAM_NAME) 3 $(DCT_2D_OUT) $(IDCT_2D_OUT)

.PHONY : run4
run4:
	@./$(PROGRAM_NAME) 4 $(BMPFILE) $(OUTFILE)

.PHONY : run5
run5:
	@./$(PROGRAM_NAME) 5 $(BMPFILE) $(OUTFILE)

.PHONY : info
info:
	@./$(PROGRAM_NAME)


.PHONY : clean
clean:
	$(RM) -r $(OUT_DIR)