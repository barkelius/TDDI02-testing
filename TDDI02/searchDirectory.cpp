#include "dirent.h"
#include <vector>
#include "searchDirectory.h"
#include <iostream>
using namespace std;


string searchD(){
  string fileNames;
  string temp;
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir ("C:\\emacs-22.3\\bin\\test\\TDDI02")) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      string str(ent->d_name);
      int pos = str.rfind('.',str.size());
      temp = str.substr(pos+1, str.size());
      if(temp == "txt"){
	fileNames +=  ent->d_name;
	fileNames += "\n";
      }
      // for(int x = 0; x < 36-ent->d_name.size(); ++x)
      //fileNames += " ";
    }
    closedir (dir);
  } 
  return fileNames;
}
