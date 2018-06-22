/*****************************************************************************/
//  Filename:      Lab7.cpp
//
//  Author:        
//
//  Date:          
//
//  Modifications: 
//
//
//  Description:   
//
/*****************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int getdata(ifstream &, double[][3], int, int);
//void outputHeading(ofstream &);
void cal(int, double[][3], double[], double [], double[], double[], double[], double[]);
void output(ofstream &, double[], double[], double[], double[], double[], double[], int);
void selectionSort(double [], int, double[], double[], double[], double[], double[]);


int main()
{
   ifstream myfile;
   myfile.open("HR.txt");
   
   const int NUMBER_OF_PEOPLE = 10;
   int r2 = 0;
   int row = 100;
   int col = 3;

   double averageHR[NUMBER_OF_PEOPLE];
   double subjectNumber[NUMBER_OF_PEOPLE];
   double estimatedMHR[NUMBER_OF_PEOPLE];
   double ratioMeasuredMHR_EstimatedMHR[NUMBER_OF_PEOPLE];
   double ratioHighestCHR_MeasuredMHR[NUMBER_OF_PEOPLE];
   double personOwnExercise[NUMBER_OF_PEOPLE];
   
   double data[100][3];

   r2 = getdata(myfile, data, row, col);
 
   cal(r2, data, averageHR, personOwnExercise, subjectNumber, estimatedMHR, ratioMeasuredMHR_EstimatedMHR, ratioHighestCHR_MeasuredMHR);
  
   
   ofstream thisfile;
   thisfile.open("OutputData.txt");

   selectionSort(subjectNumber, NUMBER_OF_PEOPLE, averageHR, personOwnExercise,  estimatedMHR, ratioMeasuredMHR_EstimatedMHR, ratioHighestCHR_MeasuredMHR);

   output(thisfile, subjectNumber, averageHR, personOwnExercise, estimatedMHR, ratioMeasuredMHR_EstimatedMHR, ratioHighestCHR_MeasuredMHR, NUMBER_OF_PEOPLE);
      
   
   return 0;
}
/*****************************************************************************/
//
// Function:  
//
// Parameters: 
//
// Outputs:    None
//
// Returns:    
//
// Author:     
//
// Date:       
//
// Modifications: 
//
// Description:
// 
//

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
      if (myfile.eof())
         break;
   }
   rows++;
   }
   
   return rows;
   
}
/*****************************************************************************/
//
// Function:   double calc_resistance( double resistivity,
//                                     double length,
//                                     double diameter)
//
// Parameters: double resistivity - resistivity, in ohm-meter
// (Inputs)    double length      - wire length, in meters
//             double diameter    - wire diamter, in mm
//
// Outputs:    None
//
// Returns:    
//
// Author:     
//
// Date:       
//
// Modifications: 
//
// Description:
// 
//

void cal(int r2, double dd[][3], double averageHR[], double ND[], double subjectNumber[], double ehr[], double ratio[], double ratioH[]) {
   int r22;
   double a = 0.0, ta = 0.0, hv = 0.0;
   int ac = 0;
   int rc = 0, ai = 0;
  
   double HV[10]; 
   int numberofdate = 0;


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
         if (dd[r22][2] > 0.0) {
            numberofdate += 1;
         }
         if (hv < dd[r22][1]) {
            hv = dd[r22][1];

         }
         if (rc == 5) {
            ta = a / ac;
            a = 0.0; ac = 0;
            averageHR[ai] = ta;
            ND[ai] = numberofdate;
            HV[ai] = hv;
            hv = 0.0;
            ai++;
         }
         else
         { 
         
         }

      }
      else
      {
         subjectNumber[ai] = dd[r22][0];
         ehr[ai] = 220 - dd[r22][2];
         ratio[ai] = (dd[r22][1] / ehr[ai]) * 100;
         numberofdate = 0;
      }

      }
   for (int i = 0; i < 10; i++)
      ratioH[i] = (HV[i] / ehr[i]) * 100;
}

/*****************************************************************************/
//
// Function:   double calc_resistance( double resistivity,
//                                     double length,
//                                     double diameter)
//
// Parameters: double resistivity - resistivity, in ohm-meter
// (Inputs)    double length      - wire length, in meters
//             double diameter    - wire diamter, in mm
//
// Outputs:    None
//
// Returns:    double – resistance, in ohms
//
// Author:     
//
// Date:       
//
// Modifications: 
//
// Description:
//
//

void selectionSort(double array[], int size, double AHR[], double POE[], double EHR[], double RMHR[], double RCHR[])
{
   int startScan, minIndex, minValue;
   double mahr, mahr1, mahr2, mahr3, mahr4;

   
   for (startScan = 0; startScan < (size - 1); startScan++)
   {
      minIndex = startScan;
      minValue = array[startScan];
      for (int index = startScan + 1; index < size; index++)
      {
         if (array[index] < minValue)
         {
            minValue = array[index];
            mahr = AHR[index];
            mahr1 = POE[index];
            mahr2 = EHR[index];
            mahr3 = RMHR[index];
            mahr4 = RCHR[index];
            minIndex = index;
         }
      }
      array[minIndex] = array[startScan];
      AHR[minIndex] = AHR[startScan];
      POE[minIndex] = POE[startScan];
      EHR[minIndex] = EHR[startScan];
      RMHR[minIndex] = RMHR[startScan]; 
      RCHR[minIndex] = RCHR[startScan];

      array[startScan] = minValue;
      AHR[startScan] = mahr;
      POE[startScan] = mahr1;
      EHR[startScan] = mahr2;
      RMHR[startScan] = mahr3;
      RCHR[startScan] = mahr4;
   }
}
/*****************************************************************************/
//
// Function:  
//
// Parameters: 
//
// Outputs:    None
//
// Returns:    double – resistance, in ohms
//
// Author:     
//
// Date:       
//
// Modifications: 
//
// Description:
// 
//

void output(ofstream &thisfile, double subject[], double Average[], double Number[], double EstimatedHR[], double RatioEHR[], double RatioCHR[], const int numberOfpeople) {
   for (int i = 0; i < numberOfpeople; i++) {
      thisfile << fixed << setprecision(0) << subject[i] << "  ";
      thisfile << fixed << setprecision(1) << Average[i] << "  ";
      thisfile << fixed << setprecision(0) << Number[i] << "  " << EstimatedHR[i] << "  ";
      thisfile  << fixed << setprecision(1) << RatioEHR[i] << "  " << RatioCHR[i]   << endl;
   }
}
/*****************************************************************************/
//
// Function:  
//
// Parameters: 
//
// Outputs:    None
//
// Returns:    
//
// Author:     
//
// Date:       
//
// Modifications: 
//
// Description:
// 

void outputHeading(ofstream &thisfile) {

}

