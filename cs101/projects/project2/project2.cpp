#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
using namespace std;

class object {
  public:
    int rows;
    int cols;
    vector<vector<string> > data;
};

void quicksort(object& data, int left, int right);
int getCols(string fileName);
int getRows(string fileName);
int findColumn(object, string name);

int main(int argc, char** argv) {
    ifstream input1;
    ifstream input2;
    ofstream output1;
 
    //open all the files for use  DON'T FORGET TO CLOSE
    input1.open(argv[1]);
    input2.open(argv[2]);
    output1.open(argv[3]);

    //create the data object
    object data;

    //size the data for use
    data.cols = getCols(argv[1]);
    data.rows = getRows(argv[1]);
    data.data.resize(data.rows);

    for(int d = 0; d < data.rows; d++) {
	data.data[d].resize(data.cols);
    }
    input1.close();
    input1.open(argv[1]);

    int x = 0;
    int y = 0;
    //process all the data from the 1st input file
    while(!input1.eof()) {
	string line;
	getline(input1, line);

	string token;
	stringstream stream(line);
	while(getline(stream, token, ',')) {
	    data.data[x][y++] = token;
	}

	//reset the col to 0 and increase to the next row/line
	y = 0;
	x++;
    }

    //close the 1st file
    input1.close();
    //some data for the 2nd set
    object sort;

    //size the data for use
    sort.cols = getCols(argv[2]);
    sort.rows = getRows(argv[2]);
    sort.data.resize(sort.rows);

    for(int e = 0; e < sort.rows; e++) {
	sort.data[e].resize(sort.cols);
    }

    input2.close();
    input2.open(argv[2]);
    x = 0;
    y = 0;
    //process all the data from the 2nd input file
    while(!input2.eof()) {
	string line;
	getline(input2, line);

	string token;
	stringstream stream(line);
	while(getline(stream, token, ',')) {
	    sort.data[x][y++] = token;
  	}

	//reset the col to 0 and increase to the next row/line
	y = 0;
	x++;
    }

    //close the 2nd file
    input2.close();
    for(int g = 1; g < data.rows-1; g++) {
	for(int h = 0; h < data.cols; h++) {
	    cout << data.data[g][h] << ",";
	}
	cout << endl;
    }
  
    //sort the data
    quicksort(data, 1, data.rows-2);

    for(int g = 1; g < data.rows-1; g++) {
	for(int h = 0; h < data.cols; h++) {
	    cout << data.data[g][h] << ",";
	}
	cout << endl;
    }
    return 0;
}

void quicksort(object& data, int left, int right) {


//find how to switch the entire row, not just the specify column



int col = 0;
    int i = left;
    int j = right;
    vector<string> tmp;
    string pivot = data.data[(left + right) / 2][col];

    while(i <= j) {
	while(data.data[i][col] < pivot) i++;
	while(data.data[j][col] > pivot) j--;
	if(i <= j) {
	    tmp = data.data[i];
	    data.data[i] = data.data[j];
	    data.data[j] = tmp;
	    i++;
	    j--;
	}
    }

    if(left < j) 
	quicksort(data, left, j);
    if(i < right)
	quicksort(data, i, right);

    return;
}

int findColumn(object data, string search) {
    for(int x = 0; x < data.cols; x++) {
	//if the word matches
	if(search.compare(data.data[0][x]) == 0) {
	    //return the location of that string 
	    return x;
	}
    }

    //if word isn't found return 0;
    return 0;
}

int getCols(string fileName) {
    int count = 0;
    
    ifstream input1;
    input1.open(fileName.c_str());

    string line;
    getline(input1, line);

    string token;
    stringstream stream(line);
    while(getline(stream, token, ',')) {
	count++;
    }

    input1.close();
    return count;	
}

int getRows(string fileName) {
    int count = 0;

    ifstream input;
    input.open(fileName.c_str());
   
    while(!input.eof()) {
  	string line;
	getline(input, line);

	count++;
    } 

    input.close();
    return count;	
}
