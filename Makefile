CC=gcc
CFLAGS=-Wall -Wextra -Werror -ansi -pedantic -g

all:: proj1
proj1:
	$(CC) $(CFLAGS) src/*.c -o proj1
tests:: proj1
	$(MAKE) $(MFLAGS) -C tests
clean::
	rm -f proj1 a.out *.o core tests/*.diff *.zip *.*~
zip::
	zip proj1.zip src/*.c src/*.h
indent::
	indent -i8 -br -ce -l80 -npcs -nbad -brf -lp src/*.c src/*.h && rm -f *.*~

