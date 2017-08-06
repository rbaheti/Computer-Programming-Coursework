#include <iostream>
#include <string>
using namespace std;

int CountWords(string str) {
  int start_index = -1;
  int wordCount = 0;
  str += " ";
  for (int i = 0; i < str.size(); ++i) {
    if (str.at(i) != ' ') {
      if (start_index == -1) {
        start_index = i;
      }
    }
    if (str.at(i) == ' ') {
      if (start_index != -1) {
        cout << "Start index is: " << start_index << endl;
        cout << "End index is: " << i - 1 << endl;
        string word(str.c_str() + start_index, i - start_index);
        // (str.c_str() + start_index) =>  gives the address of the value of the character at start_index.
        cout << "word is: " << word << endl;
        start_index = -1;
        wordCount++;
      }
    }
  }
  return wordCount;
}

/* Using Stack and Queue
bool CountWords(string str) {
  int start_index = -1;
  int wordCount = 0;
  // Eliminate the special cases for i < str.size() 
  // by adding 1 extra char " " to the string.
  str += " ";
  Stack<string> stack;
  Queue<string> queue;
  for (int i = 0; i < str.size(); ++i) {
    if (isalnum(str.at(i))) {
      if (start_index == -1) {
        start_index = i;
      }
    }
    if (!isalnum(str.at(i))) {
      if (start_index != -1) {
        cout << "Start index is: " << start_index << endl;
        cout << "End index is: " << i - 1 << endl;
        string word(str.c_str() + start_index, i - start_index);
        queue.enqueue(toUpperCase(word));
        stack.push(toUpperCase(word));
        // (str.c_str() + start_index) =>  gives the address of the value of the character at start_index.
        cout << "word is: " << word << endl;
        start_index = -1;
        wordCount++;
      }
    }
  }
  string stack_word, queue_word;
  while (!stack.isEmpty()) {
    stack.pop(stack_word);
    queue.dequeue(queue_word);
    if (stack_word != queue_word) {
      return false;
    }
  }
  return true;
}
*/

int main() {
  string sentence = " Hello, you there?";
  cout << "Number of words in the sentence is: " << CountWords(sentence) << endl;

  cin.get();
  return 0;
}