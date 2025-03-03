#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "include/caesar_dec.h"
#include "include/caesar_enc.h"
#include "include/subst_dec.h"
#include "include/subst_enc.h"
#include "utils.h"

using namespace std;

// Initialize random number generator in .cpp file for ODR reasons
std::mt19937 Random::rng;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// Function declarations go at the top of the file so we can call them
// anywhere in our program, such as in main or in other functions.
// Most other function declarations are in the included header
// files.

// When you add a new helper function, make sure to declare it up here!

/**
 * Print instructions for using the program.
 */
void printMenu();

void decryptSubstFileCommand(const QuadgramScorer& scorer);

int main() {
  Random::seed(time(NULL));
  string command;

  cout << "Welcome to Ciphers!" << endl;
  cout << "-------------------" << endl;
  cout << endl;

  ifstream fin("dictionary.txt");
  vector<string> dictionary;
  string word;
  while (fin >> word) {
    dictionary.push_back(word);
  }

  vector<string> quadgrams;
  vector<int> counts;
  ifstream file("english_quadgrams.txt");
  string line;
  while (getline(file, line)) {
    int end = line.find(',');
    quadgrams.push_back(line.substr(0, end));
    counts.push_back(stoi(line.substr(end + 1, line.size() - end)));
  }

  QuadgramScorer scorer(quadgrams, counts);

  do {
    printMenu();
    cout << endl << "Enter a command (case does not matter): ";

    // Use getline for all user input to avoid needing to handle
    // input buffer issues relating to using both >> and getline
    getline(cin, command);
    cout << endl;

    if (command == "R" || command == "r") {
      string seed_str;
      cout << "Enter a non-negative integer to seed the random number "
              "generator: ";
      getline(cin, seed_str);
      Random::seed(stoi(seed_str));
    }

    if (command == "C" || command == "c") {
      caesarEncryptCommand();
    }

    if (command == "D" || command == "d") {
      caesarDecryptCommand(dictionary);
    }

    if (command == "A" || command == "a") {
      applyRandSubstCipherCommand();
    }

    if (command == "E" || command == "e") {
      computeEnglishnessCommand(scorer);
    }

    if (command == "S" || command == "s") {
      decryptSubstCipherCommand(scorer);
    }

    if (command == "F" || command == "f") {
      decryptSubstFileCommand(scorer);
    }

    cout << endl;

  } while (!(command == "x" || command == "X") && !cin.eof());

  return 0;
}

void printMenu() {
  cout << "Ciphers Menu" << endl;
  cout << "------------" << endl;
  cout << "C - Encrypt with Caesar Cipher" << endl;
  cout << "D - Decrypt Caesar Cipher" << endl;
  cout << "E - Compute English-ness Score" << endl;
  cout << "A - Apply Random Substitution Cipher" << endl;
  cout << "S - Decrypt Substitution Cipher from Console" << endl;
  cout << "F - Decrypt Substitution Cipher from File" << endl;
  cout << "R - Set Random Seed for Testing" << endl;
  cout << "X - Exit Program" << endl;
}

// "#pragma region" and "#pragma endregion" group related functions in this file
// to tell VSCode that these are "foldable". You might have noticed the little
// down arrow next to functions or loops, and that you can click it to collapse
// those bodies. This lets us do the same thing for arbitrary chunks!
#pragma region CaesarEnc

char rot(char c, int amount) {
  size_t alphaPos = ALPHABET.find(c);
  size_t newAlphaPos = (alphaPos + amount) % 26;
  return ALPHABET[newAlphaPos];
}

string rot(const string& line, int amount) {
  string res = "";
  for (char c : line) {
    if (isalpha(c)) {
      res += rot(toupper(c), amount % 26);
    } else if (isspace(c)) {
      res += c;
    }
  }
  return res;
}

void caesarEncryptCommand() {
  string originalString;
  string rotateAmountString;
  int rotateAmount;
  cout << "Enter a string to caesar encrypt: ";
  getline(cin, originalString);
  cout << "Enter the amount to rotate your string by: ";
  getline(cin, rotateAmountString);
  rotateAmount = stoi(rotateAmountString);

  string encryptedString = rot(originalString, rotateAmount);
  cout << encryptedString;
}

#pragma endregion CaesarEnc

#pragma region CaesarDec

void rot(vector<string>& strings, int amount) {
  for (string& s : strings) {
    for (char& c : s) {
      if (isalpha(c)) {
        c = ALPHABET[(ALPHABET.find(c) + amount) % 26];
      }
    }
  }
}

string clean(const string& s) {
  string cleanedString = "";
  for (char c : s) {
    if (isalpha(c)) {
      cleanedString += toupper(c);
    }
  }
  return cleanedString;
}

vector<string> splitBySpaces(const string& s) {
  vector<string> words;
  int start = 0;

  while (start < s.size()) {
    size_t spaceIndex = s.find(' ', start);
    if (spaceIndex == string::npos) {
      words.push_back(s.substr(start));
      break;
    }
    if (s[start] != ' ') {
      words.push_back(s.substr(start, spaceIndex - start));
    }
    start = spaceIndex + 1;
  }

  return words;
}

string joinWithSpaces(const vector<string>& words) {
  string result = "";
  for (int i = 0; i < words.size(); i++) {
    result += words.at(i);
    if (i < words.size() - 1) {
      result += " ";
    }
  }
  return result;
}

int numWordsIn(const vector<string>& words, const vector<string>& dict) {
  int numWords = 0;
  for (string word : words) {
    bool found = false;
    for (string dictWord : dict) {
      if (word == dictWord) {
        found = true;
      }
    }
    if (found) {
      numWords++;
    }
  }
  return numWords;
}

void caesarDecryptCommand(const vector<string>& dict) {
  string line;
  cout << "Enter an encrypted text you want to decipher: ";
  getline(cin, line);

  vector<string> words = splitBySpaces(line);
  for (string& s : words) {
    s = clean(s);
  }

  vector<string> validDecryptions;

  for (int i = 0; i < 26; i++) {
    vector<string> rotatedWords = words;
    rot(rotatedWords, i);

    int numWords = numWordsIn(rotatedWords, dict);

    if (numWords > rotatedWords.size() / 2) {
      validDecryptions.push_back(joinWithSpaces(rotatedWords));
    }
  }

  if (validDecryptions.empty()) {
    cout << "No good decryptions found" << endl;
  }

  for (string decryption : validDecryptions) {
    cout << decryption << endl;
  }
}

#pragma endregion CaesarDec

#pragma region SubstEnc

string applySubstCipher(const vector<char>& cipher, const string& s) {
  string encryptedText;
  for (char c : s) {
    if (isalpha(c)) {
      encryptedText += cipher[toupper(c) % 65];
    } else {
      encryptedText += c;
    }
  }
  return encryptedText;
}

void applyRandSubstCipherCommand() {
  string line;
  cout << "Enter the tet you want to apply the random substitution cipher to: ";
  getline(cin, line);

  vector<char> cipher = genRandomSubstCipher();

  string encryptedLine = applySubstCipher(cipher, line);
  cout << "Encrypted text: " << endl;
  cout << encryptedLine << endl;
}

#pragma endregion SubstEnc

#pragma region SubstDec

double scoreString(const QuadgramScorer& scorer, const string& s) {
  double score = 0.0;
  int quadgramSize = 4;
  for (int i = 0; i <= s.size() - quadgramSize; ++i) {
    score += scorer.getScore(s.substr(i, quadgramSize));
  }
  return score;
}

void computeEnglishnessCommand(const QuadgramScorer& scorer) {
  string line, s;
  cout << "Enter a string to compute its Englishness: ";
  getline(cin, line);
  vector<string> words = splitBySpaces(line);
  for (string w : words) {
    w = clean(w);
    s += w;
  }
  double score = scoreString(scorer, s);
  cout << "Englishness: " << score << endl;
}

vector<char> decryptSubstCipher(const QuadgramScorer& scorer,
                                const string& ciphertext) {
  vector<char> key = genRandomSubstCipher();
  vector<char> bestKey = key;
  int trials = 0;
  double highestScore = scoreString(scorer, ciphertext);
  while (trials < 1000) {
    int letter1 = Random::randInt(25);
    int letter2 = Random::randInt(25);
    while (letter2 == letter1) {
      letter2 = Random::randInt(25);
    }

    swap(key[letter1], key[letter2]);

    double currentScore =
        scoreString(scorer, applySubstCipher(key, ciphertext));

    if (currentScore > highestScore) {
      bestKey = key;
      highestScore = currentScore;
      trials = 0;
    } else {
      swap(key[letter1], key[letter2]);
    }

    trials++;
  }
  cout << applySubstCipher(bestKey, ciphertext) << endl;

  return bestKey;
}

void decryptSubstCipherCommand(const QuadgramScorer& scorer) {
  string line;
  cout << "Enter an encrypted text to decipher: ";
  getline(cin, line);
  string cleanedLine;
  vector<string> words = splitBySpaces(line);

  for (string w : words) {
    cleanedLine += clean(w);
  }

  vector<char> bestKey;
  double highestScore = scoreString(
      scorer, applySubstCipher(genRandomSubstCipher(), cleanedLine));
  for (int i = 0; i < 25; ++i) {
    vector<char> currentKey = decryptSubstCipher(scorer, cleanedLine);
    double currentScore =
        scoreString(scorer, applySubstCipher(currentKey, cleanedLine));
    if (currentScore > highestScore) {
      highestScore = currentScore;
      bestKey = currentKey;
    }
  }

  cout << "Best decryption found: " << applySubstCipher(bestKey, line);
}

void decryptSubstFileCommand(const QuadgramScorer& scorer) {
  string inputFileName;
  string outputFileName;
  string line;
  string cleanText;
  vector<string> fileLines;

  cout << "Enter the name of an encrypted file to decipher: ";
  getline(cin, inputFileName);
  cout << "Enter the name of the output file: ";
  getline(cin, outputFileName);

  ifstream fin(inputFileName);

  while (getline(fin, line)) {
    fileLines.push_back(line);
    vector<string> words = splitBySpaces(line);
    for (string w : words) {
      cleanText += clean(w);
    }
  }
  fin.close();

  vector<char> bestKey;
  double highestScore =
      scoreString(scorer, applySubstCipher(genRandomSubstCipher(), cleanText));
  for (int i = 0; i < 25; ++i) {
    vector<char> currentKey = decryptSubstCipher(scorer, cleanText);
    double currentScore =
        scoreString(scorer, applySubstCipher(currentKey, cleanText));
    if (currentScore > highestScore) {
      highestScore = currentScore;
      bestKey = currentKey;
    }
  }

  ofstream fout(outputFileName);

  for (string originalLine : fileLines) {
    fout << applySubstCipher(bestKey, originalLine) << endl;
  }

  fout.close();
  cout << "Decrypted text written to " << outputFileName << endl;
}

#pragma endregion SubstDec
