#include <iostream>
#include <fstream>
using namespace std;

void getdata(ifstream &, double[][3], int, int, int);
//void outputHeading();
void output(ofstream &);
// void selectionSort();


int main()
{
   ifstream myfile;
   myfile.open("HR.txt");

   int each_person;
   int row = 6;
   int col = 3;
   double data[6][3];

   getdata(myfile, data, row, col, each_person);

   return 0;
}

void getdata(ifstream &myfile, double data[][3], int row, int col, int each_person) {

   int rows;
   int cols; //counters


   for (cols = 0; cols < col; cols++) {
      myfile >> data[0][cols];
   }
   for (rows = 0; rows < row; rows++) {
      for (cols = 0; cols < col; cols++)
      {
         myfile >> data[rows][cols];
         cout << [rows][cols] << endl;
      }
   }

