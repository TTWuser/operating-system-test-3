disksys:main.o function.o
	gcc -o disksys main.o function.o
main.o:main.c main.h
	gcc -c main.c
function.o:function.c main.h
	gcc -c function.c