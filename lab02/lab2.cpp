#include "lab2.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int numWordsIn(const string& sentence) {
  int numWords = 0;
  string tmp;
  stringstream ssin(sentence);
  while (ssin >> tmp) {
    numWords++;
  }
  return numWords;
}

int main() {
  string sentence;
  getline(cin, sentence);
  int numWords = numWordsIn(sentence);
  cout << "Your sentence contains " << numWords << " words" << endl;
  return 0;
}
