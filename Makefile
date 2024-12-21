# Makefile

# Переменные
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o operations.o
EXEC = sed_simplified

# Правило сборки исполняемого файла
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Правило для компиляции main.c
main.o: main.c operations.h
	$(CC) $(CFLAGS) -c main.c

# Правило для компиляции operations.c
operations.o: operations.c operations.h
	$(CC) $(CFLAGS) -c operations.c

# Фиктивная цель для очистки
clean:
	rm -f $(OBJ) $(EXEC)

# Фиктивная цель для тестирования
.PHONY: test

test: $(EXEC)
	./$(EXEC) test.txt -r "old" "new"
	./$(EXEC) test.txt -d "delete_me"
	./$(EXEC) test.txt -i -f "front_"
	./$(EXEC) test.txt -i -b "_back"

