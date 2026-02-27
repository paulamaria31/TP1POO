CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++17
INCLUDE_DIRS = -I./include
SRC_DIR = src
TARGET = exe
TARGET_VAL = exeval
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Ligando os arquivos objeto para criar o executável..."
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: $(SRC_DIR)/%.cpp
	@echo "Compilando $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

run: all
	@./$(TARGET)

val: all
	@echo "Executável principal já compilado com flags de debug. Pronto para Valgrind."

valrun: all
	@echo "Executando Valgrind..."
	@valgrind --leak-check=full --track-origins=yes -s ./$(TARGET)

clean:
	@echo "Limpando arquivos compilados..."
	@rm -f $(OBJECTS) $(TARGET) $(TARGET_VAL)