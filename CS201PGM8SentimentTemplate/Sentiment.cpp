#include "Sentiment.h"


//SUPPORT FUNCTION TO FIND THE CURRENT WORD IN THE SENTEMENT VECTOR & RETURN THE SENTIMENT VALUE
//PRE:   accepts a string (in) and the words list
//POST:  returns the sentiment of the word if found or the value 0 if not
// Assuming wordList is already sorted by word
double sentimentVal(const string& in, const vector<wordList>& words) {
    auto it = lower_bound(words.begin(), words.end(), in, [](const wordList& wl, const string& val) {
        return wl.word < val;
        });

    if (it != words.end() && it->word == in) {
        return it->value;
    }
    return 0; // Word not found
}


//PRE:   accepts an empty set of 3 <wordList> vectors
//POST:  loads all three vectors with data from sentiment.txt
void loadSentiment(vector<wordList>& sentList, vector<wordList>& posList, vector<wordList>& negList) {
    ifstream inFile("sentiment.txt");

    if (!inFile.is_open()) {
        cout << "Unable to open file\n";
        return;
    }

    string inRecord;
    while (getline(inFile, inRecord)) { 
        int pos = inRecord.find(",");
        wordList tempWord;
        tempWord.word = inRecord.substr(0, pos);
        tempWord.value = stod(inRecord.substr(pos + 1));

        // Add the word to the sentList vector
        sentList.push_back(tempWord);

        // If positive enough add to posList
        if (tempWord.value > 1.25) {
            posList.push_back(tempWord);
        }
        // If negative enough add to negList
        else if (tempWord.value < -1.25) {
            negList.push_back(tempWord);
        }
    }

    inFile.close(); // Ensures file is closed

    // sorts the sentiment list alphabetically 
    sort(sentList.begin(), sentList.end(), [](const wordList& a, const wordList& b) {
        return a.word < b.word;
        });
}

// Helper function to find a random replacement word with opposite sentiment
string findReplacement(double sentiment, const vector<wordList>& replacementList) {
    vector<string> candidates;
    for (const auto& word : replacementList) {
        if ((sentiment < 0 && word.value > 1.25) || (sentiment > 0 && word.value < -1.25)) {
            candidates.push_back(word.word);
        }
    }
    if (!candidates.empty()) {
        size_t index = static_cast<size_t>(rand()) % candidates.size();
        return candidates[index];
    }
    return ""; 
}

double calculateTotalSentiment(const vector<wordList>& words) {
    double totalSentiment = 0.0;
    for (const auto& word : words) {
        totalSentiment += word.value;
    }
    return totalSentiment;
}

//PRE:  positive & negative word lists are sent
//POST: Open the input file & output file (infile+Output 
//      'Clean' the input by removing syntax and setting all to lower case
//       Get the sentiment value for the edited word
//        store unedited word in vector with sentiment value
//         if sentiment < -1  find a positive word to replace it
//         if sentiment > 1   find a negative word to replace

void processFile(ifstream& inFile, ofstream& outFile, const string& fileName,
    vector<wordList>& words, vector<wordList>& posList, vector<wordList>& negList) {

    string inWord, originalWord, formattedReview = "", updatedReview = "";
    vector<wordList> origWords, modifiedWords;
    vector<replaceList> replacements;
    double totalSentiment = 0.0, updatedSentiment = 0.0;
    int lineLength = 0;

    outFile << "PROCESSING FILE: " << fileName << endl << "FORMATTED REVIEW: \n";

    string line, word;
    while (getline(inFile, line)) {
        stringstream ss(line);
        while (ss >> word) {
            originalWord = word; // Preserve the original word with case and punctuation
            string cleanedWord = ""; // Cleaned word for sentiment analysis and replacement
            for (char c : word) {
                if (isalpha(static_cast<unsigned char>(c))) {
                    cleanedWord += tolower(static_cast<unsigned char>(c));
                }
            }

            double wordSentiment = sentimentVal(cleanedWord, words);
            totalSentiment += wordSentiment;

            string replacementWord = findReplacement(wordSentiment, wordSentiment < -1 ? posList : negList);
            double newSentiment = replacementWord.empty() ? wordSentiment : sentimentVal(replacementWord, words);

            if (!replacementWord.empty()) {
                replacements.push_back({ cleanedWord, wordSentiment, replacementWord, newSentiment });
                modifiedWords.push_back({ replacementWord, newSentiment });
            }
            else {
                modifiedWords.push_back({ cleanedWord, wordSentiment });
            }

            // formatted original review with right case and punctuation, tkaen from chatgpt   
            if (lineLength + originalWord.length() + 1 > 80) {
                outFile << formattedReview << "\n";
                formattedReview = "";
                lineLength = 0;
            }
            formattedReview += (formattedReview.empty() ? "" : " ") + originalWord;
            lineLength += originalWord.length() + 1;

            // Prepare updated review text (to be processed after replacements)
            updatedReview += (updatedReview.empty() ? "" : " ") + (replacementWord.empty() ? originalWord : replacementWord);
            updatedSentiment += newSentiment;
        }
    }

    // Output the last line of the formatted review i not empty 
    if (!formattedReview.empty()) {
        outFile << formattedReview << "\n\n";
    }

    outFile << "ORIGINAL SENTIMENT: " << fixed << setprecision(2) << totalSentiment << "\n";

    // Output modifications for more negative and more positive sentiment adjustments
    // After calculating and outputting original sentiment 
    if (!replacements.empty()) {
        outFile << "\nWORDS UPDATED TO BE MORE POSITIVE OR NEGATIVE:\n";
        outFile << left << setw(15) << "Original" << setw(10) << "Sentiment" << setw(15) << "Replacement" << setw(10) << "Sentiment\n";
        outFile << "---------------------------------------------------------------\n";
        for (const auto& r : replacements) {
            outFile << left << setw(15) << r.origWord << setw(10) << setprecision(2) << r.origValue
                << setw(15) << r.newWord << setw(10) << setprecision(2) << r.newValue << "\n";
        }
        outFile << "\nTOTALS: " << fixed << setprecision(2) << totalSentiment << " " << updatedSentiment << "\n\n";
    }
    else {
        outFile << "\nREVIEW NOT UPDATED. THE SENTIMENT REMAINS: " << fixed << setprecision(2) << totalSentiment << "\n\n";
    }

    // Updated review below 
    outFile << "\nUPDATED REVIEW (MORE NEGATIVE/POSITIVE):\n";
    stringstream updatedSS(updatedReview);
    string updatedLine = "";
    lineLength = 0; 
    while (updatedSS >> word) {
        if (lineLength + word.length() >= 80) {
            outFile << updatedLine << "\n";
            updatedLine = "";
            lineLength = 0;
        }
        updatedLine += (updatedLine.empty() ? "" : " ") + word;
        lineLength += word.length() + 1;
    }
    // Output  last line of updated review if not empty
    if (!updatedLine.empty()) {
        outFile << updatedLine << "\n";
    }

    outFile << "\nUPDATED SENTIMENT: " << fixed << setprecision(2) << updatedSentiment << "\n\n";
}





