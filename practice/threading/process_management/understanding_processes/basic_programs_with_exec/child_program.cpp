#include<iostream>
int main(int argc, char *argv[]){
    //the first argument in argv will always be the name of the program itself
    for(int i=0; i<argc; i++){
        std::cout<<"argv["<<i<<"]: "<<argv[i]<<std::endl;
    }
    return 69;
}