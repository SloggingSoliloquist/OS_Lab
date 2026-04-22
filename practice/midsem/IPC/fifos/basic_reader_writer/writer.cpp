#include<iostream>
#include<fcntl.h>//don't forget
#include<sys/stat.h>//don't forget
#include<unistd.h>
#include<string>
int main()
{
    const char * fifo= "notmyfifo";
    //a fifo is a file. create it by passing the permissions. 
    mkfifo(fifo, 0666);
    //to work with the fifo you still need file descriptors. So the
    //read() and write() methods actuall return file descriptors. 
    int fd= open(fifo, O_WRONLY);//Write Read
    //Treat this fd as the write/read end as you normally did
    std::string s;
    int n;
    std::cout<<"Enter the message: "<<std::endl;
    std::cin>>s;
    n=s.size();
    write(fd, &n, sizeof(int));
    write(fd, s.data(), s.size());//can do s.size() cos char buffer
    close(fd);
    return 0;
}