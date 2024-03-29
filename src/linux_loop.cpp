#include "linux_loop.h"
/**
 * @link https://developer.ibm.com/tutorials/l-inotify/
 */
namespace fw{
    Loop::Loop() {
        _efd = epoll_create(MAXEVENTS);
        if (-1 == _efd) {
            LOG_ERR("epoll create fail")
        }


    }
    void Loop::register_(Event *&evt) {
        struct kevent ev;
        ev.data.fd = evt->fd;
        ev.events = EPOLLIN | EPOLLET;
        ev.data = evt->data;
        if(epoll_ctl(_efd, EPOLL_CTL_ADD, evt->fd, &ev) != 0){
            LOG_ERR("epoll_ctl fail fd=%d",evt->fd)
            return;
        }
        _active[evt->fd] = evt;
        monitors.push_back(ev)

    }
    void Loop::unregister_(Event *&evt) {

        evt->data = nullptr;
        epoll_ctl(_efd,  EPOLL_CTL_DEL,evt->fd, nullptr);
        int fd_ = evt->fd;
        auto iter = _active.find(fd_);
        _active.erase(iter);
    }
    void Loop::modify(Event *&evt, int evn) {
        LOG("modify")

        _ev.events = evn==E_READ?EPOLLIN:EPOLLOUT;
        _ev.events|= EPOLLET;
        epoll_ctl(_efd,  EPOLL_CTL_MOD,evt->fd, &_ev);
        evt->ev_flags = evn;
    }
    vector<Event*> Loop::poll() {
        struct epoll_event events_in[MAXEVENTS];
        int n =epoll_wait(_efd, events_in, MAXEVENTS,-1);
        std::vector<Event *> items;
        for (int i = 0; i < n; ++i) {
            int fd = static_cast<int>(events_in[i].data.fd);
            auto item = _active[fd];
            if( events_in[i].events & EPOLLIN){

                item->ev_flags = E_READ;
            }
            if( events_in[i].events & EPOLLOUT){

                item->ev_flags = E_WRITE;
            }

            items.push_back(item);
        }
        return items;
    }


}
}