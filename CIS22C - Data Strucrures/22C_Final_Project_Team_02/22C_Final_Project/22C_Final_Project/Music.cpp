#include "Music.h"

bool Music::operator==(const Music& rhs) {
  return songName == rhs.GetSongName();
}

bool Music::operator<(const Music& rhs) {
  return songName < rhs.GetSongName();
}

bool Music::operator>(const Music& rhs) {
  return (songName > rhs.GetSongName());
}

/*ostream& operator<<(ostream& os, Music& music) {
  os << music.GetId() << " ";
  return os;
}*/