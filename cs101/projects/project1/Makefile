search: search.o
	g++ -Wall -o search search.o

search.o:  search.cpp
	g++ -Wall -c search.cpp


clean:	
	rm -f *.o search

test:	search
	./search sample.txt
