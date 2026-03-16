#include<iostream>
#include<sys/types.h>
#include<unistd.h>
#include<iostream>
#include<string>

int main()
{
    int fd[2];
    pipe(fd);
    pid_t pid=fork();
    if(pid==-1){
        return -1;
    }
    else if(pid==0){
        close(fd[1]);
        int n;
        read(fd[0], &n, sizeof(int));
        char buffer[n];
        read(fd[0], buffer, sizeof(char)*n);
        int j=n-1;
        int i=0;
        int flag=0;
        while(i<j){
            if(buffer[i]!=buffer[j]){
                std::cout<<"Not palindrome\n";
                flag=1;
                break;
            }
            i++;
            j--;
        }
        if (flag==0){
            std::cout<<"Palindrome";
        }
        close(fd[0]);

    }else{
        close(fd[0]);
        std::string s;
        std::cout<<"Enter the string: ";
        std::cin>>s;
        int n=s.length();
        write(fd[1], &n, sizeof(int));
        write(fd[1], s.data(), s.size());
        //size and length both return the length. But only in the case of sstrings, we can use s.size() cos each charaacter is size 1
        close(fd[1]);
    }
}
