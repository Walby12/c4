CC = clang -v
CFLAGS = -g -O0 -Iinclude `llvm-config --cflags`
LDFLAGS = `llvm-config --libs core executionengine native` -ldl -lpthread
SRC = src/main.c src/lexer.c src/parser.c src/ast.c
OBJ = $(SRC:.c=.o)
TARGET = c4c

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

