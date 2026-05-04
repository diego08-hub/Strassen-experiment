CXX = g++

CXXFLAGS = -O3 -Wall -std=c++17 -march=native

SRC = main.cpp matrix_std.cpp

# Ejecutable
TARGET = experimento

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
