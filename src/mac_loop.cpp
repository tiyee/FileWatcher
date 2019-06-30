#include "mac_loop.h"
#include <sys/event.h>
// @link
// https://www.freebsd.org/cgi/man.cgi?query=EV_SET&sektion=3&apropos=0&manpath=FreeBSD+10.0-RELEASE
namespace fw {
inline int evtsEncode(int evFlag) {
  int n = 0x00000000;
  for (auto item : Events) {
    n |= evtsEncode(item);
  }
  return n;
}  // namespace fw
inline int evtEncode(int evFlag) {
  switch (evFlag) {
    case NOTE_DELETE:
      return E_DELETE;

    case NOTE_WRITE:
      return E_WRITE;

    case NOTE_EXTEND:
      return E_EXTEND;

    case NOTE_ATTRIB:
      return E_ATTRIB;

    case NOTE_LINK:
      return E_LINK;

    case NOTE_RENAME:
      return E_RENAME;

    case NOTE_REVOKE:
      return E_REVOKE;
    case NOTE_NONE:
      return E_NONE;
    case NOTE_FUNLOCK:
      return E_FUNLOCK;
    default:
      return 0x00000000;
  }
}
inline int evtDecode(int evt) {
  switch (evt) {
    case E_DELETE:
      return NOTE_DELETE;
    case E_WRITE:
      return NOTE_WRITE;
    case E_EXTEND:
      return NOTE_WRITE;
    case E_ATTRIB:
      return NOTE_ATTRIB;
    case E_LINK:
      return NOTE_LINK;
    case E_RENAME:
      return NOTE_RENAME;
    case E_REVOKE:
      return NOTE_REVOKE;
    case E_NONE:
      return NOTE_NONE;
    case E_FUNLOCK:
      return NOTE_FUNLOCK;
  }
  return 0x00000000;
}
inline int evtsDecode(int evts) {
  int n = 0x00000000;
  for (size_t i = 0; i < sizeof(EVTS) / sizeof(EVTS[0]); ++i) {
    auto e = EVTS[i];
    if (evts & e) {
      n |= evtDecode(e);
    }
  }
  return n;
}  // namespace fw

Loop::Loop()
    : _kfd(kqueue()){

      };
void Loop::register_(Event *&evt) {
  LOG("this monitors size=%d", this->_monitors.size());
  struct kevent ev;

  EV_SET(&ev, evt->fd, EVFILT_VNODE, EV_ADD | EV_ENABLE | EV_CLEAR,
         evtsDecode(evt->ev_flags), 0, evt->data);

  LOG("kevent success:: kid=%d", evt->fd)
  _active[evt->fd] = evt;
  this->_monitors.push_back(ev);
  LOG("this monitors size=%d", this->_monitors.size());
};

void Loop::unregister_(Event *&evt) {
  struct kevent ev[1];
  EV_SET(&ev[0], evt->fd, evtsDecode(evt->ev_flags), EV_DELETE, 0, 0, nullptr);
  int r = kevent(_kfd, ev, 1, nullptr, 0, nullptr);
  if (r < 0) {
    std::cout << "kevent error" << std::endl;
    return;
  }
  int fd_ = evt->fd;
  auto iter = _active.find(fd_);
  _active.erase(iter);
  // delete evt;
};

void Loop::modify(Event *&evt, int ev) {
  struct kevent kev[2];
  EV_SET(&kev[0], evt->fd, evtsDecode(evt->ev_flags), EV_DELETE, 0, 0, nullptr);
  EV_SET(&kev[1], evt->fd, evtsDecode(ev), EV_ADD, 0, 0, nullptr);
  int r = kevent(_kfd, kev, 2, nullptr, 0, nullptr);
  if (r < 0) {
    std::cout << "kevent error" << std::endl;
    return;
  }
  LOG("kevent success:: kid=%d", r)
  evt->ev_flags = ev;
};

vector<Event *> Loop::poll() {
  timespec timeout = {};
  timeout.tv_sec = 10;
  timeout.tv_nsec = 500000000;
  const int kMaxints = 20;

  struct kevent event_data[1];
  // int n = kevent(_kfd, nullptr, 0, activeEvs, kMaxints, &timeout);
  int n = kevent(_kfd, this->_monitors.data(), this->_monitors.size(),
                 event_data, this->_monitors.size(), &timeout);
  // LOG("poll return n=%d", n)
  LOG("monitor size=%d", this->_monitors.size());
  std::vector<Event *> items;

  for (int i = 0; i < n; ++i) {
    int fd = event_data[i].ident;
    int flags = event_data[i].fflags;
    LOG("fd=%d filter=%d", fd, flags)
    int ev_flags = 0;
    for (auto item : Events) {
      if (flags & item) {
        ev_flags |= evtEncode(item);
      }
    }
    Event *item = nullptr;
    item = _active[fd];
    item->ev_flags = ev_flags;
    items.push_back(item);
  }
  return items;
};

}  // namespace fw
