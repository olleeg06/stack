all : my_stack.o stack_function.o
	g++ my_stack.o stack_function.o -o result

my_stack.o : my_stack.cpp
	g++ -c my_stack.cpp

stack_function.o : stack_function.cpp stack_function.h
	g++ -c stack_function.cpp

clean:
	del my_stack.o stack_function.o result.exe