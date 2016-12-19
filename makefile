CXX := g++
CXXFLAGS := -g -Wall 
TARGET := runMinesweeper

all: $(TARGET)

$(TARGET): $(TARGET).c++
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).c++
	./$(TARGET)
clean: 
	$(RM) $(TARGET)


