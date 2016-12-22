#include <iostream> 
#include <string> 
#include <cstring>
#include <fstream> 
#include <iomanip>
#include "StudentFile.h"

using namespace std;

 /**
	* Final Exam
	* Author: Kyle Cooper
	* Class: CSCI 333
	* Professor Jung
	* December 13, 2016
	* Program Description: this is the class that does almost everything from the file. Allows for search, avg calculations and more 
	* 
	* wihthin this program there are mostly return statements that return some form of object, int, string  etc. to whatever is calling it 
	* This is done so that whatever is using it can maniupluate the output, not the actual function within the class. For example, if you 
	* add a GUI to this project later, it makes it easier. 
  */
/**
 * @brief 
 * @return 
Consturcutor that does not take paramters, is not used, and returns an error
 */

StudentFile::StudentFile() {
	cout << "\nYou have errored!\n"; //cout is only incase this constructor is called on accident
}

/**
 * @brief 
 * @param fname name of file user wants to work with
 * @return 
 * Constructor that sets the file name, 
 */
StudentFile::StudentFile(string fname) { 
	fileName = fname; 

}

/**
 * @brief 
 * @return
 * Deconstructor 
 */
StudentFile::~StudentFile() {
}

/**
 * @brief 
 * @return returns a notification telling whether the file was there succesfully
 * test to see if a file is there, or not. If not lets whatherver is calling know or not
 */
int StudentFile::testFile() { //test if file is valid
	int notification; 
	char tempName[256]; 
	string contents;
	strcpy(tempName, fileName.c_str());  //copies the string into an array because fwrite does not understand strings
	if(ifstream(tempName)) {
		notification = 1;
	} else if (!ifstream(tempName)) {
		notification = 0;
	}
	return notification;
}

/**
 * @brief 
 * @return returns an int to see if the file was created succesfully or not
* Creats a new file with a basic template design that includes some spaceing, and proper headings
 */
int StudentFile::fileCreation() { //create the file 
	int notification; 
	char tempName[256]; 
	string contents;
	std::strcpy(tempName, fileName.c_str());	
	ofstream fileWrite(tempName); //make this work with strings.	
	if(fileWrite.is_open()) { 
		fileWrite <<"Student Name | " << setw(20) << "Student ID | " << setw(20) << 
					"Year in School | " << setw(20) << "Department | " << setw(20) <<
					"Mid-Term Exam |" << setw(20) << "Final Exam |  " << setw(6) << setw(20) << "Exam Avgerage | "  << setw(6) <<
					"HW.1 | " << setw(6) << "HW.2 |" << setw(6) << "HW.3 | " << setw(6) << "HW Avg | " << setw(11) <<
					"Attendance | " << setw(8) << "Project | " << setw(15) << "Overall Grade | " <<
					setw(13) << "Letter Grade |";
		notification = 1;
	} else {
		notification = 0;
	} 
	fileWrite.close();
	return notification;
}

/**
 * @brief 
 * @return resturns a string that is fully formatted to display the contents of the file
* Displays the contents of the file. Puts it all into a string and then returns that to whatever is calling the functions
 */
string StudentFile::displayContents() {
	string contents;
	string display_Contents;
	ifstream readFile; 
	char tempName[256];
	std::strcpy(tempName, fileName.c_str());
	readFile.open(tempName);
	if(readFile.is_open()) {
		while(true) {
			getline(readFile, contents);
			display_Contents += contents + "\n";
			if(readFile.eof()) {
				break; 
			}
		}
	}
	readFile.close();
	return display_Contents; 
}

/**
 * @brief 
 * @return returns a notification if file write was a failure or success 1 = success 0 = failure
 * Adds data into the last row of the file based on what the user enters
 */
int StudentFile::dataAdd(string stuName, string stuID, string stuYear, string dep, string letGrade,
							double mid, double finalG, double examAvg, double h1, double h2, double h3, 
							double hwAvg, double proj, double att , double overallGrade) {
	char tempName[256]; //need to convert to string because fileAppend does not like Strings
	int notfication;
	std::strcpy(tempName, fileName.c_str());
	ofstream fileAppend(tempName, ios::app);
	if (fileAppend.is_open()) {
		fileAppend << "\n" << stuName << " | " <<  setw(20) << stuID << " | "<<  
					setw(20) << stuYear << " | " <<  setw(20) << dep << " | "<<  setw(20)<<
					mid  << " | "<<  setw(6)<< finalG << " | "<<  setw(20)<< examAvg << " | "<<  setw(6)<< h1 << " | "<< 
					setw(6) << h2  << " | "<< setw(6)<< h3 << " | " << setw(6)<< hwAvg << " | "<< setw(11) << att<< " | " << setw(8) << proj << " | "<< 
					setw(15) << overallGrade << " | "<<setw(13) << letGrade<< " | ";
		notfication = 1; //success
	} else {
		notfication = 0; //indicate failure
	}
	fileAppend.close();
	return notfication;
}

/**
 * @brief 
 * @return Returns the name of the file
 * Gets the ame of the file
 */
string StudentFile::getFileName() {
	return fileName;
}


/**
 * @brief 
 * @param mid mid term grade 
 * @param finalG final grade
 * @return returns the comuted average
 * returns the computed average 
 */
double StudentFile::calcExamAvg(double mid, double finalG) {
	double sum, avg;
	sum = mid + finalG; 
	avg = sum/2; //2 because there are only two exams
	return avg;
	
}

/**
 * @brief 
 * @param h1 hw 1 grade 
 * @param h2 hw2 grade
 * @param h3 h3 grade
 * @return returns the average of the homework grades
 * computes and returns the average of the homework grades
 */
double StudentFile::calcHWAvg(double h1, double h2, double h3) {
	double sum, avg;
	sum = h1 + h2 + h3;
	avg = sum/3;
	return avg; 
}

/**
 * @brief 
 * @param hwAvg takes hw average grade 
 * @param examAvg takes exam average grade
 * @param proj takes project grades
 * @param att takes attedence grade
 * @return returns the weight grade based on the forumula provided
 * coputes and returns the weighted average garade on the provided formula
 */
double StudentFile::calcWghtAvg(double hwAvg, double examAvg, double proj, double att) {
	double avg;
	avg = (hwAvg * 0.20)+(examAvg *0.50)+(proj*0.20)+(att*0.10);
	return avg;
}

/**
 * @brief 
 * @param grade takes the overall grade 
 * @return returns the calculated overall grade as string. ex A, B, C etc
 * converts and returns the letter grade for the class as string
 */
string StudentFile::calcLettergrade(double grade) { //parameter is the double (number grade) which needs to be converted to a letter
	string letterGrade;;  //letter grade 
	if(grade >= 90.00) {
		letterGrade = "A";
	} else if (grade >= 80.00 && grade <= 89.99) {
		letterGrade = "B";
	} else if (grade >= 70.00 && grade <= 79.99) {
		letterGrade = "C";
	} else if (grade >= 65.00 && grade <= 69.99) {
		letterGrade = "D";
	} else {
		letterGrade = "F";
	}
	return letterGrade; //return the newly found letter grade.
}

/** 
 *  Searchs through the file for a specific term and tries to located it. 
 * returns lines that show up with those contents as a string
 */
string StudentFile::dataSearch(string term) { //search through the file for the search term
	string contents;
	string display_Contents;
	ifstream readFile; 
	char tempName[256];
	std::strcpy(tempName, fileName.c_str());
	readFile.open(tempName);
	if(readFile.is_open()) {
		while(true) {
			getline(readFile, contents);
			if(contents.find(term) != string::npos) {
				display_Contents += contents + "\n";
			}
			if(readFile.eof()) {
				break; 
			}
		}
	}
	readFile.close();
return display_Contents;  
}