#include <iostream>
#include <cstdlib>
using namespace std;
#include "binstree.h"
#include <fstream>

int main()
{
  BST MyTree;
  
  //variables to be read from .txt file
  string name;
  char location; 
  double reserve;
  string date;
  int n;
  el_t elem; //artwork info

  char choice;
  char choice2;
  //.txt file will be parsed to construct the element
  ifstream fin("inventory.txt", ios::in); //reads from inventory.txt
  
  //while name can be read from the file
  while(fin >> name)
    {
      fin >> location; //parse location
      fin >> reserve; //parse reserve 
      fin >> date; //parse date
      
     
      el_t elem(name,location,reserve,date); //construct elem
      MyTree.InsertVertex(elem); //add element to the BST
    }
  
  //output stream
  ofstream fout("salesHistory.txt", ios::out);
  
  MyTree.Display();
  
  choice = 'y';
  
  //while choice is yes
  while(choice == 'y')
    {
      cout << "Provide the name of the artwork: ";
      cin >> name;
      
      el_t elemsearch(name, location, reserve, date);
      
      //if element is found
      if(MyTree.Search(elemsearch))
	{
	  cout << "The artwork is in stock. Do you wish to sell it before the auction date? (y/n)" << endl;
	  cin >> choice2;
	  if(choice2 != 'n')
	    {
	      fout << elemsearch << '\n'; //read into file
	    
	      MyTree.DeleteVertex(elemsearch); //delete element
	    }
	}
      //element not found
      else
	cout << "The artwork is not in stock. Check file: salesHistory.txt" << endl;
      
      cout << "Would you like to search another artwork?" << endl;
      cin >> choice;
    }

  fout.close(); //close output file

  MyTree.Display();
}
