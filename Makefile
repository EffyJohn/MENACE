CXX = g++
CXXFLAGS = -Wall -g

main.out: main.o data.o transform.o
	${CXX} ${CXXFLAGS} -o main.out bin/main.o bin/data.o bin/transform.o

main.o: src/main.cc 
	${CXX} ${CXXFLAGS} -c src/main.cc -o bin/main.o

data.o: src/data.cc
	${CXX} ${CXXFLAGS} -c src/data.cc -o bin/data.o

transform.o: src/transform.cc
	${CXX} ${CXXFLAGS} -c src/transform.cc -o bin/transform.o



