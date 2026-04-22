#include<cstdlib>
#include<unistd.h>
#include<vector>
#include<math.h>
#include<iostream>
struct Point{
    float x;
    float y;
    float z;
};

float find_distance(float x, float y, float z){
    return(sqrt(x*x+y*y+z*z));
}
int main(int argc, char *argv[]){
    int read_end= atoi(argv[1]);
    int n;
    read(read_end, &n, sizeof(int));
    //reconstruct the vector of structs
    std::vector<Point> points(n);
    read(read_end, points.data(), n*sizeof(Point));
    Point min_point=points[0];
    int min_dist=find_distance(points[0].x, points[0].y,points[0].z);
    for(auto point: points){
        if(find_distance(point.x, point.y, point.z)<min_dist){
            min_point = point;
            min_dist=find_distance(point.x, point.y, point.z);
        }
    }
    std::cout<<"Point with min dist: "<<std::endl;
    std::cout<<min_point.x<<" "<<min_point.y<<" "<<min_point.z;
    return 0;
}