#include "billboard.h"

#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

map<string, size_t> buildCounts(const vector<string>& artists) {
  // The returned map should answer the question:
  //     How many weeks has this artist had a number
  //     one song in the Billboard top 100?
  map<string, size_t> counts;
  for (string artist : artists) {
    counts[artist]++;
  }

  return counts;
}

map<char, set<string>> buildLetterIndex(const vector<string>& artists) {
  // The returned map should answer the question:
  //     What are the artists who have had a #1 song in the
  //     Billboard top 100, whose name start with the given
  //     character?
  map<char, set<string>> letterIndex;
  for (string artist : artists) {
    letterIndex[artist[0]].insert(artist);
  }

  return letterIndex;
}

int main() {
  // string filename = "billboard.txt";
  string filename = "billboardSmall.txt";
  vector<string> artists;

  parseBillboardFile(filename, artists);

  cout << "<<<Number of weeks with a #1 song>>>" << endl;
  auto counts = buildCounts(artists);
  for (auto entry : counts) {
    cout << entry.first << " : " << entry.second << endl;
  }

  cout << endl;

  cout << "<<<Index of all artists with a #1 song>>>" << endl;
  auto letterIndex = buildLetterIndex(artists);
  for (auto entry : letterIndex) {
    cout << entry.first << ":" << endl;
    for (string artist : entry.second) {
      cout << "\t" << artist << endl;
    }
  }
}
