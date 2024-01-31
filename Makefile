MAIN = star_main
FUNCTIONS = star
LLFUNCTIONS = llist_star
COMPILER = g++
COMPILERFLAGS = -c


all: $(MAIN)



$(MAIN): $(FUNCTIONS).o $(LLFUNCTIONS).o $(MAIN).o
	$(COMPILER) $(FUNCTIONS).o $(LLFUNCTIONS).o $(MAIN).o -o cpp_star

$(MAIN).o: $(MAIN).cpp
	$(COMPILER) $(COMPILERFLAGS) $(MAIN).cpp

$(FUNCTIONS).o: $(FUNCTIONS).cpp $(FUNCTIONS).h
	$(COMPILER) $(COMPILERFLAGS) $(FUNCTIONS).cpp

$(LLFUNCTIONS).o: $(LLFUNCTIONS).cpp $(LLFUNCTIONS).h star_data.h
	$(COMPILER) $(COMPILERFLAGS) $(LLFUNCTIONS).cpp



clean:
	rm -f *.o cpp_star*