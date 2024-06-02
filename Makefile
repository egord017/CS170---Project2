CC = g++
CFLAGS = -std=c++11

# Define the source and header directories
SRC_DIR = src
HEADER_DIR = header

# Source and header files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/algorithm.cpp
HEADERS = $(HEADER_DIR)/algorithm.h

# Object files
OBJS = main.o algorithm.o

# Executable name
EXECUTABLE = classifier

# Make rules
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)

# Pattern rule for object file compilation
%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del -f $(OBJS) $(EXECUTABLE)