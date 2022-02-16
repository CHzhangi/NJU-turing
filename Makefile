turing : parser.o simulator.o main.o
	g++ parser.o simulator.o main.o -o turing

simulator.o : simulator.cpp  parser.h common.h
	g++ -c simulator.cpp

parser.o : parser.cpp parser.h common.h
	g++ -c parser.cpp

main.o : main.cpp parser.h  common.h
	g++ -c main.cpp

clean : 
	rm parser.o simulator.o main.o

update:
	sudo rm turing
	make turing