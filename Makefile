CXX = g++

CXXFLAGS = -O2 -Wall -std=c++17 -march=native

SRC = main.cpp matrix_std.cpp matrix_str.cpp
TARGET = experimento

DATA_DIR = data
PLOT_DIR = plots

CSV_OUT = $(DATA_DIR)/resultados.csv
GRAPH_OUT = $(PLOT_DIR)/grafico_bc16.png

PLOT_SCRIPT = plot_script.gp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)
	gnuplot $(PLOT_SCRIPT)
	@echo "Experimento terminado."
	@echo "Resultados: $(CSV_OUT)"
	@echo "Gráfico: $(GRAPH_OUT)"

clean:
	rm -f $(TARGET)
	# rm -f $(CSV_OUT)
	# rm -f $(GRAPH_OUT)

