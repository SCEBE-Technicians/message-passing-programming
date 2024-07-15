all:average_array print_array integrate_sin

average_array:average_array.c
	mpicc average_array.c -o average_array -O3

print_array:print_array.c
	mpicc print_array.c -o print_array -O3

integrate_sin:integrate_sin.c
	mpicc integrate_sin.c -lm -o integrate_sin -O3

clean:
	rm average_array print_array integrate_sin
