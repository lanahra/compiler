TEST_DIR = test/
TEST_INCLUDE = -I/usr/local/include
TEST_LD_FLAGS = -L/usr/local/lib -lfl -lgtest -lpthread

TEST_OBJ = $(addprefix $(TEST_DIR), main.o scanner.o)

all: lex.yy.o
	gcc -Wall main.c lex.yy.o -lfl -o etapa1

test: lex.yy.o $(TEST_OBJ)
	g++ -o run_test lex.yy.o $(TEST_OBJ) $(TEST_LD_FLAGS)
	./run_test

lex.yy.o:
	flex --header-file=lex.yy.h scanner.l
	gcc -c lex.yy.c

$(TEST_DIR)%.o: $(TEST_DIR)%.cpp
	g++ -c -Wall $(TEST_INCLUDE) -o $@ $<

clean:
	rm -f main run_test lex.yy.* test/*.o
