#include "dirent.h"
#include <vector>
#include "searchDirectory.h"
#include <iostream>
using namespace std;


string searchD(string finalDirectory){
  string fileNames;
  string temp;
  DIR *dir;
  string filePath = "//home//danha761//TDDI02//Arvid2//" + finalDirectory;
  struct dirent *ent;
 /* if(finalDirectory == "1")
    filePath = "//home//danha761//TDDI02//Arvid2//savedGames";
  if(finalDirectory == "2")
    filePath = "//home//danha761//TDDI02//Arvid2//newFiles";
  if(finalDirectory == "3")
    filePath = "//home//danha761//TDDI02//Arvid2//savedFiles";
*/
  //cout << "filePath: " << filePath << endl;
  if((dir = opendir(filePath.c_str())) != NULL) {
    /* print all the files and directories within directory */
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
