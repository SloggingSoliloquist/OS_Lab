#include<iostream>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string>

int main(){
    const char * fifo="notmyfifo";
    int fd = open(fifo, O_RDONLY);
    int n;
    read(fd, &n, sizeof(int));
    char buffer[n];
    read(fd, buffer, n);
    std::cout<<"I read: "<<buffer;
    close(fd);
    return 0;
}