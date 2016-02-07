#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

void sort(string (&data)[50000][100], string name, string direction, string type);

int main(int argc, char** argv) {
    ifstream input1;
    ifstream input2;
    ofstream output1;
 
    //open all the files for use  DON'T FORGET TO CLOSE
    input1.open(argv[1]);
    input2.open(argv[2]);
    output1.open(argv[3]);

    //some data for the array
    int rows = 0;
    int cols = 0;
    string data[50000][100];

    //process all the data from the 1st input file
    while(!input1.eof()) {
	string line;
	getline(input1, line);

	string token;
	stringstream stream(line);
	while(getline(stream, token, ',')) {
	    data[rows][cols++] = token;
	}

	//reset the col to 0 and increase to the next row/line
	cols = 0;
	rows++;
    }
    
    //close the 1st file
    input1.close();

    //some data for the 2nd array
    int rows2 = 0;
    int cols2 = 0;
    string sortData[50000][100];

    //process all the data from the 2nd input file
    while(!input2.eof()) {
	string line;
	getline(input2, line);

	string token;
	stringstream stream(line);
	while(getline(stream, token, ',')) {
	    data[rows2][cols2++] = token;
  	}

	//reset the col to 0 and increase to the next row/line
	cols2 = 0;
	rows2++;
    }

    //close the 2nd file
    input2.close();

    //go through all the sort data info and sort the data
    for(int x = 0; x < rows2; x++) {
 	string name = sortData[x][0];
	string direction = sortData[x][1];
	string type = sortData[x][2];

	//sort the data
	sort(data, name, direction, type);
    }

    return 0;
}

void sort(string (&data)[50000][100], string name, string direction, string type) {

    return;
}

int findColumn(string data[50000][100], string search, int cols) {
    for(int x = 0; x < cols; x++) {
	//if the word matches
	if(search.compare(data[0][x]) == 0) {
	    //return the location of that string 
	    return x;
	}
    }

    //if word isn't found return 0;
    return 0;
}
