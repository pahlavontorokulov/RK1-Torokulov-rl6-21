all : test

test : main.o tasks_rk1.o
	g++ main.o tasks_rk1.o -o test

main.o : main.cpp
	g++ -c main.cpp

tasks_rk1.o : tasks_rk1.cpp
	g++ -c tasks_rk1.cpp

clean :
	rm -rf *.o test

