#include "anagrams.h"

#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

set<string> findAnagrams(const string& word, const vector<string>& dictionary) {
  // Get letter sets for every word in the dictionary
  set<string> result;

  set<char> wordLetters;
  for (char c : word) {
    wordLetters.insert(c);
  }

  for (string s : dictionary) {
    set<char> lettersInCurrentWord;
    for (char c : s) {
      lettersInCurrentWord.insert(c);
    }

    if (s.size() == word.size()) {
      if (lettersInCurrentWord == wordLetters) {
        result.insert(s);
      }
    }
  }

  return result;
}

int main() {
  // TODO student: Add manual testing code, if desired
  return 0;
}
