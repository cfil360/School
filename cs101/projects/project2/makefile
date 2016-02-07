project2: project2.o
	g++ -Wall -o project2 project2.o

project2.o:    project2.cpp
	g++ -Wall -c project2.cpp

clean:
	\rm -f *.o project2

test:
	./project2 input1.csv input2.csv output1.csv 
