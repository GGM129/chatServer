#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <event2/event.h>

// 瀵规搷浣滃鐞嗗嚱鏁?
void write_cb(evutil_socket_t fd, short what, void *arg)
{
    // write绠￠亾
    char buf[1024] = {0};
    
    static int num = 0;
    sprintf(buf, "hello,world-%d\n", num++);
    write(fd, buf, strlen(buf)+1);
    
    sleep(1);
}


// 鍐欑閬?
int main(int argc, const char* argv[])
{
    // open file
    //int fd = open("myfifo", O_WRONLY | O_NONBLOCK);
    int fd = open("myfifo", O_WRONLY);
    if(fd == -1)
    {
        perror("open error");
        exit(1);
    }

     struct event_base* base = NULL;
    base = event_base_new();

    // 鍒涘缓浜嬩欢
    struct event* ev = NULL;
    // 妫€娴嬬殑鍐欑紦鍐插尯鏄惁鏈夌┖闂村啓
    //ev = event_new(base, fd, EV_WRITE , write_cb, NULL);
    ev = event_new(base, fd, EV_WRITE | EV_PERSIST, write_cb, NULL);

    // 娣诲姞浜嬩欢
    event_add(ev, NULL);

    // 浜嬩欢寰幆
    event_base_dispatch(base);

    // 閲婃斁璧勬簮
    event_free(ev);
    event_base_free(base);
    close(fd);
    
    return 0;
}

