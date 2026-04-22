#include<iostream>
#include<vector>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

struct Student{
    char name[100];
    int attendance;
    int marks;
};

int main()
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if(pid == -1){
        std::cout<<"Fork failed\n";
        return 1;
    }

    else if(pid == 0){
        // CHILD

        close(fd[1]);

        int n;
        read(fd[0], &n, sizeof(int));

        std::vector<Student> students(n);
        read(fd[0], students.data(), n * sizeof(Student));//the size isn't sizeof(students.data) cos students.data() is a pointer. 
        //similarly never try to find the size of an array in memory by just calling size() on the array itself, cos that's again a pointer. 

        Student max = students[0];

        for(const Student &el : students){
            if(el.marks > max.marks){
                max = el;
            }
        }

        std::cout<<"Top student:\n";
        std::cout<<max.name<<" "
                 <<max.attendance<<" "
                 <<max.marks<<"\n";

        close(fd[0]);
    }

    else{
        // PARENT

        close(fd[0]);

        int n;
        std::cout<<"Enter number of students: ";
        std::cin>>n;

        std::vector<Student> students(n);

        for(auto &s : students){
            std::cout<<"Enter student name: ";
            std::cin>>s.name;

            std::cout<<"Enter attendance: ";
            std::cin>>s.attendance;

            std::cout<<"Enter marks: ";
            std::cin>>s.marks;
        }

        write(fd[1], &n, sizeof(int));//A buffer can also be a single element
        write(fd[1], students.data(), n * sizeof(Student));

        close(fd[1]);

        wait(NULL);
    }

    return 0;
}