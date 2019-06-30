#include "mac_acceptor.h"
namespace fw {
Acceptor::Acceptor(LoopImp* loop_) : _loop(loop_) {}
void Acceptor::AddFile(string file) { _files.push_back(file); }
void Acceptor::AddFiles(vector<string> files_) {
  for (auto file_ : files_) {
    _files.push_back(file_);
  }
}
int Acceptor::Bind() {
  for (auto file_ : _files) {
    LOG("bind file:%s", file_.data());
    auto event_fd = open(file_.data(), O_EVTONLY);
    if (event_fd <= 0) {
      LOG_ERR(
          "The file %s could not be opened for monitoring.  Error was %s.\n",
          file_.data(), strerror(errno))
      return -1;
    }
    auto event =
        new Event(event_fd, fw::E_WRITE | fw::E_DELETE, (void*)file_.data());
    _loop->register_(event);
  }
  return _files.size();
}
int Acceptor::Listen() {
  for (int i = 0; i < 10; ++i) {
    auto items = _loop->poll();
    for (auto item : items) {
      std::cout << item->callback(item) << std::endl;
    }
  }
  return 1;
};
}  // namespace fw
