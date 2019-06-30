#ifndef EVENT_H
#define EVENT_H
#include <functional>
#include <string>
#include "common.h"
namespace fw {

enum E {
  E_DELETE = 0x00000001,
  E_WRITE = 0x00000002,
  E_EXTEND = 0x00000004,
  E_ATTRIB = 0x00000008,
  E_LINK = 0x00000010,
  E_RENAME = 0x00000020,
  E_REVOKE = 0x00000040,
  E_NONE = 0x00000080,
  E_FUNLOCK = 0x00000100

};
std::string show(E e) {
  switch (e) {
    case E_DELETE:
      return "NOTE_DELETE";
    case E_WRITE:
      return "NOTE_WRITE";
    case E_EXTEND:
      return "NOTE_WRITE";
    case E_ATTRIB:
      return "NOTE_ATTRIB";
    case E_LINK:
      return "NOTE_LINK";
    case E_RENAME:
      return "NOTE_RENAME";
    case E_REVOKE:
      return "NOTE_REVOKE";
    case E_NONE:
      return "NOTE_NONE";
    case E_FUNLOCK:
      return "NOTE_FUNLOCK";
    default:
      return "NULL";
  }
}
const E EVTS[] = {E_DELETE, E_WRITE,  E_EXTEND, E_ATTRIB, E_LINK,
                  E_RENAME, E_REVOKE, E_NONE,   E_FUNLOCK};
std::string print(char* f, int flags) {
  std::string ret;
  ret.reserve(512);
  std::string _or = " ";
  ret += f;
  for (E evt : EVTS) {
    if (flags & evt) {
      ret += _or;
      ret += show(evt);
      _or = "|";
    }
  }

  return ret;
}
struct Event {
  const int fd;
  int ev_flags;
  void* data;
  std::function<std::string(Event*)> callback = [&](Event* e) -> std::string {
    return print((char*)e->data, e->ev_flags);
  };
  Event(int fd_, int flag_, void* data_)
      : fd(fd_), ev_flags(flag_), data(data_){};
};

}  // namespace fw

#endif  // EVENT_H
