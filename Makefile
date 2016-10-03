CPPUNIT_PATH=/home/Projetos/HardSoft
LIBS=-lsystemc -lm
CPPFLAGS=-I. -I$(SYSTEMC_HOME)/include
LDFLAGS=-L. -L$(LD_LIBRARY_PATH) $(LIBS)
CPPSOURCES = $(wildcard *.cpp)

all: out
out: $(CPPSOURCES:.cpp=.o)
	g++ -o $@ $^ $(LDFLAGS)
%.o: %.cpp
	g++ -c $< $(CPPFLAGS) -o $@

clean: 
	rm *.o