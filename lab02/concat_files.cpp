#include "concat_files.h"

#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string> readlines(const string& fname) {
  vector<string> lines;
  ifstream fin(fname);
  string line;
  while (getline(fin, line)) {
    lines.push_back(line);
  }
  return lines;
}

void concatFiles(const string& in_fname, const string& out_fname) {
  ifstream infile(in_fname);
  ofstream outfile(out_fname);
  string currFileName;
  while (getline(infile, currFileName)) {
    vector<string> fileStrs = readlines(currFileName);
    for (string s : fileStrs) {
      outfile << s << endl;
    }
  }
}

int main() {
  // TODO (optional) student: add manual testing code, if desired
  return 0;
}
