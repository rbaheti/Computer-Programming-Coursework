#include <iostream>
#include <fstream>
#include "Music.h"
#include "HashTable.h"
#include "BinarySearchTree.h"
using namespace std;

#define INPUT_FILE "MusicInputFile.txt"
#define OUTPUT_FILE "MusicOutputFile.txt"

void loadDataStrucures(HashTable<Music>* hashTable, BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree, const char *filename);
void FindValueByPrimaryKey(HashTable<Music>* hashTable);
void FindValueBySecondaryKey(BinarySearchTree<Music>* secondryKeyTree);
void DeleteValue(HashTable<Music>* hashTable, BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree);
void RequestAction(HashTable<Music>* hashTable, BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree);
void PrintDepthFirstTraversal(BinarySearchTree<Music>* primaryKeyTree, 
  BinarySearchTree<Music>* secondaryKeyTree);
void AddNewMusic(HashTable<Music>* hashTable, BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree);
void PrintIndented(BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree);
void PrintBreadthFirstTraversals(BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree);
void PrintSortedAndUnsortedList(HashTable<Music>* hashTable, BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree);
void SaveListToFile(HashTable<Music>* hashTable);

void displayPrimaryIndented(Music *music) {
  cout << ". " << music->GetSongName() << endl;
}

void displaySecondaryIndented(Music *music) {
  cout << ". " << music->GetArtistName() << endl;
}

void displayMusicInfo(Music *music) {
  cout << music->GetSongName() << "; ";
  cout << music->GetArtistName() << "; ";
  cout << music->GetGenre() << "; ";
  cout << music->GetYearReleased() << "; ";
  cout << music->GetRecordLabel() << endl;
}

void displaySingleMusicInfo(Music *music) {
  cout << "Song Name: " << music->GetSongName() << endl;
  cout << "Artist Name: " << music->GetArtistName() << endl;
  cout << "Genre:" << music->GetGenre() << endl;
  cout << "Year Released:" << music->GetYearReleased() << endl;
  cout << "Record Label:" << music->GetRecordLabel() << endl;
}

int ComparePrimaryKey(Music *music1, Music *music2) {
  if (music1->GetSongName() > music2->GetSongName())
    return 1;
  else if (music1->GetSongName() < music2->GetSongName())
    return -1;
  else
    return 0;
}

int CompareSecondaryKey(Music *music1, Music *music2) {
  if (music1->GetArtistName() > music2->GetArtistName())
    return 1;
  else if (music1->GetArtistName() < music2->GetArtistName())
    return -1;
  else
    return 0;
}

string TrimSpaces(string name) {
  // trim trailing spaces
  int endpos = name.find_last_not_of(" ");
  if (string::npos != endpos)
  {
    name = name.substr(0, endpos + 1);
  }

  // trim leading spaces
  int startpos = name.find_first_not_of(" ");
  if (string::npos != startpos)
  {
    name = name.substr(startpos);
  }
  return name;
}

int main() {
  HashTable<Music> hashTable(71);
  BinarySearchTree<Music> primaryKeyTree(ComparePrimaryKey);
  BinarySearchTree<Music> secondaryKeyTree(CompareSecondaryKey);

  loadDataStrucures(&hashTable, &primaryKeyTree, &secondaryKeyTree, INPUT_FILE);
  RequestAction(&hashTable, &primaryKeyTree, &secondaryKeyTree);

  // Save data to the OUTPUT_FILE
  SaveListToFile(&hashTable);

  cin.get();
  return 0;
}

void RequestAction(HashTable<Music>* hashTable, BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree) {
  cout << "************* MUSIC DATABASE MENU *************" << endl << endl;
  cout << "I : Print Indented Trees" << endl;
  cout << "B : Print binary tree Breadth-First Traversals" << endl;
  cout << "D : Print binary tree Depth-First Traversals" << endl;
  cout << "R : Print Sorted/Unsorted list" << endl;
  cout << "T : Print Hash Table Statistics" << endl;
  cout << "P : Search by primary key (Song Name)" << endl;
  cout << "S : Search by secondary key (Artist Name)" << endl;
  cout << "A : Add new song to the file" << endl;
  cout << "E : Erase/Delete a song from the file" << endl;
  cout << "V : Save Music to the file" << endl;
  cout << "H : Help - to show the menu" << endl;
  cout << "Q : Quit" << endl;
  cout << "************************************************" << endl << endl;
  string choice = "T";

  while (choice != "Q" && choice != "q") {
    cout << "Please enter a letter to perform one of the Menu operations OR enter 'H' to see the Menu: ";
    getline(cin, choice);
    cout << endl;
    if (choice == "T" || choice == "t" || choice == "B" || choice == "b" || choice == "D" || choice == "d" ||
      choice == "R" || choice == "r" || choice == "P" || choice == "p" || choice == "S" || choice == "s" ||
      choice == "A" || choice == "a" || choice == "E" || choice == "e" || choice == "I" || choice == "i" || 
      choice == "H" || choice == "h" || choice == "V" || choice == "v" || choice == "Q" || choice == "q" ||
      choice == "team")
    {
      if (choice == "I" || choice == "i") {
        PrintIndented(primaryKeyTree, secondaryKeyTree);
        cout << endl;
      }
      else if (choice == "P" || choice == "p") {
        FindValueByPrimaryKey(hashTable);
        cout << endl;
      }
      else if (choice == "B" || choice == "b") {
        PrintBreadthFirstTraversals(primaryKeyTree, secondaryKeyTree);
        cout << endl;
      }
      else if (choice == "D" || choice == "d") {
        PrintDepthFirstTraversal(primaryKeyTree, secondaryKeyTree);
      }
      else if (choice == "R" || choice == "r") {
        PrintSortedAndUnsortedList(hashTable, primaryKeyTree, secondaryKeyTree);
      }
      else if (choice == "T" || choice == "t") {
        hashTable->PrintStats();
        cout << endl;
      }
      else if (choice == "S" || choice == "s") {
        FindValueBySecondaryKey(secondaryKeyTree);
        cout << endl;
      }
      else if (choice == "A" || choice == "a") {
        AddNewMusic(hashTable, primaryKeyTree, secondaryKeyTree);
        cout << endl;
      }
      else if (choice == "E" || choice == "e") {
        DeleteValue(hashTable, primaryKeyTree, secondaryKeyTree);
        cout << endl;
      }
      else if (choice == "V" || choice == "v") {
        SaveListToFile(hashTable);
        cout << "Your file has been saved." << endl;
        cout << endl;
      }
      else if (choice == "team") {
        cout << "Developers: Team Number 02" << endl;
        cout << "Team Members: Rashmi Baheti, Aditi Cherian and Jennifer Suiter" << endl << endl;
      }
      else if (choice == "H" || choice == "h") {
        cout << "************* MUSIC DATABASE MENU *************" << endl << endl;
        cout << "I : Print Indented Trees" << endl;
        cout << "B : Print binary tree Breadth-First Traversals" << endl;
        cout << "D : Print binary tree Depth-First Traversals" << endl;
        cout << "R : Print Sorted/Unsorted list" << endl;
        cout << "T : Print Hash Table Statistics" << endl;
        cout << "P : Search by primary key (Song Name)" << endl;
        cout << "S : Search by secondary key (Artist Name)" << endl;
        cout << "A : Add new song to the file" << endl;
        cout << "E : Erase/Delete a song from the file" << endl;
        cout << "V : Save Music to the file" << endl;
        cout << "H : Help - to show the menu" << endl;
        cout << "Q : Quit" << endl;
        cout << "************************************************" << endl << endl;
      }
    }
    else {
      cout << "Please enter either I, B, D, R, T, P, S, A, E, V, H or Q" << endl;
    }
  }
  cout << "\nExiting now.. Good Bye!";
}

void loadDataStrucures(HashTable<Music>* hashTable, BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree, const char *filename) {
  ifstream inputDataFile;
  inputDataFile.open(filename);
  if (!inputDataFile) {
    cout << "File open failure!" << endl << endl;
    exit(1);
  }
  //Read each line of text into its own student object, then insert it into the Hash Table
  while (!inputDataFile.eof()) {
    Music *music = new Music();

    //getline discards the delimiter ';' while preserving the space
    string songName;
    getline(inputDataFile, songName, ';');
    songName = TrimSpaces(songName);
    music->SetSongName(songName);

    string artistName;
    getline(inputDataFile, artistName, ';');
    artistName = TrimSpaces(artistName);
    music->SetArtistName(artistName);

    string genre;
    getline(inputDataFile, genre, ';');
    genre = TrimSpaces(genre);
    music->SetGenre(genre);

    string yearReleased;
    getline(inputDataFile, yearReleased, ';');
    yearReleased = TrimSpaces(yearReleased);
    music->SetYearReleased(yearReleased);

    string recordLabel;
    getline(inputDataFile, recordLabel, '\n');
    recordLabel = TrimSpaces(recordLabel);
    music->SetRecordLabel(recordLabel);

    //Populating Hash Table
    hashTable->Insert(music->GetSongName(), music);

    //Populating primary tree
    primaryKeyTree->insert(music);

    //Populating primary tree
    secondaryKeyTree->insert(music);
  }
  inputDataFile.close();
}

void PrintDepthFirstTraversal(BinarySearchTree<Music>* primaryKeyTree, 
  BinarySearchTree<Music>* secondaryKeyTree) {
  cout << "Print Depth-First Traversals:" << endl << endl;
  cout << "1. In-Order Traversal of Song Name (Primary key) based binary tree" << endl;
  cout << "2. Pre-Order Traversal of Song Name (Primary key) based binary tree" << endl;
  cout << "3. Post-Order Traversal of Song Name (Primary key) based binary tree" << endl;
  cout << "4. In-Order Traversal of Artist Name (Secondary key) based binary tree" << endl;
  cout << "5. Pre-Order Traversal of Artist Name (Secondary key) based binary tree" << endl;
  cout << "6. Post-Order Traversal of Artist Name (Secondary key) based binary tree" << endl;
  cout << "7. Go to the previous menu" << endl << endl;
  string choice = "1";
  while (choice != "7") {
    cout << "Please enter your choice of Traversal: ";
    getline(cin, choice);
    cout << endl;
    if (choice == "1" || choice == "2" || choice == "3" || choice == "4" ||
      choice == "5" || choice == "6" || choice == "7") {
      if (choice == "1") {
        cout << "In-Order Traversal using Song Name based binary tree:" << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "SONG NAME; ARTIST NAME; GENRE; YEAR RELEASED; RECORD LABLE" << endl;
        cout << "------------------------------------------------------------" << endl;
        primaryKeyTree->inOrder(displayMusicInfo);
        cout << endl;
      }
      else if (choice == "2") {
        cout << "Pre-Order Traversal using Song Name based binary tree: " << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "SONG NAME; ARTIST NAME; GENRE; YEAR RELEASED; RECORD LABLE" << endl;
        cout << "------------------------------------------------------------" << endl;
        primaryKeyTree->preOrder(displayMusicInfo);
        cout << endl;
      }
      else if (choice == "3") {
        cout << "Post-Order Traversal using Song Name based binary tree: " << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "SONG NAME; ARTIST NAME; GENRE; YEAR RELEASED; RECORD LABLE" << endl;
        cout << "------------------------------------------------------------" << endl;
        primaryKeyTree->postOrder(displayMusicInfo);
        cout << endl;
      }
      else if (choice == "4") {
        cout << "In-Order Traversal using Song Name based binary tree:" << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "SONG NAME; ARTIST NAME; GENRE; YEAR RELEASED; RECORD LABLE" << endl;
        cout << "------------------------------------------------------------" << endl;
        secondaryKeyTree->inOrder(displayMusicInfo);
        cout << endl;
      }
      else if (choice == "5") {
        cout << "Pre-Order Traversal using Song Name based binary tree: " << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "SONG NAME; ARTIST NAME; GENRE; YEAR RELEASED; RECORD LABLE" << endl;
        cout << "------------------------------------------------------------" << endl;
        secondaryKeyTree->preOrder(displayMusicInfo);
        cout << endl;
      }
      else if (choice == "6") {
        cout << "Post-Order Traversal using Song Name based binary tree: " << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "SONG NAME; ARTIST NAME; GENRE; YEAR RELEASED; RECORD LABLE" << endl;
        cout << "------------------------------------------------------------" << endl;
        secondaryKeyTree->postOrder(displayMusicInfo);
        cout << endl;
      }
    }
    else {
      cout << "Please enter number 1, 2, 3, 4, 5, 6 or 7" << endl << endl;
    }
  }
  cout << "Going to the previous menu.." << endl << endl;
}

void FindValueByPrimaryKey(HashTable<Music>* hashTable) {
  cout << "Please enter song name you want to search: ";
  string songName;
  getline(cin, songName);
  cout << endl;
  Music* foundMusic = hashTable->Find(songName);
  if (foundMusic) {
    cout << "This song is available!" << endl;
    displaySingleMusicInfo(foundMusic);
  }
  else {
    cout << "This song is not available." << endl;
  }
}

void FindValueBySecondaryKey(BinarySearchTree<Music>* secondaryKeyTree) {
  cout << "Please enter Artist name you want to search: ";
  string input;
  getline(cin, input);
  cout << endl;
  Music searchMusic;
  searchMusic.SetArtistName(input);
  //Music* foundMusic = secondaryKeyTree->getEntry(inputId);
  vector<Music*> vec;
  bool isFound = secondaryKeyTree->getEntry(&searchMusic, &vec);
  if (isFound) {
    cout << "Artist " << input << " is available!" << endl;
    cout << "Here are the song listings by " << input << ": " << endl << endl;
    for (int i = 0; i < vec.size(); ++i) {
      displaySingleMusicInfo(vec[i]);
      cout << endl;
    }
  }
  else {
    cout << "Artist " << input << " is not available." << endl;
  }
}

void DeleteValue(HashTable<Music>* hashTable, BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree) {
  cout << "Please enter song name you want to delete: ";
  string songName;
  getline(cin, songName);
  Music music;
  music.SetSongName(songName);

  // Delete from Primary Key Tree
  bool ifPrimaryDeleted = primaryKeyTree->remove(&music);
  if (ifPrimaryDeleted) {
    // Delete from Hash Table
    Music* deleteFromHashTable = hashTable->Erase(songName);
    if (deleteFromHashTable) {
      bool ifSecondaryDeleted = secondaryKeyTree->remove(&music);
      if (ifSecondaryDeleted) {
        cout << "Your song has been deleted." << endl;
      }
    }
  }
  else {
    cout << "Your song is not in the list." << endl;
  }
}

void AddNewMusic(HashTable<Music>* hashTable, BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree) {
  Music *newMusic = new Music();
  string input;

  cout << "Please enter the details of new Song: " << endl << endl;
  cout << "Song Name: ";
  getline(cin, input);
  newMusic->SetSongName(input);
  Music* searchMusic = hashTable->Find(input);
  if (searchMusic) {
    if (searchMusic->GetSongName() == input) {
      cout << "This song already exists. Please enter new song in the list." << endl;
      return;
    }
  }

  cout << "Artist Name: ";
  getline(cin, input);
  newMusic->SetArtistName(input);

  cout << "Genre: ";
  getline(cin, input);
  newMusic->SetGenre(input);

  cout << "Year Released: ";
  getline(cin, input);
  if (input.size() != 4 || isdigit(input.at(0)) == 0 || isdigit(input.at(1)) == 0 ||
    isdigit(input.at(2)) == 0 || isdigit(input.at(3)) == 0) {
    cout << "Invalid input. Year may only contain 4 digits." << endl << endl;
    return;
  }
  newMusic->SetYearReleased(input);

  cout << "Record Label: ";
  getline(cin, input);
  newMusic->SetRecordLabel(input);

  //Inserting new object in Hash Table
  hashTable->Insert(newMusic->GetSongName(), newMusic);

  //Inserting new object in Primary Tree
  primaryKeyTree->insert(newMusic);

  //Inserting new object in Secondary Tree
  secondaryKeyTree->insert(newMusic);

  cout << "\nYour song has been added to the list." << endl << endl;
}

void PrintIndented(BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree) {
  string choice = "1";
  while (choice != "3") {
    cout << "Print Indented Tree:" << endl << endl;
    cout << "1. Using Song Name (Primary Key) based binary tree" << endl;
    cout << "2. Using Artist Name (Secondary Key) based binary tree" << endl;
    cout << "3. Go to the Main menu" << endl;
    getline(cin, choice);
    cout << endl;
    if (choice == "1" || choice == "2" || choice == "3") {
      if (choice == "1") {
        cout << "Indented Tree using Song Name based binary tree: " << endl << endl;
        primaryKeyTree->printIndented(displayPrimaryIndented);
        cout << endl;
      }
      else if (choice == "2") {
        cout << "Indented Tree using Artist Name based binary tree: " << endl << endl;
        secondaryKeyTree->printIndented(displaySecondaryIndented);
        cout << endl;
      }
    }
    else cout << "Please enter 1, 2 or 3" << endl << endl;
  }
  cout << "Going to the Main menu.." << endl << endl;
}

void PrintBreadthFirstTraversals(BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree) {
  string choice = "1";
  while (choice != "3") {
    cout << "Print Breadth-First Traversal:" << endl << endl;
    cout << "1. Using Song Name (Primary Key) based binary tree" << endl;
    cout << "2. Using Artist Name (Secondary Key) based binary tree" << endl;
    cout << "3. Go to the Main menu" << endl;
    getline(cin, choice);
    cout << endl;
    if (choice == "1" || choice == "2" || choice == "3") {
      if (choice == "1") {
        cout << "Breadth-First Traversal using Song Name based binary tree: " << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "SONG NAME; ARTIST NAME; GENRE; YEAR RELEASED; RECORD LABLE" << endl;
        cout << "------------------------------------------------------------" << endl;
        primaryKeyTree->breadthFisrtTraversal(displayMusicInfo);
        cout << endl;
      }
      else if (choice == "2") {
        cout << "Breadth-First Traversal using Artist Name based binary tree: " << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "SONG NAME; ARTIST NAME; GENRE; YEAR RELEASED; RECORD LABLE" << endl;
        cout << "------------------------------------------------------------" << endl;
        secondaryKeyTree->breadthFisrtTraversal(displayMusicInfo);
        cout << endl;
      }
    }
    else cout << "Please enter 1, 2 or 3" << endl << endl;
  }
  cout << "Going to the Main menu.." << endl << endl;
}

void PrintSortedAndUnsortedList(HashTable<Music>* hashTable, BinarySearchTree<Music>* primaryKeyTree,
  BinarySearchTree<Music>* secondaryKeyTree) {
  string choice = "1";
  while (choice != "4") {
    cout << "Print Sorted/Unsorted list of songs:" << endl << endl;
    cout << "1. Unsorted list using hash table" << endl;
    cout << "2. Sorted list using Song Name (Primary Key) based binary tree" << endl;
    cout << "3. Sorted list using Artist Name (Secondary Key) based binary tree" << endl;
    cout << "4. Go to the Main menu" << endl;
    getline(cin, choice);
    cout << endl;
    if (choice == "1" || choice == "2" || choice == "3" || choice == "4") {
      if (choice == "1") {
        cout << "Unsorted list using hash table: " << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "SONG NAME; ARTIST NAME; GENRE; YEAR RELEASED; RECORD LABLE" << endl;
        cout << "------------------------------------------------------------" << endl;
        hashTable->PrintHashTable(displayMusicInfo);
        cout << endl;
      }
      else if (choice == "2") {
        cout << "Sorted list using Song Name based binary tree: " << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "SONG NAME; ARTIST NAME; GENRE; YEAR RELEASED; RECORD LABLE" << endl;
        cout << "------------------------------------------------------------" << endl;
        primaryKeyTree->inOrder(displayMusicInfo);
        cout << endl;
      }
      else if (choice == "3") {
        cout << "Sorted list using Artist Name based binary tree: " << endl << endl;
        cout << "------------------------------------------------------------" << endl;
        cout << "SONG NAME; ARTIST NAME; GENRE; YEAR RELEASED; RECORD LABLE" << endl;
        cout << "------------------------------------------------------------" << endl;
        secondaryKeyTree->inOrder(displayMusicInfo);
        cout << endl;
      }
    }
    else cout << "Please enter 1, 2, 3 or 4" << endl << endl;
  }
  cout << "Going to the Main menu.." << endl << endl;
}

void SaveListToFile(HashTable<Music>* hashTable) {
  ofstream musicOutFile;
  musicOutFile.open(OUTPUT_FILE);
  if (!musicOutFile) {
    cout << "File open failure!" << endl << endl;
    return;
  }
  vector<Music*> music_vec;
  hashTable->InsertValuesIntoVector(&music_vec);
  for (int i = 0; i < music_vec.size(); ++i) {
    // Write details of ith book to file.
    Music* music = music_vec[i];
    musicOutFile << music->GetSongName() << "; ";
    musicOutFile << music->GetArtistName() << "; ";
    musicOutFile << music->GetGenre() << "; ";
    musicOutFile << music->GetYearReleased() << "; ";
    musicOutFile << music->GetRecordLabel();

    // Dont print an end of line character after the last line in the file
    if (i < music_vec.size() - 1) {
      musicOutFile << endl;
    }
  }
  musicOutFile.close();
}