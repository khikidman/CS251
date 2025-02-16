#include "include/vector_votes.h"

#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

void processVotesVector(ifstream& file, vector<string>& votes,
                        set<string>& restaurants) {
  string restaurant;
  while (getline(file, restaurant)) {
    restaurants.insert(restaurant);
    votes.push_back(restaurant);
  }
}

string findMostVotedVector(const vector<string>& votes,
                           const set<string>& restaurants) {
  int max = 0;
  int current;
  string mostVotedRestaurant;

  for (string restaurant : restaurants) {
    current = 0;
    for (string vote : votes) {
      if (vote == restaurant) {
        current++;
      }
    }
    if (current > max) {
      max = current;
      mostVotedRestaurant = restaurant;
    }
  }
  return mostVotedRestaurant;
}
