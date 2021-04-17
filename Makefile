CC=gcc
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -g
all:: src/*.c
	$(MAKE) $(MFLAGS) -C tests
zip:
	zip proj1.zip src/*.c src/*.h
indent:
	indent -i8 -br -ce -l80 -npcs -nbad -brf -lp src/*.c src/*.h && rm -f *.*~
clean:
	rm -f proj1 a.out *.o core tests/*.diff *.zip *.*~
compile:
	gcc src/*.c -o proj1
