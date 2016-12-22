#include <string> 
using namespace std;
 /**
	* Final Exam
	* Author: Kyle Cooper
	* Class: CSCI 333
	* Professor Jung
	* December 13, 2016
	* Program Description: The header file for the class StudentFile
  */
class StudentFile {
	private: 
		string fileName; 
		
	public: 
	StudentFile(); //default constructor
	StudentFile(string fname); //constructor with parameters FOR CREATING FILE
	~StudentFile(); 
	
	//Functions: 
	int fileCreation(); //Create a file
	int testFile(); //tests to see if the file exists 
	string displayContents(); //display the contents of the file
	string getFileName(); 
	int dataAdd(string stuName, string stuID, string stuYear, string dep, string letGrade, double mid, double finalG, 
					double examAvg, double h1, double h2, double h3, double hwAvg, double proj, double att, double overallGrade); //for new obeject
	string dataSearch(string term);  //search database
	double calcExamAvg(double mid, double finalG); //calculate Exam average
	double calcHWAvg(double h1, double h2, double h3);  //calculate HW grades average
	double calcWghtAvg(double hwAvg, double examAvg, double proj, double att); //calcuates the weight average for all grades
	string calcLettergrade(double grade); //calculates the letter grade
	void closeFile(); 
};	