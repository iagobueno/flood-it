CC = gcc -g
RM = rm -f
OBJS = main.o game.o print.o stack.o fianqueto.o
OUTPUT = main

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUTPUT)

main.o: main.c
	$(CC) -c main.c

fianqueto.o: fianqueto.c fianqueto.h
	$(CC) -c fianqueto.c

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
