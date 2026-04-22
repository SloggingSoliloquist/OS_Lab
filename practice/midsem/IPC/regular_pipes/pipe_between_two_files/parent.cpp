#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<vector>
#include<string>

//Send vector of structs to child to process.
struct Point{
    float x;
    float y;
    float z;
};
//Program sends a vector of points and calculates the point that is farthest from origin
int main(){
    int fd[2];
    pipe(fd);
    pid_t pid=fork();
    if(pid==-1){
        std::cout<<"Couldn't fork"<<std::endl;
    }
    else if(pid==0){
        //before we call exec, we have to convert the integer file descriptors to strings
        //we actually only need to send the read end though, so only that needs to be converted
        char fd_str[10];
        sprintf(fd_str, "%d", fd[0]);//sprintf is like printf but it sends output to a char array[] or buffer instead of std output
        ;//this is what you'll pass as an argument
        char *args[]={(char *)"Banana", fd_str, NULL};
        execv("./child", args);
        perror("I'm sorry but the exec failed lol");
    }
    else{
    close(fd[0]);
    int n;
    std::cout<<"Enter the number of Points: ";
    std::cin>>n;
    std::vector<Point> points(n);
    for(auto &point:points){
        std::cout<<"X: ";
        std::cin>>point.x;
        std::cout<<"Y: ";
        std::cin>>point.y;
        std::cout<<"Z: ";
        std::cin>>point.z;
    }
    write(fd[1], &n, sizeof(int));//so that the child knows how many points there are
    write(fd[1], points.data(), n*sizeof(Point));
    close(fd[1]);
    return 0;
}
}