CC=g++
FLAGS=-Iinclude -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE -D_EJC
FILES=main.o new_node.o delete_tree.o dump_tree.o search_in_tree.o definition_and_comparison.o

TARGET = okinator

# pathsub
# addprefix
# wildcard

PATCHED_FILES = $(addprefix build/, $(FILES))

all: prepare $(TARGET)
	cd ./stack && make

prepare:
	mkdir -p build

$(TARGET): $(FILES)
	@echo "Linling..."
	@$(CC) $(FLAGS) $(PATCHED_FILES) -o $(TARGET)

main.o: src/main.cpp
	@$(CC) -c $(FLAGS) src/main.cpp -o build/main.o

new_node.o: src/new_node.cpp
	@$(CC) -c $(FLAGS) src/new_node.cpp -o build/new_node.o

delete_tree.o: src/delete_tree.cpp
	@$(CC) -c $(FLAGS) src/delete_tree.cpp -o build/delete_tree.o

dump_tree.o: src/dump_tree.cpp
	@$(CC) -c $(FLAGS) src/dump_tree.cpp -o build/dump_tree.o

search_in_tree.o: src/search_in_tree.cpp
	@$(CC) -c $(FLAGS) src/search_in_tree.cpp -o build/search_in_tree.o

definition_and_comparison.o: src/definition_and_comparison.cpp
	@$(CC) -c $(FLAGS) src/definition_and_comparison.cpp -o build/definition_and_comparison.o

clean:
	rm -rf $(TARGET)
	cd build && rm -rf *.o
	cd ./stack && make clean
