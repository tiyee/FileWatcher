#ifndef LINUX_LOOP_H
#define LINUX_LOOP_H

#include"loop_impl.h"
#include <sys/epoll.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/inotify.h>
/**
 *IN_ACCESS，即文件被访问
IN_MODIFY，文件被 write
IN_ATTRIB，文件属性被修改，如 chmod、chown、touch 等
IN_CLOSE_WRITE，可写文件被 close
IN_CLOSE_NOWRITE，不可写文件被 close
IN_OPEN，文件被 open
IN_MOVED_FROM，文件被移走,如 mv
IN_MOVED_TO，文件被移来，如 mv、cp
IN_CREATE，创建新文件
IN_DELETE，文件被删除，如 rm
IN_DELETE_SELF，自删除，即一个可执行文件在执行时删除自己
IN_MOVE_SELF，自移动，即一个可执行文件在执行时移动自己
IN_UNMOUNT，宿主文件系统被 umount
IN_CLOSE，文件被关闭，等同于(IN_CLOSE_WRITE | IN_CLOSE_NOWRITE)
IN_MOVE，文件被移动，等同于(IN_MOVED_FROM | IN_MOVED_TO)
 *
 *
 */

namespace fw {
    using std::map;
    const int Events[] = {IN_ACCESS, IN_MODIFY, IN_ATTRIB, IN_CLOSE_WRITE, IN_CLOSE_NOWRITE, IN_OPEN, IN_MOVED_FROM,
                          IN_MOVED_TO, IN_CREATE, IN_DELETE, IN_DELETE_SELF, IN_MOVE_SELF, IN_UNMOUNT, IN_CLOSE,
                          IN_MOVE};
    const MAXEVENTS = 256;

    class Loop : public LoopImp {
    private:
        int _efd;
        map<int, Event *> _active;
        vector<struct epoll_event> monitors;
    public:
        Loop();
        ~Loop() = default;

         void register_(Event *&evt) override ;

         void unregister_(Event *&evt) override ;

         void modify(Event *&evt, int ev) override ;

          vector<Event *> poll() override ;
    };
}


#endif // LINUX_LOOP_H
