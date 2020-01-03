all: write.c control.c
	gcc -o write write.c
	gcc -o control control.c