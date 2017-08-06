#include <iostream>
#include <fstream>
#include <bitset>
#include "MorseCodeDecrypter.h"
using namespace std;

#define INPUT_FILE "Morse.bin"

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