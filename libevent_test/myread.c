#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <string.h>  
#include <fcntl.h>
#include <event2/event.h>  

void read_cb(evutil_socket_t fd,short what,void *arg)
{
  char buf[1024]={0};
  int len=read(fd,buf,sizeof(buf));
  printf("r_e:%s\n",what&EV_READ?"YES":"NO");
  printf("data len=%d,buf=%s\n",len,buf);
  sleep(1);
}
int main()
{
  unlink("myfifo");
  mkfifo("myfifo",0644);
  int fd=open("myfifo",O_RDONLY);
  struct event_base* base=NULL;
  base=event_base_new();
  struct event* ev=NULL;
  ev = event_new(base, fd, EV_READ | EV_PERSIST, read_cb, NULL);
  event_add(ev,NULL);
   event_base_dispatch(base);
   event_free(ev);
   event_base_free(base);
   close(fd);
   return 0;

}
