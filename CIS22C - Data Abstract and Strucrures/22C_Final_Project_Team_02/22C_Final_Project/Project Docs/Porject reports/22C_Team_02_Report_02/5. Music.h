#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <string>
using namespace std;

class Music {
public:
  // Constructor
  Music();

  // Parameterized Constructor
  Music(string songName, string artistName, string genre, int yearReleased, string recordLabel) {
    this->songName = songName;
    this->artistName = artistName;
    this->genre = genre;
    this->yearReleased = yearReleased;
    this->recordLabel = recordLabel;
  }

  // Destructor
  ~Music();

  // Mutators
  void SetSongName(string songName) { this->songName = songName; }
  void SetArtistName(string artistName) { this->artistName = artistName; }
  void SetGenre(string genre) { this->genre = genre; }
  void SetYearReleased(int yearReleased) { this->yearReleased = yearReleased; }
  void SetRecordLabel(string recordLabel) { this->recordLabel = recordLabel; }

  // Accessors
  string GetSongName() { return songName; }
  string GetArtistName() { return artistName; }
  string GetGenre() { return genre; }
  int GetYearReleased() { return yearReleased; }
  string GetRecordLabel() { return recordLabel; }

private:
  // Member variables
  string songName;
  string artistName;
  string genre;
  int yearReleased;
  string recordLabel;

  // Overloading operators ==, >, < and =
  bool operator==(const Music& rhs);
  bool operator<(const Music& rhs);
  bool operator>(const Music& rhs);
  const Music operator=(const Music& rhs);
};
#endif
