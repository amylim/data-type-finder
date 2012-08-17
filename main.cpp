/**********************************************************
Author: Amy Lim
Program: CS3A Test 2
Purpose: Searches a file for a particular data type 
         (string, char, int, double)
Notes: None.
**********************************************************/
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "template.h"

using namespace std;

int sizeOfFile(ifstream &fin, char fileName[]);
char* getData(ifstream &fin, int size);
void findString(char data[], int size);
void findChar(char data[], int size);
void findInt(char data[], int size);
void findDouble(char data[], int size);
bool uniqueChoice();
bool sortChoice();
int mainMenuChoice();

int main(int argc, char *argv[])
{
    char repeat;
    do
    {    
       try
       { 
          ifstream fin, fin2;

     	  cout << "Enter the name of the file: ";
	      char fileName[100];
	      cin >> fileName;
	
	      int size = sizeOfFile(fin2, fileName);

          fin.open(fileName);
	      
          if(fin.fail())
	       	 throw 404;
	      else
	      {
              char *data = new char[size];
              data = getData(fin, size);
        
              void (*menu[4])(char*, int);
              menu[0] = &findString;
              menu[1] = &findChar;
              menu[2] = &findInt;
              menu[3] = &findDouble;
        
              int choice = mainMenuChoice();
              menu[choice](data, size);

              fin.close();
          }
       }
       catch(int x) 
       {
          switch(x)
          {
          case 100:
               cout << "Invalid input. " << endl;
               break;
          case 200:
               cout << "Bag is full. " << endl;
               break;
          case 404:
               cout << "Invalid file. " << endl;
               break;
          default:
               cout << "Unknown error. " << endl;
               break;
          }    
       } 
       cout << "Repeat? ";
       cin >> repeat;
       cout << endl;
    }while(toupper(repeat) != 'N');
    system("PAUSE");
    return EXIT_SUCCESS;
}

int sizeOfFile(ifstream &fin, char fileName[])
{
    int size = 0;
    fin.open(fileName);
	if(fin.fail())
		throw 404;
	else
	{
        char next;
        fin.get(next);
        while(!fin.eof())
        {
           size++;
           fin.get(next);                   
        }
        fin.close();
    } 
    return size;
}

char* getData(ifstream &fin, int size)
{
   char *data = new char[size];
   char next;
   int pos = 0;
   fin.get(next);
   while(!fin.eof())
   {
      data[pos++] = next;
      //cout << next;              //displays data in the file onto the screen
      fin.get(next);                   
   }
   cout << endl;
   return data;
}

void findString(char data[], int size)
{
    Bag<string> stringBag(size);
    int pos = 0;
    bool unique = uniqueChoice();
    bool sortUp = sortChoice();
    ofstream fout;
    while(pos < size)
    {
       int iniPos = pos;       
       int wordLength = 0;
       while(isalnum(data[pos]))
       {
          wordLength++;
          pos++;
	   }
	   while(!(isalnum(data[pos])))
       {
          pos++;
	   }
	   char piece[wordLength+1];
       
       if(!unique)
	   {
          for(int i = 0; i < wordLength; i++)  
             piece[i] = tolower(data[iniPos+i]);      
          piece[0] = toupper(piece[0]);
       }
       else 
       {
          for(int i = 0; i < wordLength; i++)  
             piece[i] = data[iniPos+i];
       }
       
       piece[wordLength] = '\0';
       stringBag.insert(piece);    
    }
    if(sortUp)
       stringBag.sortAscending();
    else 
       stringBag.sortDescending();
    
    fout.open("output.txt");
    fout << stringBag;
    stringBag.findPalindromes(sortUp);
    cout << "Total different strings: " << stringBag.getUniqueAmt() << endl;
    cout << "Total strings: " << stringBag.getTotal() << endl;
}

void findChar(char data[], int size)
{
   Bag<char> charBag(256);
   bool sortUp = sortChoice();
   bool unique = uniqueChoice();
   
   if(!unique)
      for(int i = 0; i < size; i++)
         charBag.insert(toupper(data[i]));
   else 
      for(int i = 0; i < size; i++)
         charBag.insert(data[i]);
            
   if(sortUp)
       charBag.sortAscending();
   else 
       charBag.sortDescending();
       
   cout << charBag;
   cout << "Total different characters: " << charBag.getUniqueAmt() << endl;
   cout << "Total characters: " << charBag.getTotal() << endl;
}

void findInt(char data[], int size)
{
    Bag<float> intBag(size);
    int pos = 0;
    bool sortUp = sortChoice();
    while(pos < size)
    {
       int iniPos = pos;       
       int numLength = 0;
       while(isdigit(data[pos]) || data[pos] == ',' || data[pos] == '.')
       {
          numLength++;
          pos++;
	   }
	   while(!(isdigit(data[pos])))
       {
          pos++;
       }
       if(numLength > 0)
       {
	      char piece[numLength+1];
          int i = 0, j = 0;
          bool valid = true;
          while(i < numLength && valid == true)
          {
             if(isdigit(data[iniPos+i]))
             {
                piece[j] = data[iniPos+i];  
                j++;
             }
             if(data[iniPos+i] == '.')
                valid = false;
             i++;
          }    
          piece[numLength] = '\0';
       
          if(valid)
            intBag.insert(atoi(piece)); 
       }
    }
    
    if(sortUp)
       intBag.sortAscending();
    else 
       intBag.sortDescending();
    
    cout << intBag;
    cout << "Total different integers: " << intBag.getUniqueAmt() << endl;
    cout << "Total integers: " << intBag.getTotal() << endl;
}

void findDouble(char data[], int size)
{
    Bag<double> doubleBag(size);
    int pos = 0;
    bool sortUp = sortChoice();
    while(pos < size)
    {
       int iniPos = pos;       
       int numLength = 0;
       while(isdigit(data[pos]) || data[pos] == ',' || data[pos] == '.')
       {
          numLength++;
          pos++;
	   }
	   while(!(isdigit(data[pos])))
       {
          pos++;
       }
       if(numLength > 0)
       {
      	  char piece[numLength+1];
          int i = 0, j = 0;
          while(i < numLength)
          {
             if(isdigit(data[iniPos+i]) || data[iniPos+i] == '.')
             {
                piece[j] = data[iniPos+i];  
                j++;
             }
             i++;
          }
          piece[numLength] = '\0';
          doubleBag.insert(atof(piece)); 
       }
    }
    
    if(sortUp)
       doubleBag.sortAscending();
    else 
       doubleBag.sortDescending();
    
    cout << doubleBag;
    cout << "Total different floating point numbers: " << doubleBag.getUniqueAmt() << endl;
    cout << "Total floating point numbers: " << doubleBag.getTotal() << endl;
}

bool uniqueChoice()
{
   cout << "\t0 - Non-unique data types\n\t1 - Unique data types\nEnter your choice: ";
   int menu;
   cin >> menu;
   if(menu == 1 || menu == 0)     
      return menu;
   else
      throw 100;
}

bool sortChoice()
{
   cout << "\t0 - Sort Descending\n\t1 - Sort Ascending\nEnter your choice: ";
      int menu;
   cin >> menu;
   if(menu == 1 || menu == 0)     
      return menu;
   else
      throw 100;     
}

int mainMenuChoice()
{
    cout << "\t0 - Strings\n\t1 - Characters\n\t2 - Integers\n\t3 - Double\nEnter your menu choice: ";
    int menu;
    cin >> menu;
    if(menu < 0 || menu > 3)
       throw 100;
    else 
       return menu;
}
