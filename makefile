OBJ = main.o help_function.o swapper.o rotors.o enigmas.o

EXE = enigma
CXX = g++
CXXFLAGS = -Wall -g -MMD -std=c++11	


$(EXE): $(OBJ) 
	$(CXX) $(OBJ) -o $@

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(OBJ:.o=.d)


.PHONY: clean

clean:
	rm -f $(OBJ) $(EXE) $(OBJ:.o=.d)
