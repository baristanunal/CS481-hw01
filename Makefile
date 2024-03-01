CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC = string_matching.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = sm

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJ)
