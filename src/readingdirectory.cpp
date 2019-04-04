#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sys/types.h>
#include <dirent.h>

typedef std::vector<std::string> stringvec;
 

 
void read_directory(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
} 
 
 
int main()
{
    stringvec v;
    read_directory("music", v);
     for (int i=0;i<v.size();i++){
        if (v[i].rfind(".", 0) == 0) {
          v.erase(v.begin()+i);
        }
     }
       
    for (unsigned i=0; i<v.size(); ++i)
    std::cout << v[i] << std::endl;;   
       
    //std::cout << "vector position 0: " << v[0] << std::endl;
    //std::cout << "vector position 1: " << v[1] << std::endl;
   
}