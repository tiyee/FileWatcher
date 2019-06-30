#ifndef LOOP_IMPL_H
#define LOOP_IMPL_H
#include "event.h"
#include"common.h"
namespace fw {
using std::vector;
class LoopImp {
 public:
  virtual void register_(Event *&ev) = 0;
  virtual void unregister_(Event *&ev) = 0;
  virtual void modify(Event *&evt, int ev) = 0;
  virtual vector<Event *> poll() = 0;
};
}  // namespace fw
#endif  // LOOP_IMPL_H
