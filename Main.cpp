#include <iostream>
#include <string>

//Node class
class Node{

	public:
	int studentNum;
	int classNum;
	int grade;
	Node *SP;
	Node *CP;
	Node(int stu, int cls, Node *nextStu, Node *nextCls){
		this->studentNum = stu;
		this->classNum = cls;
		this->SP = nextStu;
		this->CP = nextCls;
	}//end Node constructor

	~Node(){
		delete this;
	}//end node deconstructor
	//Inserts an empty student node
	void quickStuInsert(Node *p, int num){
		p->SP = new Node(num, 0, NULL, NULL);
	}//end insertStudent
	//Inserts a node with a student class combo
	void classInsert(Node *p, int stu, int cls){
		p->CP = new Node(stu, cls, NULL, NULL);
	}//end classInsert
	//Inserts an empty class node
	void quickClsInsert(Node *p, int num){
		p->CP = new Node(0, num, NULL, NULL);
	}//end insertStudent

};//end Node class

//Function declerations
int viewGrade(int stu, int cls);
void menu(Node *head);
bool searchStu(Node *t, int x);
bool searchCls(Node *t, int x);
void searchStudentClass(Node *t, int stu, int cls);
void insertStudentClass(Node *start, Node *end, int stu, int cls);
void printStudents(Node *head);
void changeGrade(Node *head, int stu, int cls, int grade);

//Main program
int main(){
	//Creates the header node
	Node *head = new Node(0, 0, NULL, NULL);
	//I unfortunately didn't have time to implement the txt file reading as input for various reasons, so I instead created the nodes from the text file here
	searchStudentClass(head, 5, 153);
	searchStudentClass(head, 5, 203);
	searchStudentClass(head, 10, 354);
	searchStudentClass(head, 2, 354);
	searchStudentClass(head, 3, 599);
	searchStudentClass(head, 5, 439);
	searchStudentClass(head, 2, 223);
	searchStudentClass(head, 7, 448);
	searchStudentClass(head, 8, 559);
	searchStudentClass(head, 8, 478);
	//Runs the menu
	menu(head);	
	return 0;
}//end main

void changeGrade(Node *head, int stu, int cls){
	bool keepGoing2 = true;
	bool keepGoing = true;
	std::cout << "Enter the new grade value: ";
	int choice;
        std::cin >> choice;
	while(keepGoing){
		if(head->studentNum == stu){
			while(keepGoing2){
				if(head->classNum == cls){
					head->grade = choice;
					std::cout << "Successfully changed the grade" << std::endl;
					keepGoing2 = false;
				}//end if
				else if(head->CP == NULL){
					std::cout << "Student not in class" << std::endl;
					keepGoing2 = false;
				}//end else if
				else{
					head = head->CP;
				}//end else	
			}//end while
			keepGoing = false;
		}//end if
		else if(head->SP == NULL){
			std::cout << "Student doesn't exist" << std::endl;
			keepGoing = false;
		}//end else if
		else{
			head = head->SP;
		}//end else
	}//end while
}//end changeGrade

int viewGrade(Node *head, int stu, int cls){
	bool keepGoing2 = true;
	bool keepGoing = true;
	while(keepGoing){
		if(head->studentNum == stu){
			while(keepGoing2){
				if(head->classNum == cls){
					return head->grade;
				}//end if
				else if(head->CP == NULL){
					std::cout << "Student not in class" << std::endl;
					return -1;
				}//end else if
				else{
					head = head->CP;
				}//end else
			}//end while
		}//end if
		else if(head->SP == NULL){
			std::cout << "Student doesn't exist" << std::endl;
			return -1;
		}//end else if
		else{
			head = head->SP;
		}//end else
	}//end while
	return -1;
}//end viewGrade

//Takes a starting node, an node to be inserted, a student number and a class number.
void insertStudentClass(Node *start, Node *end, int stu, int cls){
	bool keepGoing = true;
	bool keepGoing2 = true;
	//std::cout << "Inserting Student into class list" << std::endl;
	while(keepGoing){
		//If the current node is the class number, then we move on to the second loop
		if(start->classNum == cls){
			//std::cout << "Found Class" << std::endl;
			while(keepGoing2){
				//If the the student is already in the class student list, then we don't need to link it
				if(start->studentNum == stu){
					//std::cout << "Student is already in this class!" << std::endl;
					keepGoing2 = false;
				}//end else if
				//If we don't find the student in the list, then we set the student pointer of the current node to the inner node we created earlier
				else if(start->SP == NULL){
					start->SP = end;
					//std::cout << "Class now has the student!" << std::endl;
					keepGoing2 = false;
				}//end if
				//If not found and not null, then move to the next pointer
				else{
					start=start->SP;
				}//end else
			}//end while
			keepGoing = false;
		}//end if
		//If the class list is empty, then we need to add the class to the list
		else if(start->CP == NULL){
			//std::cout << "Class not found, inserting class" << std::endl
			//Adds the class to the list, then moves the pointer to the new class so the first if statement will execute immediately
			start->quickClsInsert(start, cls);
			start=start->CP;
		}//end else if
		//If not found and not null, then move to the next class node
		else{
			start=start->CP;
		}//end else
	}//end while
}//end insertStudentClass


void searchStudentClass(Node *t, int stu, int cls){
	bool keepGoing = true;
	bool keepGoing2 = true;
	//start should be the head, so we assign it to t so we can use head later
	Node *start = t;
	while(keepGoing){
		//If the student is found, then we keep this pointer and move to the inner loop
		if(t->studentNum == stu){
			//std::cout << "Found Student" << std::endl;
			while(keepGoing2){
				//If the student has the class num in it's class list, this runs
				if(t->classNum == cls){
					//std::cout << "Student is in class!" << std::endl;
					//Will double check that the class the student is enrolled in is linked to the classes list
					insertStudentClass(start, t, stu, cls);
					keepGoing2 = false;
				}//end if
				//If the class pointer is null, that means the student is not in the class, so we insert them into the class
				else if(t->CP == NULL){
					//std::cout << "Student not in class. Adding the student to the class" << std::endl;
					//Creates the inner node. The class pointer of the student will point to this node.
					t->classInsert(t, stu, cls);
					t = t->CP;
					//std::cout << "Completed double insert";
					//Now that an inner node has been created for the student, link it to the class list as well
					insertStudentClass(start, t, stu, cls);
					keepGoing2 = false;
				}//end else if
				//If not null and not found, then move to the next class in the list
				else{
					t=t->CP;
				}//end else
			}//end while
			keepGoing = false;
		}//end if
		//If the student pointer is NULL, then we need to insert a blank student
		else if(t->SP == NULL){
			//std::cout << "Student not found, inserting student" << std::endl;
			t->quickStuInsert(t, stu);
			//Sets the pointer to the new blank student, so the first if statement will immediately trigger
			t=t->SP;
		}//end else if
		//If not null and not found, then move to the next student
		else{
			t=t->SP;
		}//end else
	}//end while
}//end searchStudentClass

//Will print all the classes every student is taking. Same logic as printStudents
void printClasses(Node *head){
	bool keepGoing = true;
	bool keepGoing2 = true;
	Node *cls;
	Node *stu = head->SP;
	while(keepGoing){
		if(stu->CP == NULL){
			std::cout << "Student #" << stu->studentNum << " isn't in any classes" << std::endl;
		}//end if
		else{
			keepGoing2 = true;
			cls = stu->CP;
			std::cout << "Student #" << stu->studentNum << ": Classes ";
			while(keepGoing2){
				std::cout << cls->classNum << ", ";
				if(cls->CP == NULL){
					keepGoing2 = false;
					std::cout << ";" << std::endl;
				}//end if
				else{
					cls = cls->CP;
				}//end else
			}//end while
		}//end else
		if(stu->SP == NULL){
			std::cout << "End of students" << std::endl;
			keepGoing =false;
		}//end if
		stu = stu->SP;
	}//end while
}//end printClasses

//Will print all the students in every class
void printStudents(Node *head){
	bool keepGoing = true;
	bool keepGoing2 = true;
	Node *cls;
	Node *stu;
	cls = head->CP;
	while(keepGoing){
		//If the Student Pointer for this class is null, then say there are no students in the class
		if(cls->SP == NULL){
			std::cout << "Class #" << cls->classNum << " has no students enrolled" << std::endl;
		}//end if
		//There is a student in Studetn Pointer
		else{
			//Takes the current class and sets it to stu pointer.
			keepGoing2 = true;
			stu = cls->SP;
			std::cout << "Class #" << cls->classNum << ": Students ";
			//Will keep going until student pointer points to a null. Will print the num of every student. Each iteration moves the pointer to the next student pointer
			while(keepGoing2){
				std::cout << stu->studentNum << ", ";
				if(stu->SP == NULL){
					keepGoing2 = false;
					std::cout << ";" << std::endl;
				}//end if
				else{
					stu = stu->SP;
				}//end else
			}//end while
		}//end else
		//When the last class is reached, end the loop
		if(cls->CP == NULL){
			std::cout << "End of classes" << std::endl;
			keepGoing = false;
		}//end else if
		//Since the final class might still have data, do all checks BEFORE changing the pointer value
		cls = cls->CP;
	}//end while
}//end printStudents

void menu(Node *head){
	bool keepGoing = true;
	int choice2;
	int choice;
	while(keepGoing){
		//Prints menu
		std::cout << "What would you like to do?" << std::endl;
		std::cout << "1. Add a student (no classes)" << std::endl;
		std::cout << "2. Add a class (no students)" << std::endl;
		std::cout << "3. Add a student into a class, or a class with a student" << std::endl;
		std::cout << "4. Print all students in a class" << std::endl;
		std::cout << "5. Print all classes a student is taking" << std::endl;
		std::cout << "6. Show the grade of a student" << std::endl;
		std::cout << "7. Change the grade of a student" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cin >> choice;
		//Gets the student num from user and adds the student to the list
		if(choice == 1){
			std::cout << "Enter the student number: ";
			std::cin >> choice;
			searchStu(head, choice);
			std::cout << "Successfully added new student" << std::endl;
		}//end if
		//Gets the class num from user and adds the class to the list
		else if(choice == 2){
			std::cout << "Enter the class number: ";
			std::cin >> choice;
			searchCls(head, choice);
			std::cout << "Successfully added new class" << std::endl;
		}//end else if
		//Gets the class and student num from the user and inserts it into the multilist
		else if(choice == 3){
			std::cout << "Enter the student number: ";
			std::cin >> choice;
			std::cout << std::endl;
			std::cout << "Enter the class number: ";
			std::cin >> choice2;
			searchStudentClass(head, choice, choice2);
			std::cout << "Linked a student/class combo" << std::endl;
		}//end else if
		//Prints all the students in each class
		else if(choice == 4){
			printStudents(head);
		}//end else if
		//Prints all the classes students are in
		else if(choice == 5){
			printClasses(head);
		}//end else if
		else if(choice == 6){
			std::cout << "Enter the student number: ";
			std::cin >> choice;
			std::cout << std::endl;
			std::cout << "Enter the class number: ";
			std::cin >> choice2;
			std::cout << std::endl;
			std::cout << "That student has a grade of " << viewGrade(head, choice, choice2) << " in that class" << std::endl;
		}//end else if
		else if(choice == 7){
			std::cout << "Enter the student number: ";
			std::cin >> choice;
			std::cout << std::endl;
			std::cout << "Enter the class number: ";
			std::cin >> choice2;
			std::cout << std::endl;
			changeGrade(head, choice, choice2);
		}//end else if
		//Exits the menu
		else if(choice == 0){
			keepGoing = false;
		}//end else if
		//If the input is invalid, then tell the user
		else{
			std::cout << "Please enter a valid choice" << std::endl;
		}//end else
	}//end insertSearchMenu
}//end menu

//Searches outer class list and looks for the class numbered x. Inserts the class if it's not found
bool searchCls(Node *t, int x){
	bool keepGoing = true;
	while(keepGoing){
		if(t->classNum == x){
			return true;
		}//end if
		else if(t->CP == NULL){
			//std::cout << "Not found, inserting Class" << std::endl;
			t->quickClsInsert(t, x);
			return false;
		}//end else if
		else{
			t=t->CP;
		}//end else
	}//end while
	return false;
}//end searchCls

//Searches outer student list and looks for the student numbered x. Inserts the student if it's not found
bool searchStu(Node *t, int x){
	bool keepGoing = true;
	while(keepGoing){
		if(t->studentNum == x){
			return true;
		}//end if
		else if(t->SP == NULL){
			//std::cout << "Not found, inserting Student" << std::endl;
			t->quickStuInsert(t, x);
			return false;
		}//end else if
		else{
			t=t->SP;
		}//end else
	}//end while
	return false;
}//end searchStu
