#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

/**
 * Returns a new map that is the "reversal" of the given map `m`.
 * For example, the map `{{"key", "value"}}` would be reversed to the map
 * `{{"value", "key"}}`.
 */
map<string, set<string>> reverseMap(map<string, string> m) {
  map<string, set<string>> reverseMap;
  for (pair<string, string> p : m) {
    reverseMap[p.second].insert(p.first);
  }
  return reverseMap;
}

int main() {
  // Because you're changing the signature, we don't have tests for this
  // function. Instead, update this example to demonstrate that your function
  // works as intended!
  map<string, string> example = {
      {"apple", "fruit"},        {"banana", "fruit"},   {"carrot", "vegetable"},
      {"cucumber", "vegetable"}, {"salmon", "protein"}, {"chicken", "protein"}};

  map<string, set<string>> reversedExample = reverseMap(example);

  for (pair<string, set<string>> p : reversedExample) {
    cout << p.first << " : ";
    int i = 0;
    for (string s : p.second) {
      cout << s;
      if (i < p.second.size() - 1) {
        cout << ", ";
      }
      i++;
    }
    cout << endl;
  }

  return 0;
}
