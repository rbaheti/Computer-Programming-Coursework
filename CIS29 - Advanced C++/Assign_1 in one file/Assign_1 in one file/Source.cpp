#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
using namespace std;

#define INPUT_FILE "Morse.bin"

// Define base class "Decrypter"
class Decrypter {
public:
  virtual char Decrypt(vector<char> code) = 0;
};

// Define inherited class "MorseCodeDecrypter"
class MorseCodeDecrypter : public Decrypter {
private:
  // First character in each nested vector is the ascii char corresponding to
  // the following morse code in the vector.
  vector<vector<char>> morseCodes;

public:
  MorseCodeDecrypter();
  char Decrypt(vector<char> code);
};

// MorseCodeDecrypter constructor has Morse Code Table 
// which shows each character's representation in the form of '.' and '-'.
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

void enableDebug(bool bvalue)
{
  if (!bvalue) return;

  int tmpFlag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

  // Turn on leak-checking bit.
  tmpFlag |= _CRTDBG_LEAK_CHECK_DF;

  // Turn off CRT block checking bit.
  tmpFlag &= ~_CRTDBG_CHECK_CRT_DF;

  // Set flag to the new value.
  _CrtSetDbgFlag(tmpFlag);
}

// BitPattern() function converts given bit sequence 
// into '.' or '-' or ' ' or '?' and returns the converted character.
char BitPattern(const bitset<8>& byte, int second_index) {
  if (byte[second_index] == 1 && byte[second_index - 1] == 0)
    return '.';
  else if (byte[second_index] == 0 && byte[second_index - 1] == 1)
    return '-';
  else if (byte[second_index] == 1 && byte[second_index - 1] == 1)
    return ' '; // ' ' means end of word
  else
    return '?'; // '?' means end of character
}

int main() {
  enableDebug(true);

  ifstream inputFile;
  inputFile.open(INPUT_FILE, ios::binary);
  // Error message and exit from code when file doesnot open.
  if (!inputFile) {
    cout << "Error opening file " << INPUT_FILE << "\n";
    exit(1);
  }

  // vector "morse_code_charaters" will store input file data 
  // in Morse code ('.' and '-') form.
  vector<char> morse_code_charaters;
  while (!inputFile.eof()) {
    const bitset<8> byte(inputFile.get());
    for (int i = byte.size() - 1; i >= 0; i -= 2) {
      char letter = BitPattern(byte, i);
      morse_code_charaters.push_back(letter);
    }
  }

  cout << "Decoded Morse Code Characters:" << endl << endl;
  // vector "code" identifies words by seperating letters by end of character
  //  in the "morse_code_charaters" vector.
  vector<char> code;
  MorseCodeDecrypter table;
  for (int i = 0; i < morse_code_charaters.size(); ++i) {
    if (morse_code_charaters[i] == '?' || morse_code_charaters[i] == ' ') {
      // Ignore consecutive end of letter or end of word codes.
      if (!code.empty()) {
        cout << table.Decrypt(code);
      }
      if (morse_code_charaters[i] == ' ') {
        cout << " ";
      }
      code.clear();
    }
    else
      code.push_back(morse_code_charaters[i]);
  }

  cin.get();
  return 0;
}
