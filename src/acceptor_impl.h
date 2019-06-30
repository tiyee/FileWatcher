#ifndef ACCEPTOR_IMPL_H
#define ACCEPTOR_IMPL_H
#include "common.h"
namespace fw {
using std::string;
using std::vector;
class AcceptorImpl {
 public:
  virtual void AddFiles(vector<string> files) = 0;
  virtual void AddFile(string file) = 0;
  virtual int Listen() = 0;
  virtual int Bind() = 0;
};

}  // namespace fw

#endif  // ACCEPTOR_IMPL_H
