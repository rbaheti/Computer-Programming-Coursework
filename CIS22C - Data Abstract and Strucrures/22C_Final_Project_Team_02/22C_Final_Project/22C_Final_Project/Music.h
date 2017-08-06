#ifndef _MUSIC_H_
#define _MUSIC_H_

#include <string>
using namespace std;

class Music {
public:
  // Constructor
  Music() { }

  // Parameterized Constructor
  Music(string songName, string artistName, string genre, string yearReleased, string recordLabel) {
    this->songName = songName;
    this->artistName = artistName;
    this->genre = genre;
    this->yearReleased = yearReleased;
    this->recordLabel = recordLabel;
  }

  // Destructor
  ~Music() { }

  // Mutators
  void SetSongName(string songName) { this->songName = songName; }
  void SetArtistName(string artistName) { this->artistName = artistName; }
  void SetGenre(string genre) { this->genre = genre; }
  void SetYearReleased(string yearReleased) { this->yearReleased = yearReleased; }
  void SetRecordLabel(string recordLabel) { this->recordLabel = recordLabel; }

  // Accessors
  string GetSongName() const { return songName; }
  string GetArtistName() { return artistName; }
  string GetGenre() { return genre; }
  string GetYearReleased() { return yearReleased; }
  string GetRecordLabel() { return recordLabel; }

  // Overloading operators ==, >, < and =
  bool operator==(const Music& rhs);
  bool operator<(const Music& rhs);
  bool operator>(const Music& rhs);

private:
  // Member variables
  string songName;
  string artistName;
  string genre;
  string yearReleased;
  string recordLabel;
};

// Overloaded << operator needs to be declared global.
ostream& operator<<(ostream& os, Music& music);

#endif
