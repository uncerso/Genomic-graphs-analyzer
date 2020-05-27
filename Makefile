FLAGS:=-std=c++17 -pedantic-errors -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wduplicated-branches -Wduplicated-cond -Wextra-semi -Wfloat-equal -Wlogical-op -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo 
OUT_NAME:=run
FILES:=src/*.cpp

build_release:
	g++ -O3 -Werror $(FLAGS) $(FILES) -o $(OUT_NAME)
build_debug:
	g++ -g -no-pie  $(FLAGS) $(FILES) -o $(OUT_NAME)
