#include "player.h"
#include "character.h"
int main(){
    string filepath;
    Player daniel("adventure.txt");
    daniel.printPlayer();
    daniel.useItem("nyckel");
    daniel.printPlayer();
    Allied friend1("adventure.txt",1001);
    friend1.printAllied();
    Allied friend2("adventure.txt",1003);
    friend2.printAllied();
    
   
    //<----otestat start------> // bugg, läser in sluttecknet '¤' om itemet är 
    //det sista i rummet.... dvs 2008;asd;asda;¤ kommer ligga först i filen
    vector <string> lines;
    ifstream inFile;
    string str,str2;
    int itemId = 2008;
    int lineToMove = 0;    
    inFile.open("adventure2.txt");
    while(!inFile.eof()){
      getline(inFile,str,';');
      if(stringToInt(str) == itemId)
	lineToMove = lines.size();
      getline(inFile,str2);
      lines.push_back(str + ";" + str2);
    }
    inFile.close();
    string removeFile = "adventure3.txt";
    if(remove(removeFile.c_str()) != 0 )
      cerr << "failed to remove file" << removeFile << endl;
    ofstream outFile;
    lines.insert(lines.begin(),lines[lineToMove]);
    lines.erase(lines.begin()+lineToMove+1);
    outFile.open("adventure3.txt");
    for(int i = 0; i < lines.size(); ++i){  
      outFile << lines[i] << "\n";
    }
    //<----otestat end------>

return 0;
}
