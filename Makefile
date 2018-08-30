TEST_DIR = test/
TEST_INCLUDE = -I/usr/local/include
TEST_LD_FLAGS = -L/usr/local/lib -lfl -lgtest -lpthread

TEST_OBJ = $(addprefix $(TEST_DIR), main.o scanner.o parser.o)

all: yy
	gcc -Wall main.c lex.yy.o parser.tab.o -lfl -o etapa2

test: yy $(TEST_OBJ)
	g++ -o run_test lex.yy.o parser.tab.o $(TEST_OBJ) $(TEST_LD_FLAGS)
	./run_test

yy:
	flex --header-file=lex.yy.h scanner.l
	bison -Wall -d parser.y
	gcc -c lex.yy.c
	gcc -c parser.tab.c

parser.tab.o:
	gcc -c parser.tab.c

$(TEST_DIR)%.o: $(TEST_DIR)%.cpp
	g++ -c -Wall $(TEST_INCLUDE) -o $@ $<

clean:
	rm -f etapa2 run_test lex.yy.* test/*.o parser.tab.*
