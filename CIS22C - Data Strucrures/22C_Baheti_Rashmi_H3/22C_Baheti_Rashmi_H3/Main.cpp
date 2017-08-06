#define _CRT_SECURE_NO_WARNINGS // needed to avoid warnings
#include "Queue.h"
#include "Stack.h"
#include <string>
#include <fstream>
#include <cctype> // for isalnum()
#include <iostream>
using namespace std;

#define INPUT_FILE "test_word_plndrms.txt"
#define OUTPUT_FILE "word_plndrms.txt"

//Fuction prototypes:
string toUpperCase(string input);
void LoadStackAndQueue(string str, Stack<string> *stack, Queue<string> *queue);
bool IsPallindrome(Stack<string> *stack, Queue<string> *queue);

int main() {
  ifstream inputFile;
  // open the input file
  inputFile.open(INPUT_FILE);
  if (!inputFile) {
    cout << "Error opening file \"" << INPUT_FILE << "\"\n";
    cin.get();
    exit(1);
  }

  //Read each line of text from the input file
  string sentence;
  ofstream outFile(OUTPUT_FILE);

  while (!inputFile.eof()) {
    getline(inputFile, sentence);
    Stack<string> stack;
    Queue<string> queue;
    LoadStackAndQueue(sentence, &stack, &queue);
    if (IsPallindrome(&stack, &queue)) {
      cout << "1 " << sentence << endl;
      outFile << sentence << endl;
    }
    else {
      cout << "\t0 " << sentence << endl;
    }
  }

  // Close the files.
  inputFile.close();
  outFile.close();

  cin.get();
  return 0;
}

/******************************************************
// toUpperCase converts the given string to upper case.
********************************************************/
string toUpperCase(string input) {
  char* charInput = new char[input.size() + 1];
  strcpy(charInput, input.c_str());

  char* orig_charInput = charInput;

  while (*charInput != '\0') {
    *charInput = toupper(*charInput);
    charInput++;
  }

  // Create anonymous string object and assign it to input
  // using string class constructor : string (const char* s);
  input = string(orig_charInput);
  delete[] orig_charInput;
  return input;
}

/********************************************************************
// LoadStackAndQueue function extracts a word from the given sentence
// and pushes it to the stack and enqueues in the queue.
*********************************************************************/
void LoadStackAndQueue(string str, Stack<string> *stack, Queue<string> *queue) {
  int start_index = -1;
  // Append an extra space at the end of the string to easily 
  // extract the last word
  str += " ";

  // Extract the word from a sentence and push it in 
  // the stack and enqueue it in the queue
  for (int i = 0; i < str.size(); ++i) {
    if (isalnum(str.at(i))) {
      if (start_index == -1) {
        start_index = i;
      }
    }
    if (!isalnum(str.at(i))) {
      if (start_index != -1) {
        string word(str.c_str() + start_index, i - start_index);
        queue->enqueue(toUpperCase(word));
        stack->push(toUpperCase(word));
        start_index = -1;
      }
    }
  }
}

/******************************************************
// IsPallindrome function will return true if 
// the given string is pallindrome otherwise false.
*******************************************************/
bool IsPallindrome(Stack<string> *stack, Queue<string> *queue) {
  string stack_word, queue_word;
  while (!stack->isEmpty()) {
    stack->pop(stack_word);
    queue->dequeue(queue_word);
    if (stack_word != queue_word) {
      return false;
    }
  }
  return true;
}

/********************************************************************************
Sample output of the program is:

1 Did I say you never say "never say never"? You say I did.
  0 Did I say you never say "never"?
  0 Are you glad you are king?
1 King, are you glad you are king?
1 Fall leaves after leaves fall.
1 Says Mom, "What do you do?" - You do what Mom says.
  0 Says Mom, "What do you do?" - You do what Mom does.
1 You know, I did little for you, for little did I know you.
  0 You know, I did little for you, since little did I know you.
  0 First Ladies rule the State.
  0 Escher, drawing hands, drew hands drawing.
  0 You can cage a swallow, can't you?
1 First Ladies rule the State, and state the rule: "ladies first".
  0 Blessed are they that believe they are blessed.
1 You can cage a swallow, cannot you, but you cannot swallow a cage, can you?
1 Mind your own business: Own your mind.
1 Rode, and rode, and rode, and rode, and rode, and rode, and rode!
1 Clatter and hum and crunch, and crunch and hum and clatter.
  0 Mind your own business.
1 All for one, and one for all!
1 Escher, drawing hands, drew hands drawing Escher.

********************************************************************************/