#include "lab1.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int numWordsIn(const string& sentence) {
  int numWords = 0;
  size_t space_pos;
  for (int i = 0; i < sentence.size(); ++i) {
    size_t tmp = sentence.find(" ");
    if (sentence.find(" ") != string::npos) {
      
    }
  }

  if (sentence.size() > 0) {
    numWords++;
  }
  return numWords;
}

int main() {
  string sentence;
  cout << "Enter a sentence: ";
  cin >> sentence;
  int numWords = numWordsIn(sentence);
  cout << "Your sentence contains " << numWords << " words" << endl;
  return 0;
}
