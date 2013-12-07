#include "dirent.h"
#include <vector>
#include "searchDirectory.h"
#include <iostream>
using namespace std;

// "//home//danha761//TDDI02//Arvid3//" +
string searchD(string finalDirectory){
  string fileNames;
  string temp;
  DIR *dir;
  string filePath = finalDirectory;
  struct dirent *ent;

  if((dir = opendir(filePath.c_str())) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      string str(ent->d_name);
      int pos = str.rfind('.',str.size());
      temp = str.substr(pos+1, str.size());
      if(temp == "txt"){
        fileNames +=  ent->d_name;
        for(int x = 0; x < 36-str.size(); ++x)
            fileNames += " ";
      }

    }
    closedir (dir);
  }
  return fileNames;
}
