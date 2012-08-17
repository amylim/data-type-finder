#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

template<class T = int>
class Bag
{
  public:
     Bag();
     Bag(int x);
     ~Bag();
         
     T& operator=(T &other);
     Bag(T &other);
     
     void sortAscending();
     void sortDescending();
     void swapValues(T &i, T &j);
     void insert(T data); 
     int getTotal();
     int getUniqueAmt();
     void findPalindromes(bool sortUp);
     
     template<class U>
     friend ostream& operator<<(ostream& out, const Bag<U> &obj); 
     
     
  private:
     T *ptr;
     int *frequency;
     int size, qty;
     
     void copy(T &other);
};

template<class T>
Bag<T>::Bag()
{
   ptr = NULL;
   frequency = NULL;
   size = qty = 0;
}

template<class T>
Bag<T>::Bag(int x)
{           
   ptr = new T[size = x];
   frequency = new int[size];
   qty = 0;
}

Bag<int>::Bag(int x)
{           
   ptr = new int[size = x];
   frequency = new int[size];
   qty = 0;
}

template<class T>
Bag<T>::Bag(T &other)
{
   copy(other);              
}

template<class T>
Bag<T>::~Bag()
{
   delete [] ptr;   
   delete [] frequency;
}    

template<class T>         
T& Bag<T>::operator=(T &other) 
{
   if(this != &other)
      copy(other);
   return *this;
}   

template<class T>  
void Bag<T>::copy(T &other)
{
     delete ptr;
     ptr = new T[size = other.size];
     qty = other.qty;
     for(int i = 0; i < qty; i++)
        ptr[i] = other.ptr[i];
}

template<class T>    
void Bag<T>::sortAscending()
{
   for(int i = 0; i < qty; i++)
   {
      T min = ptr[i];
      int indexOfMin = i;
      for(int j = i + 1; j < qty; j++)
      { 
         if(ptr[j] < min)
         {
            min = ptr[j];
            indexOfMin = j;
         }
      }
      swapValues(ptr[i], ptr[indexOfMin]);
      int temp = frequency[i];
      frequency[i] = frequency[indexOfMin];
      frequency[indexOfMin] = temp;
   }
}

template<class T>    
void Bag<T>::sortDescending()
{
   for(int i = 0; i < qty; i++)
   {
      T max = ptr[i];
      int indexOfMax = i;
      for(int j = i + 1; j < qty; j++)
      { 
         if(ptr[j] > max)
         {
            max = ptr[j];
            indexOfMax = j;
         }
      }
      swapValues(ptr[i], ptr[indexOfMax]);
      int temp = frequency[i];
      frequency[i] = frequency[indexOfMax];
      frequency[indexOfMax] = temp;
   }
}

template<class T>    
void Bag<T>::swapValues(T &i, T &j)
{
   T temp = i;
   i = j;
   j = temp;  
}

template<class T> 
void Bag<T>::insert(T data)
{
   if(qty == size)
      throw 200;
   int i = 0;
   while(data != ptr[i] && i < qty)
   {
      i++;
   }
   if(i == qty)
   {
      ptr[qty++] = data;
      frequency[i] = 1;
   }  
   else 
      frequency[i] += 1; 
}

template<class U>
ostream& operator<<(ostream& out, const Bag<U> &obj)
{
   for(int i = 0; i < obj.qty; i++)
      out << setw(7) << obj.frequency[i] << "   " << obj.ptr[i] << endl;
   return out;
}

template<class T>
int Bag<T>::getTotal()
{
   int count = 0; 
   for(int i = 0; i < qty; i++) 
      count += frequency[i];
   return count;    
}

template<class T>
int Bag<T>::getUniqueAmt()
{
   return qty;
}

void Bag<string>::findPalindromes(bool sortUp)
{
   Bag<string> temp(qty);
   for(int i = 0; i < qty; i++)
   {
      int length = 0;
      for(int k = 0; ptr[i][k] != '\0'; k++)
         length++;
      int mid = length / 2;     
      int j = 0;
      while(j < mid && tolower(ptr[i][j]) == tolower(ptr[i][length-1-j]))
         j++;
      if(j == mid)
         temp.insert(ptr[i]);
   }
   cout << "Palindromes in the file: " << endl;
   if(sortUp)
      temp.sortAscending();
   else 
      temp.sortDescending();
   cout << temp;
}
