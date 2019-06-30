#ifndef MAC_ACCEPTOR_H
#define MAC_ACCEPTOR_H
#include <fcntl.h>
#include "acceptor_impl.h"
#include "loop_impl.h"
namespace fw {
class Acceptor : public AcceptorImpl {
 private:
  vector<string> _files;
  LoopImp* _loop;

 public:
  Acceptor(LoopImp* loop_);
  void AddFiles(vector<string> files) override;
  void AddFile(string file) override;
  int Listen() override;
  int Bind() override;
};
}  // namespace fw

#endif  // MAC_ACCEPTOR_H
