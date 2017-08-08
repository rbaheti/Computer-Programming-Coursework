#ifndef MORSECODEDECRYPTER_H_
#define MORSECODEDECRYPTER_H_
#include <vector>
using namespace std;

class Decrypter {
public:
  virtual char Decrypt(vector<char> code) = 0;
};

class MorseCodeDecrypter : public Decrypter {
private:
  // First character in each nested vector is the ascii char corresponding to
  // the following morse code in the vector.
  vector<vector<char>> morseCodes;

public:
  MorseCodeDecrypter();
  char Decrypt(vector<char> code);
};

MorseCodeDecrypter::MorseCodeDecrypter() {
  morseCodes.push_back({ 'A', '.', '-' });
  morseCodes.push_back({ 'B', '-', '.', '.', '.' });
  morseCodes.push_back({ 'C', '-', '.', '-', '.' });
  morseCodes.push_back({ 'D', '-', '.', '.' });
  morseCodes.push_back({ 'E', '.' });
  morseCodes.push_back({ 'F', '.', '.', '-', '.' });
  morseCodes.push_back({ 'G', '-', '-', '.' });
  morseCodes.push_back({ 'H', '.', '.', '.', '.' });
  morseCodes.push_back({ 'I', '.', '.' });
  morseCodes.push_back({ 'J', '.', '-', '-', '-', });
  morseCodes.push_back({ 'K', '-', '.', '-' });
  morseCodes.push_back({ 'L', '.', '-', '.', '.' });
  morseCodes.push_back({ 'M', '-', '-' });
  morseCodes.push_back({ 'N', '-', '.' });
  morseCodes.push_back({ 'O', '-', '-','-' });
  morseCodes.push_back({ 'P', '.', '-', '-', '.' });
  morseCodes.push_back({ 'Q', '-', '-','.', '-' });
  morseCodes.push_back({ 'R', '.', '-','.' });
  morseCodes.push_back({ 'S', '.', '.','.' });
  morseCodes.push_back({ 'T', '-' });
  morseCodes.push_back({ 'U', '.', '.', '-' });
  morseCodes.push_back({ 'V', '.', '.', '.', '-' });
  morseCodes.push_back({ 'W', '.', '-', '-' });
  morseCodes.push_back({ 'X', '-', '.', '.', '-' });
  morseCodes.push_back({ 'Y', '-', '.', '-', '-' });
  morseCodes.push_back({ 'Z', '-', '-', '.', '.' });
  morseCodes.push_back({ '0', '-', '-','-','-','-' });
  morseCodes.push_back({ '1', '.', '-','-','-','-' });
  morseCodes.push_back({ '2', '.', '.','-','-','-' });
  morseCodes.push_back({ '3', '.', '.','.','-','-' });
  morseCodes.push_back({ '4', '.', '.','.','.','-' });
  morseCodes.push_back({ '5', '.', '.','.','.','.' });
  morseCodes.push_back({ '6', '-', '.','.','.','.' });
  morseCodes.push_back({ '7', '-', '-','.','.','.' });
  morseCodes.push_back({ '8', '-', '-','-','.','.' });
  morseCodes.push_back({ '9', '-', '-','-','-','.' });
  morseCodes.push_back({ '\'', '.','-', '-','-','-','.' });
  morseCodes.push_back({ '@', '.', '-', '-', '.','-','.' });
  morseCodes.push_back({ ':', '-','-', '-','.','.','.' });
  morseCodes.push_back({ ',', '-','-', '.','.','-','-' });
  morseCodes.push_back({ '$', '.', '.', '.','-','.','.','-' });
  morseCodes.push_back({ '=', '-', '.', '.','.','-' });
  morseCodes.push_back({ '!', '-', '.','-','.','-','-' });
  morseCodes.push_back({ '.', '.', '-', '.', '-','.','-' });
  morseCodes.push_back({ '?', '.', '.', '-', '-','.','.' });
  morseCodes.push_back({ '"', '.', '-','.', '.','-','.' });
}

char MorseCodeDecrypter::Decrypt(vector<char> code) {
  for (int i = 0; i < morseCodes.size(); ++i) {
    if ((morseCodes[i].size() - 1) != code.size()) continue;

    bool isEqual = true;
    for (int j = 1; j < morseCodes[i].size(); ++j) {
      if (code[j - 1] != morseCodes[i][j]) {
        isEqual = false;
        break;
      }
    }
    if (isEqual) {
      return morseCodes[i][0];
    }
  }
  return '*';
}
#endif
