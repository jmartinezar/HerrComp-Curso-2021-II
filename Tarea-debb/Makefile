all: exec
deb.x: Tarea-debbug-01.cpp
	g++ -g -fsanitize=address -fsanitize=undefined -fsanitize=leak $< -o $@
exec: deb.x
	./$<
debb.x: Tarea-debbug-01.cpp
	g++ -g -Wall $< -o $@
val: debb.x
	valgrind --tool=memcheck ./$<
