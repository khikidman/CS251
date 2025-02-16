#include "include/search.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string cleanToken(const string& token) {
  string result;
  int numLetters = 0;

  int start = 0;
  while (start < token.size() && ispunct(token[start])) {
    start++;
  }
  
  int end = token.size() - 1;
  while (end > 0 && ispunct(token[end])) {
    end--;
  }

  for (char c : token) {
    if (isalpha(c)) {
      numLetters++;
    }
  }

  for (int i = start; i <= end; i++) {
    if (isalpha(token[i])) {
      result += tolower(token[i]);
    }
    else if (numLetters > 0 ) {
      result += token[i];
    }
  }

  return result;
}

set<string> gatherTokens(const string& text) {
  set<string> tokens;
  istringstream iss(text);
  string token;

  while (iss >> token) {
    string cleanedToken = cleanToken(token);
    if (!cleanedToken.empty()) {
      tokens.insert(cleanedToken);
    }
  }
  
  return tokens;
}

int buildIndex(const string& filename, map<string, set<string>>& index) {
  ifstream fin;
  fin.open(filename);

  if (!fin.is_open()) {
    cout << "Invalid filename." << endl;
  }

  cout << "Stand by while building index..." << endl;

  string url;
  string content;
  int numPages = 0;
  while (getline(fin, url)) {
    getline(fin, content);
    set<string> tokens = gatherTokens(content);
    for (string s : tokens) {
      index[s].insert(url);
    }
    numPages++;
  }
  fin.close();
  return numPages;
}

set<string> findQueryMatches(const map<string, set<string>>& index,
                             const string& sentence) {
  stringstream ss(sentence);
  string searchQueryToken;
  vector<string> searchQueryTokens;
  while (ss >> searchQueryToken) {
    searchQueryTokens.push_back(searchQueryToken);
  }
  
  set<string> result;

  for (const string& token : searchQueryTokens) {
    string cleanedToken = cleanToken(token);
    auto it = index.find(cleanedToken);
    if (it == index.end()) {
      if (token[0] == '+') {
        result = {};
      }
      continue;
    }

    set<string> temp;

    if (token[0] == '+') {
      set_intersection(result.begin(), result.end(), it->second.begin(), it->second.end(), inserter(temp, temp.begin()));
    }
    else if (token[0] == '-') {
      set_difference(result.begin(), result.end(), it->second.begin(), it->second.end(), inserter(temp, temp.begin()));
    }
    else {
      set_union(result.begin(), result.end(), it->second.begin(), it->second.end(), inserter(temp, temp.begin()));
    }
    result = temp;
  }

  return result;
}

void searchEngine(const string& filename) {

  map<string, set<string>> index;
  int pagesProcessed = buildIndex(filename, index);
  int numDistinctWordsInIndex = index.size();

  cout << "Indexed " << pagesProcessed << " pages containing " << numDistinctWordsInIndex << " unique terms" << endl;

  string userQuery;
  bool exit = false;
  while (!exit) {
    cout << "Enter query sentence (press enter to quit): ";
    getline(cin, userQuery);
    if (userQuery == "") {
      break;
    } 
    else {
      set<string> urlMatches = findQueryMatches(index, userQuery);
      cout << "Found " << urlMatches.size() << " matching pages" << endl;
      for (const string& url : urlMatches) {
        cout << url << endl;
      }
    }
  }
  cout << "Thank you for searching!" << endl;
}
