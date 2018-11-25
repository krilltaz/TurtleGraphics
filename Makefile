CC = gcc
CFLAGS = -Wall -pedantic -ansi -Werror -g
OBJ1 = readinput.o validators.o listoperations.o stringoperations.o draw.o effects.o conversions.o
OBJ2 = readinput.o validators.o listoperations.o stringoperations.o drawsimple.o effects.o conversions.o
OBJ3 = readinput.o validators.o listoperations.o stringoperations.o drawdebug.o effects.o conversions.o
EXEC1 = TurtleGraphics
EXEC2 = TurtleGraphicsSimple
EXEC3 = TurtleGraphicsDebug

all : $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1) : $(OBJ1)
	$(CC) $(OBJ1) -lm -o $(EXEC1)

$(EXEC2) : $(OBJ2)
	$(CC) $(OBJ1) -lm -o $(EXEC2)

$(EXEC3) : $(OBJ3)
	$(CC) $(OBJ1) -lm -o $(EXEC3)

readinput.o : readinput.c readinput.h validators.h listoperations.h linkedlist.h structset.h draw.h stringoperations.h
	$(CC) -c readinput.c $(CFLAGS)

validators.o : validators.c validators.h stringoperations.h
	$(CC) -c validators.c $(CFLAGS)

listoperations.o : listoperations.c listoperations.h linkedlist.h structset.h
	$(CC) -c listoperations.c $(CFLAGS)

stringoperations.o : stringoperations.c stringoperations.h
	$(CC) -c stringoperations.c $(CFLAGS)

draw.o : draw.c draw.h effects.h linkedlist.h structset.h stringoperations.h
	$(CC) -c draw.c $(CFLAGS)

drawsimple.o: draw.c draw.h effects.h linkedlist.h structset.h stringoperations.h
	$(CC) -c draw.c $(CFLAGS) -DSIMPLE=1

drawdebug.o : draw.c draw.h effects.h linkedlist.h structset.h stringoperations.h
	$(CC) -c draw.c $(CFLAGS) -DDEBUG=1

effects.o : effects.c effects.h
	$(CC) -c effects.c $(CFLAGS)

conversions.o : conversions.c conversions.h
	$(CC) -c conversions.c $(CFLAGS)


clean:
	rm -f $(EXEC1) $(EXEC2) $(EXEC3) $(OBJ1) $(OBJ2) $(OBJ3)

run:
	./TurtleGraphics charizard.txt

runVal:
	valgrind ./TurtleGraphics charizard.txt

runGdb:
	gdb ./TurtleGraphics
