CC = gcc -g
RM = rm -f
OBJS = main.o game.o print.o stack.o ai.o
OUTPUT = main

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUTPUT)

main.o: main.c
	$(CC) -c main.c

ai.o: ai.c ai.h
	$(CC) -c ai.c

print.o: print.c print.h game.h
	$(CC) -c print.c

game.o: game.c game.h
	$(CC) -c game.c

stack.o: stack.c stack.h
	$(CC) -c stack.c

clean:
	@$(RM) $(OBJS)

purge: clean
	@$(RM) $(OUTPUT)

run:
	@./main

v:
	@valgrind ./main
gdb:
	@gdb ./main