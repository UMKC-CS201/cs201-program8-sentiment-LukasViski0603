// CS201PGM8Sentiment 
// NAME:  Lukas Viskovic
// 3/10/2024, CS201R 
// Done in Visual Studios 2022

#include "Sentiment.h"
using namespace std;

int main() {
    vector<wordList> sentList, posList, negList;

    // Initialize random seed for the entire application
    srand(static_cast<unsigned>(time(nullptr)));

    // Load sentiment analysis data
    loadSentiment(sentList, posList, negList);

    // List of review filenames as provided
    vector<string> reviewFiles = {
        "review1",
        "review2",
        "review3",
        "review4",
        "review5a",
        "review6",
        "review7",
        "review8",
        "reviewsPart1",
        "reviewsPart2V2"
    };

    // Prepare for processing multiple review files, indicates failure
    ofstream outFile("processed_reviews.txt");
    if (!outFile.is_open()) {
        cout << "Failed to open output file." << endl;
        return 1;
    }

    // Process each specified review file
    for (const string& filename : reviewFiles) {
        ifstream inFile(filename + ".txt");
        if (!inFile.is_open()) {
            cout << "Failed to open " << filename << ".txt" << endl;
            continue; // Skip file
        }

        processFile(inFile, outFile, filename + ".txt", sentList, posList, negList);

        inFile.close(); // CLOSE INPUT FILE
    }

    outFile.close(); // CLOSE OUTPUT FILE

    return 0; 
}

 
