#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int getdata(ifstream &, double[][3], int, int);
//void outputHeading();
void cal(int, double[][3]);
// void selectionSort();


int main()
{
   ifstream myfile;
   myfile.open("HR.txt");
   
   int r2 = 0;
   int row = 100;
   int col = 3;
  
   
   double data[100][3];
   r2 = getdata(myfile, data, row, col);
 


   cal(r2, data);
   
      
   
   return 0;
}

int getdata(ifstream &myfile, double data[][3], int row, int col) {

   int rows=0;
   int r1 = 0;
   int cols=0; //counters

  
   while(!myfile.eof()){
   
   for (rows = 0; rows < row; rows++) {
      
      for (cols = 0; cols < col; cols++)
      {
            myfile >> data[rows][cols];  
           
            
      }
      //cout << endl;
      if (myfile.eof())
         break;
   }
   rows++;
  /*
   for (r1 = 0; r1 < rows; r1++) {
      for (cols = 0; cols < col; cols++)
      {
         
            cout << setw(3) << data[r1][cols] << " ";

      }
      cout << endl;
      */
   }
   
   return rows;
   
}

void cal(int r2, double dd[][3]) {
   int r22;
   double a = 0.0, ta = 0.0;
   int ac = 0;
   int rc = 0, ai = 0;
   double A[10];

   cout << r2 << " ";
   for (int i = 0; i < r2; i++) {
      for (int c = 0; c < 3; c++)
      {

         cout << setw(3) << dd[i][c] << " ";

      }
      cout << endl;
   }
   
   for (r22 = 0; r22 < r2; r22++)
   {

      rc = (r22 % 6);
      if (rc > 0)
      {
         if (dd[r22][0] > 0.0)
         {
            cout << "//" << r22 << " ";
            cout << setw(3) <<dd[r22][0] <<" ";
            cout << r2 << " ";
            cout << r22 << " ";
            cout << a << " ";
            cout << ac << " " << endl;
            a = dd[r22][0]+a;
            ac += 1;
         }
         if (rc == 5) {
            ta = a / ac;
            a = 0.0; ac = 0;
            A[ai] = ta;
            ai++;
         }
         else
         {
         }



      }

      }
      for (int i = 0; i < 10; i++) {
         cout << A[i] << endl;
      }
  
}
