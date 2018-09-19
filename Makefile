SOURCE_DIR = src
INLCUDE_DIR = include
TEST_DIR = test
OBJ_DIR = obj

TEST_INCLUDE = -I/usr/local/include
TEST_LD_FLAGS = -L/usr/local/lib -lfl -lgtest -lpthread

TESTS := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJ := $(TESTS:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)

SOURCES := $(wildcard $(SRC_DIR)/*.c)
SOURCES += $(addprefix $(SRC_DIR)/, lex.yy.c parser.tab.c)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = etapa2

.PHONY: all test yy dir clean

all: dir $(TARGET)

$(TARGET): yy $(OBJECTS)
	gcc -Wall main.c $(OBJECTS) -lfl -o $@

test: dir yy $(OBJECTS) $(TEST_OBJ)
	g++ -o run_test $(OBJECTS) $(TEST_OBJ) $(TEST_LD_FLAGS)
	valgrind -v --leak-check=full ./run_test

yy:
	flex -o src/lex.yy.c --header-file=include/lex.yy.h scanner.l
	bison -Wall -o src/parser.tab.c --defines=include/parser.tab.h parser.y

$(OBJECTS): $(OBJ_DIR)/%.o : $(SOURCE_DIR)/%.c
	gcc -Wall -c $< -o $@

$(TEST_OBJ): $(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	g++ -Wall $(TEST_INCLUDE) -c $< -o $@

dir:
	mkdir -p obj include src

clean:
	rm -fr etapa2 run_test */lex.yy.* */parser.tab.* obj
