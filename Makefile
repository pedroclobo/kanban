CC=gcc
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -g
all:: *.c
	$(MAKE) $(MFLAGS) -C tests
proj1: proj1.c
zip:
	zip proj1.zip *.c *.h
indent:
	indent -i8 -br -ce -l80 -npcs -nbad -brf -lp *.c *.h && rm -f *.*~
clean:
	rm -f proj1 a.out *.o core tests/*.diff *.zip *.*~
compile:
	gcc *.c -o proj1
