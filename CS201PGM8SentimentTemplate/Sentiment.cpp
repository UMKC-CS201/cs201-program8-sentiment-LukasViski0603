#include "Sentiment.h"

//SUPPORT FUNCTION TO FIND THE CURRENT WORD IN THE SENTEMENT VECTOR & RETURN THE SENTIMENT VALUE
//PRE:   accepts a string (in) and the words list
//POST:  returns the sentiment of the word if found or the value 0 if not
double sentimentVal(string in, vector<wordList> &words) {

    cout << "CODE THIS\n";
    return 0;

}


//PRE:   accepts an empty set of 3 <wordList> vectors
//POST:  loads all three vectors with data from sentiment.txt
void loadSentiment(vector<wordList>& sentList,
    vector<wordList>& posList,
    vector<wordList>& negList) {

    //open sentiment.txt
    //add the word to the sentList vector
    //if positive enough add to posList
    //if negative enough add to negList
    //close sentiment.txt

    cout << "CODE THIS\n";
    return;
 
}

//PRE:  positive & negative word lists are sent
//POST: Open the input file & output file (infile+Output 
//      'Clean' the input by removing syntax and setting all to lower case
//       Get the sentiment value for the edited word
//        store unedited word in vector with sentiment value
//         if sentiment < -1  find a positive word to replace it
//         if sentiment > 1   find a negative word to replace

void processFile(ifstream& inFile, ofstream& outFile, string fileName,
                    vector<wordList>& words,               // vectors containing the word & sentiment
                    vector<wordList>& posList, 
                    vector<wordList>& negList) {
 
    string inWord, newWord;
    char newChar;
    vector<wordList> origWords, negWords, posWords;

    cout << "CODE THIS\n";
    outFile << "PROCESSING FILE: " << fileName << endl << endl;

    // reset all vectors & values before processing inFile
    //   read and edit the initial file
    //   remove any unnecessary characters
    while (inFile >> inWord) {
        //  the inFile read will read a word up to the next space.
        //  there may be some unwanted characters
        //  read char by char and only use alphabetic characters
        //  and change all uppercase to lowercase
        newWord = "";
        for (int i = 0, len = inWord.size(); i < len; i++) {
            if (isalpha(inWord[i])) {
                newChar = tolower(inWord[i]);
                newWord += newChar;
            }
        }
        // add the 'clean' word to a temp location & add original word & sentiment value to origWords

        //CHECK TO MAKE SENTIMENT MORE NEGATIVE
        //store current word before checking to replace
        //add original word or replacement to negVector


        //CHECK TO MAKE SENTIMENT MORE POSITIVE
        //store current word before checking to replace
        //add original word or replacement to posVector
    }
    //OUTPUT UPDATES
    //EDIT ORIGINAL WORDS VECTOR FOR OUTPUT
    //check to see if the length of the words written so far
    outFile << "FORMATTED REVIEW: " << endl;
    int lineLength = 0;
    for (unsigned int i = 0; i < origWords.size(); i++) {
        lineLength += origWords[i].word.length() + 1;
        if (lineLength > 80) {
            outFile << "\n";
            lineLength = origWords[i].word.length() + 1;
        }
        outFile << origWords[i].word + " ";
    }
 

    //EDIT MORE NEGATIVE VECTOR FOR OUTPUT
    //CHECK THAT SOMETHING HAS BEEN UPDATED BEFORE BEGINNING PRINT
    //IF THE ORIGINAL SENTMENT & NEGATIVE SENTIMENT ARE EQUAL, PRINT "REVIEW NOT UPDATED, THE SENTIMENT REMAINS: "


    //EDIT MORE POSITIVE VECTOR FOR OUTPUT
    //CHECK THAT SOMETHING HAS BEEN UPDATED BEFORE BEGINNING PRINT
    //IF THE ORIGINAL SENTMENT & NEW POSITIVE SENTIMENT ARE EQUAL, PRINT "REVIEW NOT UPDATED, THE SENTIMENT REMAINS: "
 
 
}