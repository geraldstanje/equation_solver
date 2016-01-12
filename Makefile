BUILD := main
CXX = g++
YACC = bison
LEX = flex
CXXFLAGS = -g -Wall -Wno-deprecated-register -Wno-unused-function -std=c++11
YACCFLAGS = -dv
LECFLAGS = -l
INCDIR = ./include
SRCDIR = src
LIBDIR = -L/usr/local/opt/flex/lib -L/usr/local/opt/bison/lib
LIBS = -lfl -ly
OBJ = solver.o y.tab.o lex.yy.o main.o
OBJ_TEST = solver.o y.tab.o lex.yy.o main_test.o

all: $(BUILD)

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LIBDIR) $(LIBS)

main_test: $(OBJ_TEST)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ_TEST) $(LIBDIR) $(LIBS)

y.tab.cpp: $(INCDIR)/solver.y
	$(YACC) $(YACCFLAGS) -o y.tab.cpp $(INCDIR)/solver.y

lex.yy.cpp: $(INCDIR)/solver.l
	$(LEX) $(LECFLAGS) -o lex.yy.cpp $(INCDIR)/solver.l

%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $<

clean:
	rm -f y.tab.* lex.yy.* y.output $(OBJ) $(OBJ_TEST) main main_test