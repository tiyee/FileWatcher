#include <fcntl.h>
#include <getopt.h>
#include <sys/event.h>
#include <iostream>
#include "acceptor_impl.h"
#include "common.h"
#include "mac_acceptor.cpp"
#include "mac_loop.cpp"

using namespace std;
using fw::Acceptor;
using fw::Event;
using fw::Loop;
using fw::LoopImp;
int main(int argc, char** argv) {
  vector<string> files_;
  int c;
  while (true) {
    static struct option long_options[] = {

        {"delete", required_argument, 0, 'd'},
        {"create", required_argument, 0, 'c'},
        {"file", required_argument, 0, 'f'},
        {0, 0, 0, 0}};
    int option_index = 0;

    c = getopt_long(argc, argv, "abc:d:f:", long_options, &option_index);
    if (c == -1) break;
    switch (c) {
      case 'h':
        printf("option -d with value `%s'\n", optarg);

        break;

      case 'f':
        files_.push_back(optarg);
        break;

      default:
        abort();
    }
  }

  //  string path = "/Users/jiangtao/code/github.com/FileWatcher/logs/test.log";
  //  string path2 =
  //  "/Users/jiangtao/code/github.com/FileWatcher/logs/test2.log";
  if (files_.size() < 1) {
    LOG_ERR("no options -f");
    exit(1);
  }
  LoopImp* loop_ = new Loop;
  auto acceptor = Acceptor(loop_);
  acceptor.AddFiles(files_);
  int r = -1;
  if ((r = acceptor.Bind()) < 1) {
    exit(1);
  }
  LOG("Bind %d files", r);
  r = acceptor.Listen();
  cout << r << endl;
  return 0;
}
