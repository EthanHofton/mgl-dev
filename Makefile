CC = c++

#CXX flags
CXXFLAGS = -Wall -std=c++17 -stdlib=libc++

# include dirs
CXXFLAGS += -Ilib/mgl/include/

# macros
CXXFLAGS += -DMGL_PLATFORM_OSX
CXXFLAGS += -DMGL_ENABLE_ASSERTS

LDFLAGS = -Llib/mgl/bin/ -lmgl -rpath "$(shell pwd)"/lib/mgl/bin/

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
PROGRAM = out
BIN = bin

.PHONY: all clean

all: dirs libs $(PROGRAM)

run: all
	./$(BIN)/$(PROGRAM)

exe:
	./$(BIN)/$(PROGRAM)

dirs:
	mkdir -p ./$(BIN)

libs:
	cd lib/mgl && make

$(PROGRAM): $(OBJ)
	$(CC) -g -o $(BIN)/$(PROGRAM) $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -g -o $@ -c $< $(CXXFLAGS)

clean:
	rm -rf $(BIN) $(OBJ)

mglclean: clean
	cd lib/mgl && make clean