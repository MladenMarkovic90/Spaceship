P = main
PROGRAM = Spaceship
CC = g++
CXXFLAGS = -Wall -ansi -std=c++0x
LDLIBS = -lglut -lGLU -lGL -lm


$(PROGRAM):
	$(CC) -c $(P).c $(CXXFLAGS)
	$(CC) -o $(PROGRAM) $(P).o $(LDLIBS)

force:	
	rm -f $(P).o $(PROGRAM)
	$(CC) -c $(P).c $(CXXFLAGS)
	$(CC) -o $(PROGRAM) $(P).o $(LDLIBS)

.PHONY: clean

clean:
	-rm *.o $(PROGRAM)
