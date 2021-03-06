CC=D:\Program Files\LLVM\bin\clang.exe
CPPCHECK=D:\Program Files\Cppcheck\cppcheck.exe
CFLAGS=-Wall -Werror -Wno-pragma-pack
LDFLAGS=-lSDL2 -L.
BINARY=tetris
BINARY_TESTS=tetris_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

tetris: main.o tetris.o gfx.o
	$(CC) -o $(BINARY) $(LDFLAGS) $^

main.o: main.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

tetris.o: tetris.c tetris.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

gfx.o: gfx.c tetris.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

tests.o: tests.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

test: tests.o tetris.o
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)
