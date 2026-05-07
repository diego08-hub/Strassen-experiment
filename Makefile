CXX = g++

CXXFLAGS = -O3 -Wall -std=c++17 -march=native

SRC = main.cpp matrix_std.cpp matrix_str.cpp
TARGET = experimento
CSV_OUT = resultados.csv
PLOT_SCRIPT = plot_script.gp
GRAPH_OUT = grafico_n0.png

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Ejecuta el experimento y luego genera el gráfico automáticamente
run: $(TARGET)
	./$(TARGET)
	gnuplot $(PLOT_SCRIPT)
	@echo "Experimento terminado. Revisa $(CSV_OUT) y $(GRAPH_OUT)"

clean:
	rm -f $(TARGET) $(CSV_OUT) $(GRAPH_OUT)

