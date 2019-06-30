#ifndef MAC_LOOP_H
#define MAC_LOOP_H
#include <sys/event.h>
#include "loop_impl.h"
namespace fw {
using std::map;
const int Events[] = {NOTE_DELETE, NOTE_WRITE,  NOTE_EXTEND, NOTE_ATTRIB,
                      NOTE_LINK,   NOTE_RENAME, NOTE_REVOKE};
class Loop : public LoopImp {
 private:
  map<int, Event *> _active;

  vector<struct kevent> _monitors;
  int _kfd;

  //  inline int evtEncode(int evFlag);
  //  inline int evtDecode(int evt);
  //  inline int evtsDecode(int evts);

 public:
  Loop(const Loop &loop_) = delete;

  Loop &operator=(const Loop &conn) = delete;
  Loop();

  ~Loop() = default;

  void register_(Event *&evt) override;

  void unregister_(Event *&evt) override;

  void modify(Event *&evt, int ev) override;

  vector<Event *> poll() override;
};
}  // namespace fw
#endif  // MAC_LOOP_H
