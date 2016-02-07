#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cctype>
using namespace std;

void search(string array[10000], int count, string search_word);
int uniqueCounter(string array[10000], int amount);
string toLower(string word);

int main(int argc, char** argv) {
    ifstream infile;
    infile.open(argv[1]);
    
    if(infile.fail()) return 0;

    string array[10000];
    string word;
    int count = 0;
    int uniqueCount = 0;

    while(infile >> word) {
	//used to determine if we needed to split the word
	bool isSplit = false;

	//make sure the word doesn't need to be split
	for(int pos = 0; pos < (signed) word.length(); pos++) {
	    //if the character is valid skip
	    if(isalpha(word[pos])) {
		
	    }
	    else {
		//add the word up to the wrong character
		array[count++] = toLower(word.substr(0, pos));

		//don't count the word twice
		isSplit = true;

		//check if there are more characters to handle
		if(word[pos+1] != '\0') {
		    //now we need to create a new string	
		    string split;
		    for(int loc = pos+1; loc < (signed) word.length(); loc++) {
		   	split += word[loc];
		    }

		    //add the new word to the list
		    array[count++] = toLower(split);
		}
	    }
	}


	//if the word wasn't split just add it normally
	if(!isSplit) {
	    array[count] = toLower(word);
	    count++;
	}
    }

    //get the # of unique word
    uniqueCount = uniqueCounter(array, count);
  
    cout << "The number of words found in the file was " << count << endl;
    cout << "The number of unique words found in the file was " << uniqueCount << endl;

    //the word that will be tested for
    string searchWord = "test";

    cout << "Please enter a word to search for or '-1' to quit: ";
    cin >> searchWord;

    while(searchWord.compare("-1") != 0) {
        search(array, count, toLower(searchWord));

	cout << "Please enter a word to search for or '-1' to quit: ";
	cin >> searchWord;
    }

    //close file
    infile.close();

    return 0;
} 

void search(string array[10000], int count, string searchWord) {
    //will contain matched words
    string matched[count];
    int matchCount = 0;

    for(int x = 0; x < count; x++) {
	string word = array[x];
	bool isMatch = false;

	//Make sure the word isn't longer than the search word
	if(word.length() <= searchWord.length()) {
	    //go through all the letters of the search word
	    for(int y = 0; y < (signed) searchWord.length(); y++) {
		//check if the letters match
		if(searchWord[y] == word[y]) {
		    //we have matched the 1st letter
		    isMatch = true;		    
		}
		else if(searchWord[y] == '?') {
		    //if it's a question mark allow match of anything
		    isMatch = true;
		}
		else {
		    isMatch = false;
		    break;
		}
	    }
	}

	//start the word has having not yet matched
	bool hasMatched = false;

	//make sure the word hasn't been matched before
    	for(int pos = 0; pos < matchCount; pos++) {
	    if(word.compare(matched[pos]) == 0) {
		//the word has already matched don't print it
		hasMatched = true;
	    }
	}

   	//if the word hasn't matched yet print the # of times it occurs
	if(!hasMatched) {
	    if(isMatch) {
	    	//number of times the word matched occurs
	    	int occurences = 0;

	    	//if the word is a match count the # of times it occurs
	    	for(int z = 0; z < count; z++) {
	    	    if(word.compare(array[z]) == 0) {
	                occurences++;
	       	    }
	        }

   	        cout << "The word " << word << " appears " << occurences << " times in the document" << endl;
            }

	    //add the word to the list of matched words
	    matched[matchCount++] = word;

	}	
    }

    return;
}

int uniqueCounter(string array[10000], int amount) {
    string uniqueArray[amount];
    int counter = 0;
    bool isUnique = true;

    //go through each word
    for(int x = 0; x < amount; x++) {
	//start every word as unique
	isUnique = true;

	//check to see if the unique array contains the word
	for(int y = 0; y < amount; y++) {
	    if(array[x].compare(uniqueArray[y]) == 0) {
		isUnique = false;
	    }
	}

	//if the word is unique then add it to the unique array and increment the count
	if(isUnique) {
	    uniqueArray[counter++] = array[x];
	}
    }

    return counter;
}

//convert a string to lowercase
string toLower(string word) {
    int x;
    for(x = 0; x < (signed) word.length(); x++) {
	word[x] = tolower(word[x]);
    }

    return word;
}
