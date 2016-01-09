CC = g++
YACC = /usr/local/opt/bison/bin/bison
LEX = /usr/local/opt/flex/bin/flex
CFLAGS = -g -Wall -Wno-deprecated-register -Wno-unused-function -std=c++11
DFLAGS = -DDEBUG
YACCFLAGS = -dv
LECFLAGS = -l
INCDIR = ./include
SRCDIR = src
LIBDIR = -L/usr/local/opt/flex/lib -L/usr/local/opt/bison/lib
LIBS = -lfl -ly
SRC = solver.cpp y.tab.cpp lex.yy.cpp main.cpp
OBJ = solver.o y.tab.o lex.yy.o main.o
TARGET = main 

all: $(TARGET) $(OBJ)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(DFLAGS) -o $@ $(OBJ) $(LIBDIR) $(LIBS)

y.tab.cpp: $(INCDIR)/solver.y
	$(YACC) $(YACCFLAGS) -o y.tab.cpp $(INCDIR)/solver.y

lex.yy.cpp: $(INCDIR)/solver.l
	$(LEX) $(LECFLAGS) -o lex.yy.cpp $(INCDIR)/solver.l

%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(DFLAGS) -I$(INCDIR) -c $<

%.o: $(SRCDIR_EXT)/%.cpp
	$(CC) $(CFLAGS) $(DFLAGS) -c $<

%.o: %.cpp
	$(CC) $(CFLAGS) $(DFLAGS) -I$(INCDIR) -c $<

clean:
	rm -f y.tab.* lex.yy.* y.output $(OBJ) $(TARGET)