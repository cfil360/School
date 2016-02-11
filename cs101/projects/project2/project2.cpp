//Connor Filipovic
//Feb 8, 2016
//Project 2
//CS101 Dixon

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
using namespace std;

class object {
  public:
    int rows;
    int cols;
    vector<vector<string> > data;
};

vector<vector<string>> merge_sort(object& obj, int col);
vector<string> merge(const vector<int>& left, const vector<int>& right, int col);
void generalsort(object& data, object& sort);
void reverse(object&data);
void quicksort(object& data, int left, int right, int col);
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

    //sort the data
    generalsort(data, sort);

    for(int g = 1; g < data.rows; g++) {
	for(int h = 0; h < data.cols; h++) {
	    cout << data.data[g][h] << ",";
	}
	cout << endl;
    }
    return 0;
}

void generalsort(object& data, object& sort) {
    for(int x = 0; x < sort.rows; x++) {
	//do the quicksort
cout << sort.data[x][0] << endl;
	quicksort(data, 1, data.rows-1, findColumn(data, sort.data[x][0]));

	//if its descending reverse the data
/*	if(sort.data[x][2].compare("descending") == 0) {
	    reverse(data);
	}
  */  }
}

void reverse(object& data) {
    for(int x = 0; x < data.rows; x++) {
	vector<string> temp = data.data[x];
	data.data[x] = data.data[(data.rows-1) - x];
	data.data[(data.rows-1) - x] = temp;
    }
    
    return;
}	

void quicksort(object& data, int left, int right, int col) {
//find how to switch the entire row, not just the specify column
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
	quicksort(data, left, j, col);
    if(i < right)
	quicksort(data, i, right, col);

    return;
}

vector<string> merge_sort(vector<vector<string> >& obj, int col)  {  
    // Termination condition: List is completely sorted if it  
    // only contains a single element.  
    if(obj.data.size() == 1)  
    {  
        return obj.data[0];  
    }  
  
    // Determine the location of the middle element in the vector  
    vector<string>::iterator middle = obj.begin() + (obj.size() / 2);  
  
    vector<vector<string> > left(obj.begin(), middle);  
    vector<vector<string> > right(middle, obj.end());  
  
    // Perform a merge sort on the two smaller vectors  
    left = merge_sort(left, col);  
    right = merge_sort(right, col);  
  
    return merge(left, right, col);  
} 

vector<string> merge(const vector<string>& left, const vector<string>& right, int col)  {  
    // Fill the resultant vector with sorted results from both vectors  
    vector<string> result;  
    unsigned left_it = 0, right_it = 0;  
  
    while(left_it < left.size() && right_it < right.size())  
    {  
        // If the left value is smaller than the right it goes next  
        // into the resultant vector  
        if(left[left_it][col] <= right[right_it][col])  
        {  
            result.push_back(left[left_it]);  
            left_it++;  
        }  
        else  
        {  
            result.push_back(right[right_it]);  
            right_it++;  
        }  
    }  
  
    // Push the remaining data from both vectors onto the resultant  
    while(left_it < left.size())  
    {  
        result.push_back(left[left_it]);  
        left_it++;  
    }  
  
    while(right_it < right.size())  
    {  
        result.push_back(right[right_it]);  
        right_it++;  
    }  
  
    return result;  
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
    
    ifstream input;
    input.open(fileName.c_str());

    string line;
    getline(input, line);

    string token;
    stringstream stream(line);

    while(getline(stream, token, ',')) {
	count++;
    }

    input.close();
    return count;	
}

int getRows(string fileName) {
    int count = 0;

    string line;
    ifstream input;
    input.open(fileName.c_str());
  
    while(getline(input, line)) { 
	count++;
    } 

    input.close();
    return count;	
}
