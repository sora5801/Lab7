/*****************************************************************************/
//  Filename:      Lab7.cpp
//
//  Author: Matthew Fu
//
//  Date: 6/23/18
//
//
//
//  Description: This program takes in a text file that has large number of data
//               regarding a group of people's age, clinically measured maximum
//               heart rate, age, and five lines regarding the person's average commuting heart
//               rate of that day, the maximum commuting heart rate, and the exercise heart rate.
//               The file does have some errors, so the function has to be able to account
//               for those errors. After taking in all the information, it puts the required information
//               into 6 parallel arrays. Then it calls a selection sort function to sort the information
//               with respect to the subject number. After that, it outputs the header and outputs all
//               the information into a file and then close all the streams.
//
/*****************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//I declare my prototypes here. As there are six functions, I am going for the extra
//credit approach.
int input_raw_data(ifstream &, double[][3], int, int);
void outputHeading(ofstream &);
void construct_arrays(int, double[][3], double[], double[], double[], double[], double[], double[]);
void output(ofstream &, double[], double[], double[], double[], double[], double[], int);
void selectionSort(double[], int, double[], double[], double[], double[], double[]);
double calculateRatio(double, double);

/*****************************************************************************/
//
// Function: int main() 
//
// Parameters:  none
//
// Outputs: A file that has the heart informations of a bunch of people. 
//
// Returns: 0
//
// Author: Matthew Fu
//
// Date: 6/23/18
//
//
// Description: This is the main function. This function declares an input file stream
//              called myfile, a giant two-dimensional array, 6 parallel arrays, and a variable for the amount of rows
//              in the file. Then it calls the input raw data function to fill the giant array with
//              the information from the file. After knowing how many rows there in the file, it can pass
//              that value into the construct arrays function so it can store the correct values into the
//              6 parallel arrays. After having all the values stored, it calls the selection sort function
//              to sort the parallel arrays with respect to the subject number of the person from highest to lowest.
//              Then it outputs the outputheader function and the output function and then close the streams.
//
/*****************************************************************************/


int main()
{
   ifstream myfile;
  
   //The file given to me has 3 columns and a so far unspecified amount of lines
   //Each people in the file has 6 lines of information. Logically speaking, the amount of
   //people in the file is the total amount of lines in the file divided by 6.

   //This is a two dimensional double array. Their amount of storage must be declared
   //otherwise, the program will not compile as static arrays do not accept variable storage
   //values. The number 100 is completely arbitrary as I only want a giant array.
   double data[100][3];

   //Here I declare the 6 parallel arrays that can hold ten elements. All of them are doubles.
   double averageHR[10]; //Average heart rate of people
   double subjectNumber[10]; //The subject number
   double estimatedMHR[10]; //The estimated maximum heart rate
   double ratioMeasuredMHR_EstimatedMHR[10]; // The ratio of the measured maximum heart rate over the estimated maximum heart rate.
   double ratioHighestCHR_MeasuredMHR[10]; //The ratio of the highest commuting heart rate over the measured maximum heart rate.
   double personOwnExercise[10]; //The number of days that person exercised on his/her own

   //I declare this variable to find out how many lines there are in the file
   int amountOfRowsInFile = 0;

   //This function fills in the data to the giant two dimensional array.Also, by calling this function
   //I will have the number of rows in the file. Therefore, I store this function into a variable.
   amountOfRowsInFile =  input_raw_data(myfile, data, 100, 3);

   //The number of people in the file. 
   int number_of_people = amountOfRowsInFile / 6;

   //This function stores the calculated values into the 6 parallel arrays.
   construct_arrays(amountOfRowsInFile, data, averageHR, personOwnExercise, subjectNumber, estimatedMHR, ratioMeasuredMHR_EstimatedMHR, ratioHighestCHR_MeasuredMHR);

   //After storing all the values into their respective arrays, I sort them by their subject number from lowest to highest.
   selectionSort(subjectNumber, number_of_people, averageHR, personOwnExercise, estimatedMHR, ratioMeasuredMHR_EstimatedMHR, ratioHighestCHR_MeasuredMHR);
   ofstream thisfile;
   thisfile.open("OutputData.txt");

   // This function outputs the header for the calculations.
   outputHeading(thisfile);
   //This function gives the output in a neat and ordered format.
   output(thisfile, subjectNumber, averageHR, personOwnExercise, estimatedMHR, ratioMeasuredMHR_EstimatedMHR, ratioHighestCHR_MeasuredMHR, number_of_people);

   myfile.close();
   thisfile.close();
   return 0;
}
/*****************************************************************************/
//
// Function: input_raw_data(ifstream &myfile, double data[][3], int number_of_lines , int col)
//
// Parameters:  ifstream &myfile- This is the reference for the input stream
//              ifstream data[][3] -This is the two dimensional array with 3 cols where
//                                  it will be filled with data
//              int number_of_lines- This is the number of lines there are in the file.
//              int col - the number of columns there are in the file(given)
// Outputs:
//
// Returns: rows
//
// Author: Matthew Fu
//
// Date: 6/23/18
//
//
// Description: This function takes in all the data from the HR.txt file and store them
//              into one large two dimensional array. Also, this function finds out exactly
//              how many rows there are in the file and returns it.
//
//
/*****************************************************************************/
int input_raw_data(ifstream &myfile, double data[][3], int number_of_lines, int col) {
   //First I open the file
   myfile.open("HR.txt");

   //I check if the file exists.
   if (myfile.fail()) {
      cout << "No such file";
      exit(100);
   }
   
   //Then I declare the counter variables.
   int rows = 0;
   int cols = 0;

   //While the file is not at the end of the file,
   //it will keep on storing numbers into a two dimensional
   //column
   while (!myfile.eof()) {
      for (rows = 0; rows < number_of_lines; rows++) {
         for (cols = 0; cols < col; cols++)
         {
            myfile >> data[rows][cols];

         }
         if (myfile.eof())
            break;
      }
   }
   rows++;
   return rows;

}
/*****************************************************************************/
//
// Functionvoid construct_arrays(int numberOfLines, double dataOfPeople[][3], double averageHR[], 
//                         double numberOfDaysPersonExercised[], double subjectNumber[], double estimatedHeartRate[], 
//                         double ratioOfMMHR_EMHR[], double ratioOfHCHR_MMHR[])
//
// Parameters: int numberOfLines - the amount of lines there are in the file.
//             double dataOfPeople[][3] - the giant two-dimensional array filled with data
//             double averageHR[] - the array to hold the average heart rate values.
//             double numberOfDaysPersonExercised[] = the array to hold the number of days person exercised.
//             double subjectNumber[] - the array to hold the subject number of each person.
//             double estimatedHeartRate[]- the array to hold the estimated heart rate of each person
//             double ratioOfMMHR_EMHR[] - the array to the hold the ratio of measured maximum heart rate to estimated maximum heart rate
//             double ratioOfHCHR_MMHR[] - the array to hold the ratio of highest commuting heart to measured maximum heart rate
//
//
// Outputs:    None
//
// Returns:
//
// Author: Matthew Fu
//
//
// Date: 6/23/18
//
// Description: This function takes the large array from main and fills
//              them into the six parallel arrays also from main with their correct numbers. 
//              For instance, it takes the upper left number (row 1 col 1) every six lines
//              and store them into the the subject number array. It finds the number of days
//              the person exercised and store them into the array. It does the correct
//              calculations for all the variables. Also, this function calls a subfunction called
//              calculateRatio to perform the calculations of the two ratios.
//
//
/*****************************************************************************/
void construct_arrays(int numberOfLines, double dataOfPeople[][3], double averageHR[], double numberOfDaysPersonExercised[], double subjectNumber[], 
                      double estimatedHeartRate[], double ratioOfMMHR_EMHR[], double ratioOfHCHR_MMHR[]) {
   //These are my counter variables.
   int rowNumber;
   double a = 0.0, totalValue = 0.0, highestValue = 0.0;
   int accumlator = 0;
   int rowCounter = 0, anIndex = 0;

   //This array is there to find the highest commuting heart rate
   double highestCommutingValue[10];

   int numberofdate = 0;

   for (rowNumber = 0; rowNumber < numberOfLines; rowNumber++)
   {
      //The modular division is there to seperate each person's information.
      //As there are 6 lines for each person, this counter will 
      rowCounter = (rowNumber % 6);
      if (rowCounter > 0) //This is to go for each line with each person.
      {
         //The file has a number of errors and they are denoted as -1. The
         //following nested if are to not account for those errors in our
         //calculations. 
         if (dataOfPeople[rowNumber][0] > 0.0)
         {
            a = dataOfPeople[rowNumber][0] + a;
            accumlator += 1;
         }
         // Also, on the days the person did not exercise, the heart rate
         // value is zero. We are not to count those.
         if (dataOfPeople[rowNumber][2] > 0.0) {
            numberofdate += 1;
         }
         if (highestValue < dataOfPeople[rowNumber][1]) {
            highestValue = dataOfPeople[rowNumber][1];

         }
         //Once we reach the sixth row, we start the calculation
         if (rowCounter == 5) {
            //We now divide the sum of average daily heart rate by the 
            //number of days where the data was not corrupted(not -1).
            totalValue = a / accumlator;
            a = 0.0; accumlator = 0;
            //Then we store them into the 10 elements array
            averageHR[anIndex] = totalValue;
            numberOfDaysPersonExercised[anIndex] = numberofdate;
            highestCommutingValue[anIndex] = highestValue;
            highestValue = 0.0;
            anIndex++;
         }
         else
         {
            //An empty else that means nothing is going to happen
         }
      }
      else
      {
         //Here we start to put the correct numbers in their correct place.

         subjectNumber[anIndex] = dataOfPeople[rowNumber][0];
         estimatedHeartRate[anIndex] = 220 - dataOfPeople[rowNumber][2]; //formula is given

         //Here I call the calculateRatio subfunction to calculate the ratio of 
         //the measured maximum heart rate to the estimated maximum heart rate.

         ratioOfMMHR_EMHR[anIndex] = calculateRatio(dataOfPeople[rowNumber][1], estimatedHeartRate[anIndex]);
         
         numberofdate = 0;
      }

   }
   for (int i = 0; i < numberOfLines / 6 ; i++)
   {
      //Here I call the calculateRatio subfunction to calculate the ratio of the
      //highest commuting heart rate and the measured maximum heart rate. I know that
      //the measured maximum heart rate is in column 2 of the first row of each patient as it
      //is given.
      ratioOfHCHR_MMHR[i] = calculateRatio(highestCommutingValue[i], dataOfPeople[i * 6][1]);
   }
}
/*****************************************************************************/
//
// Function: double calculateRatio(double numeratorValue, double denominatorValue)
//
// Parameters: double numeratorValue - the value of the numerator 
//             double denominatorValue - the value of the denominator
//
// Outputs:    None
//
// Returns: (numeratorVale/ denominatorValue) * 100
//
// Author: Matthew Fu
//
// Date: 6/23/2018
//
//
// Description: This function is used to calculate the ratio of the measured maximum heart rate
//              to estimated maximum heart rate and the ratio of the highest commuting heart rate
//              to the measured maximum heart rate.
//
//
/*****************************************************************************/

double calculateRatio(double numeratorValue, double denominatorValue){
   //The formula of a ratio.
   return (numeratorValue / denominatorValue) * 100;
}

/*****************************************************************************/
//
// Function: void selectionSort(double subjectNumberOfPerson[], int size, double averageHeartRate[], double daysPersonExercised[], 
//                             double estimatedHeartRate[], double ratioOfMeasuredMHR_EstimatedMHR[], double ratioOfHighestCHR_MeasuredMHR[])
//
// Parameters: double subjectNumberOfPerson[] - this is the array to be sorted
//             int size- this is the size of the array.
//             double averageHeartRate[] - the array that holds the average heart rate values.
//             double daysPersonExercised[] - the array that holds the number of days person exercised.
//             double estimatedHeartRate[] - the array that holds the estimated heart rate of each person
//             double ratioOfMeasuredMHR_EstimatedMHR[] -  the array that holds the ratio of measured maximum heart rate to estimated maximum heart rate
//             double ratioOfHighestCHR_MeasuredMHR[] - the array that holds the ratio of highest commuting heart to measured maximum heart rate
//
// Outputs:    None
//
// Returns:
//
// Author: Matthew Fu
//
// Date: 6/23/2018
//
//
// Description: This is a basic selection sort function that sorts the persons number from
//              lowest value to highest value. Also, it takes the information about each person and
//              sort them with respect to the subject number.
//
//
/*****************************************************************************/
void selectionSort(double subjectNumberOfPerson[], int size, double averageHeartRate[], double daysPersonExercised[], double estimatedHeartRate[], 
                   double ratioOfMeasuredMHR_EstimatedMHR[], double ratioOfHighestCHR_MeasuredMHR[])
{
   int startScan, minIndex, minValue;
   double measuredAverageHeartRate, theDaysThePersonExercised, theEstimatedHeartRate, ratioOfMMHR_EMHR, ratioOfHCHR_MMHR;

   //A basic selection sort algorithm. It works by locating the smallest elemenr in the array
   //and then exchanging it with position 0. Locate the next smallest element in the array and
   //exchange it in position 1. It continues until all the elements are arranged in order.
   //The subject numbers are the ones being sorted. The information of that person must be ordered
   //with it.
   for (startScan = 0; startScan < (size - 1); startScan++)
   {
      minIndex = startScan;
      minValue = subjectNumberOfPerson[startScan];
      for (int index = startScan + 1; index < size; index++)
      {
         if (subjectNumberOfPerson[index] < minValue)
         {
            minValue = subjectNumberOfPerson[index];
         
            measuredAverageHeartRate = averageHeartRate[index];
            theDaysThePersonExercised = daysPersonExercised[index];
            theEstimatedHeartRate = estimatedHeartRate[index];
            ratioOfMMHR_EMHR = ratioOfMeasuredMHR_EstimatedMHR[index];
            ratioOfHCHR_MMHR = ratioOfHighestCHR_MeasuredMHR[index];
            minIndex = index;
         }
      }
      //The modifications are here. Each person has a bunch of information about them.
      //This is where they get sorted with respect to the subject number.
      subjectNumberOfPerson[minIndex] = subjectNumberOfPerson[startScan];
      averageHeartRate[minIndex] = averageHeartRate[startScan];
      daysPersonExercised[minIndex] = daysPersonExercised[startScan];
      estimatedHeartRate[minIndex] = estimatedHeartRate[startScan];
      ratioOfMeasuredMHR_EstimatedMHR[minIndex] = ratioOfMeasuredMHR_EstimatedMHR[startScan];
      ratioOfHighestCHR_MeasuredMHR[minIndex] = ratioOfHighestCHR_MeasuredMHR[startScan];

      subjectNumberOfPerson[startScan] = minValue;
      averageHeartRate[startScan] = measuredAverageHeartRate;
      daysPersonExercised[startScan] = theDaysThePersonExercised;
      estimatedHeartRate[startScan] = theEstimatedHeartRate;
      ratioOfMeasuredMHR_EstimatedMHR[startScan] = ratioOfMMHR_EMHR;
      ratioOfHighestCHR_MeasuredMHR[startScan] = ratioOfHCHR_MMHR;
   }
}
/*****************************************************************************/
//
// Function: output(ofstream &thisfile, double subject[], double average[], double number[],
//                    double estimatedHR[], double ratioEHR[], double ratioCHR[])
//
// Parameters:   ofstream &thisfile - the output file stream
//               double subject[] - this is the array to be sorted
//               double average[] - the array that holds the average heart rate values.
//               double number[] - the array that holds the number of days person exercised.
//               double estimatedHR[] - the array that holds the estimated heart rate of each person
//               double ratioEHR[] - the array that holds the ratio of measured maximum heart rate to estimated maximum heart rate
//               double ratioCHR[] - the array that holds the ratio of highest commuting heart to measured maximum heart rate
//               int theNumberOfPeople - the number of people in the file.
//
//
//
// Outputs:    None
//
// Returns:
//
// Author: Matthew Fu
//
// Date: 6/23/18
//
// Description: this function takes all the value that has been calculated, sorted, and put into arrays
//              and them displays them in a neat and ordered manner. The various setw are to make it neater.
//
//
/*****************************************************************************/
void output(ofstream &thisfile, double subject[], double average[], double number[], double estimatedHR[], double ratioEHR[], double ratioCHR[], int theNumberOfPeople) {
   for (int i = 0; i < theNumberOfPeople; i++) {
      thisfile << fixed << setprecision(0) << subject[i] << setw(9);
      thisfile << fixed << setprecision(1) << average[i] << setw(7);
      thisfile << fixed << setprecision(0) << number[i] << setw(13) << estimatedHR[i] << setw(13);
      thisfile << fixed << setprecision(1) << ratioEHR[i] << setw(10) << ratioCHR[i] << endl;
   }
}
/*****************************************************************************/
//
// Function: void outputHeading(ofstream &thisfile)
//
// Parameters: ofstream &thisfile - the output file stream
//
// Outputs:    None
//
// Returns:
//
// Author: Matthew Fu
//
// Date: 6/23/18
//
//
// Description: this function outputs the header of the file. It has various
//              amounts of setw values so to make the file looks neat and orderly.
//
//
/*****************************************************************************/
void outputHeading(ofstream &thisfile) {
   thisfile << "COMMUTING AND EXERCISE HEART RATE SUMMARY\n\n\n";
   thisfile << "SUBJECT" << setw(8) << "AVERAGE" << setw(8) << "DAYS"
      << setw(16) << "ESTIMATED" << setw(11) << "%MEASURED" << setw(6) << "%MAX" << endl;
   thisfile << "NUMBER" << setw(11) << "COMMUTING" << setw(11) << "EXERCISED" << setw(8)
      << "MAX HR" << setw(7) << "TO" << setw(18) << "COMMUTING" << endl;
   thisfile << setw(50) << "ESTIMATED" << setw(7) << "HR TO" << endl;
   thisfile << setw(47) << "MAX HR" << setw(13) << "MEASURED" << endl << endl;
}

