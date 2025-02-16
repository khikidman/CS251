#include "include/map_votes.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

void processVotesMap(ifstream& file, map<string, int>& restVotes) {
  string restaurant;
  while (getline(file, restaurant)) {
    restVotes[restaurant]++;
  }
}

string findMostVotedMap(const map<string, int>& restVotes) {
  int max = 0;
  string mostVotedRestaurant;
  for (auto [key, value] : restVotes) {
    if (value > max) {
      max = value;
      mostVotedRestaurant = key;
    }
  }

  return mostVotedRestaurant;
}