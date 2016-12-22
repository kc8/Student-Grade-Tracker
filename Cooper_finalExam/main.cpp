#include <iostream>
#include <string>
#include <iomanip>
#include <typeinfo>           
#include "StudentFile.h"
using namespace std;
 /**
	* Final Exam
	* Author: Kyle Cooper
	* Class: CSCI 333
	* Professor Jung
	* December 13, 2016
	* ProgramDescription: This program makes a database in a text file that stores students name, id, 
	* mid-term grades, final exam grades, homework grades, project and attendace grade. 
	* Uses OO Design to manipualte the file, and call various functions. 
  */
 
StudentFile newFile(); //Creates the new Student File

/**
 * @brief 
 * @return int returns exit status
	* Creates a file based on user input, then makes it an object and calls function based on that object
	* to see information regarding functions with the object caleld StudentFile look at StudenFile.cpp and StudentFile.h
	* 
	* This program is deisnged to try and display everything inside the main.cpp file. This means that most aspects using objects will expect something to be returned. 
 */
int main() {
	char trash[2]; //trash 
	int cont = 1;  //continue variable for while loop 
	int Uinput = 0; //userinput variable for their selection
	cout << "Welcome to the Final Project for CSCI333 by Kyle Cooper\n";
	cout << "This program will keep track of grades for a class in a file and display them \n\n";
	
	StudentFile file = newFile(); //create a file object. This uses a function to create it. 
	
	while (cont == 1) { 
		cout << "\n\nCurrently working with fil called: " << file.getFileName() << "\n"; //get and display the current file name that the user is working with
		cout << "The options for the file are below. Enter one of the following numbers.\n";
		cout << "1: Search\n"; //option to search
		cout << "2: Display File\n"; //option to display contents of file
		cout << "3: New entry\n"; //option to add new entry to file
		cout << "4: Create new file or change the current file\n"; //change or create a new file
		cout << "5: Exit\n"; //exit program
		cout << ">> ";
		cin >> Uinput;

		if (Uinput > 5 or Uinput < 1) { //check the vality of the input //WORK ON THIS  or (typeid(Uinput) != typeid(int())
			//cin.clear(); //clears the cin of the wrong input 
			cout << "\n\nPLEASE ENTER VALID INPUT\n\n";
		}
		if (Uinput == 5) { //exit program
			cont = 0; 
			 cout <<"\n\nThanks for using the grade keeper program\n\n";
			 break;
		}
		if (Uinput == 3) { //new entry
			// the variables below are used only for the input of information
			string stuName, stuID, stuYear, dep, letGrade;
			double mid, finalG,  h1,  h2,  h3,  proj, att, examAvg, overAllGrade, hwAvg;
			cout << "Add a new student to the file enter the following: \n";
			cin.getline(trash,2);
			cout << "Student Name: "; 
			getline(cin, stuName);
			cout << "Student ID: ";
			getline(cin,stuID);
			cout << "Student Year: ";
			getline(cin, stuYear);
			cout << "Department: ";
			getline(cin, dep);
			cout << "MidTerm Grade: ";
			//cin.getline(trash,2); //trash it!
			cin >> mid;
			cout << "Final Exam Grade:";
			cin >> finalG;
			cout << "HomeWork 1 Grade: ";
			cin >> h1;
			cout << "HomeWork 2 Grade: ";
			cin >> h2;
			cout << "HomeWork 3 Grade: ";
			cin >> h3;
			cout << "Project Grade: ";
			cin >> proj;
			cout << "Attendance Grade: ";
			cin >> att;
			examAvg = file.calcExamAvg(mid, finalG); //find the exam avearge
			hwAvg = file.calcHWAvg(h1, h2, h3); //find the homework average
			overAllGrade = file.calcWghtAvg(hwAvg, examAvg, proj, att);//weighted grade 
			letGrade = file.calcLettergrade(overAllGrade); //convert to a letter grade
			if (file.dataAdd(stuName, stuID,  stuYear,  dep,  letGrade,  mid,  finalG,  //adds it to the file using the object function. Returns an int or 1 to let user know it was succefuly 
								examAvg,  h1,  h2,  h3,  hwAvg, proj,  att , overAllGrade) == 1) {
				cout << "\nYou have succfully added information for " << stuName << " into the file\n";
				cout << file.displayContents();
			} else { //if it does not return a one, it will let the user know that it failed
				cout << "\nThere was no luck adding " << stuName << " into the database";
			}
		}
		if (Uinput == 2) { //display the file
		cout << "\n\n\n";
		cout << file.displayContents(); //calls a function to return a string to print out contents of file
		cout << "\n\n";
		}
		if (Uinput == 4) {  //change the current file or create a new one
			cin.getline(trash, 2); //clear the console for correct input
			file = newFile(); //calls function to change or create the file
		}
		if (Uinput == 1) { //search for a term 
			cin.getline(trash, 2);
			string term;
			cout << "\nPlease Enter the Term you would like to search: ";
			getline(cin,term); 
			cout << "The results for your search are: \n\n";
			cout << setw(40)<< file.dataSearch(term);
			cout << "\n\n";
		}
	}
}

/**
 * @brief 
 * @return Returns a StudentFile object that holds an object called Student File
 * Prompts the user to enter a file name, looks for the file to see if it exists, then creates it or opens it. This is done using StudentFile object
 */
StudentFile newFile() {
	int getFileName = 1; 
	string fileName; 
	string correctInput;
	StudentFile* classInfo; //the now opened and fully pointerized file
	while(getFileName == 1) { 
		cout << "Please enter the file name you want to work with: ";
		getline(cin, fileName);
		cout << "\n\nYou will be working with the file called: " << fileName << "\n"; 
		cout << "Is this correct? Y or N? ";
		getline(cin, correctInput); 
		if(correctInput == "y" or correctInput == "Y") {
			getFileName = 0; 
		}
		else if (correctInput == "n" or correctInput == "N") {
			cout << "\nTry and correct your filename\n";
		}
		else {
			cout << "\nI don't understand what your asking, I guess enter your file name again\n";
		}
	}
	
	StudentFile file(fileName); // creates an object called file giving it a filename
	if(file.testFile() == 1) { //check if the file exists
		cout << "\n\nThis file exists here are the contents:\n\n";
		cout << file.displayContents();
		cout << "\n\n";
	} else if (file.testFile() == 0) { //check if file does exist, if not then creat it 
		cout << "I do not see this file, creating it now:";
		if(file.fileCreation() == 0) { //create file ,check if failed and let user knpw
			cout <<  "\n\nFile creation failed\n\n";
		} else if (file.fileCreation() == 1) {  //create file check if it was suecful and let user know
			cout << "\n\nYour file has been succesfully created succesfully!\n\n";
			cout << "Heres what it looks like so far:\n\n";
			file.displayContents(); //display the current file to the user
			cout << "\n\n";
		} else {
			cout << "\n\nAn error has occured\n\n"; //if not... well something happend let the user know ther was an error
		}
	}
	classInfo = &file;
	return *classInfo; //return the file
}