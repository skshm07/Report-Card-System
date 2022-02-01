 #include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class student
{
 int rollno;
 char name[50];
 int physics_marks, chemisty_marks, maths_marks, english_marks, cse_marks;
 double percent;
 char grades;
 void calculate(); //function to calculate grades
public:
 void getdata(); //function to accept data from user
 void showdata() const; //function to show data on screen
 void showTable() const;
 int retrollno() const;
}; //class ends here


void student::calculate()
{
 percent=(physics_marks+chemisty_marks+maths_marks+english_marks+cse_marks)/5.0;
 if(percent>=60)
 grades='A';
 else if(percent>=50)
 grades='B';
 else if(percent>=33)
 grades='C';
 else
 grades='F';
}

void student::getdata()
{
 cout<<"\nEnter The roll number of student ";
 cin>>rollno;
 cout<<"\n\nEnter The Name of student ";
 cin.ignore();
 cin.getline(name,50);
 cout<<"\nEnter The marks in physics out of 100 : ";
 cin>>physics_marks;
 cout<<"\nEnter The marks in chemistry out of 100 : ";
 cin>>chemisty_marks;
 cout<<"\nEnter The marks in maths out of 100 : ";
 cin>>maths_marks;
 cout<<"\nEnter The marks in english out of 100 : ";
 cin>>english_marks;
 cout<<"\nEnter The marks in computer science out of 100 : ";
 cin>>cse_marks;
 calculate();
}

void student::showdata() const
{
 cout<<"\nRoll number of student : "<<rollno;
 cout<<"\nName of student : "<<name;
 cout<<"\nMarks in Physics : "<<physics_marks;
 cout<<"\nMarks in Chemistry : "<<chemisty_marks;
 cout<<"\nMarks in Maths : "<<maths_marks;
 cout<<"\nMarks in English : "<<english_marks;
 cout<<"\nMarks in Computer Science :"<<cse_marks;
 cout<<"\npercentcentage of student is  :"<<percent;
 cout<<"\ngrades of student is :"<<grades;
}

void student::showTable() const
{
 cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<physics_marks<<setw(4)<<chemisty_marks<<setw(4)<<maths_marks<<setw(4)
 <<english_marks<<setw(4)<<cse_marks<<setw(8)<<percent<<setw(6)<<grades<<endl;
}

int  student::retrollno() const
{
 return rollno;
}

void write_student(); //write the record in binary file
void display_all(); //read all records from binary file

 

void display_sp(int); //accept rollno and read record from binary file
void modifyStudent(int); //accept rollno and update record of binary file
void deleteStudent(int); //accept rollno and delete selected records from binary file
void classResult(); //display all records in tabular format from binary file
void result(); //display result menu
void intro(); //display welcome screen
void entry_menu(); //display entry menu on screen

int main()
{
 char ch;
 cout.setf(ios::fixed|ios::showpoint);
 cout<<setprecision(2); // program outputs decimal number to two decimal places
 intro();
 do
 {
 system("cls");
 cout<<"\n\n\n\tMAIN MENU";
 cout<<"\n\n\t01. RESULT MENU";
 cout<<"\n\n\t02. ENTRY/EDIT MENU";
 cout<<"\n\n\t03. EXIT";
 cout<<"\n\n\tPlease Select Your Option (1-3) ";
 cin>>ch;
 switch(ch)
 {
 case '1': result();
 break;
 case '2': entry_menu();
 break;
 case '3':
 break;
 default :cout<<"\a";
 }
    }while(ch!='3');
 return 0;
}

void write_student()
{
 student stuu;
 ofstream outFile;
 outFile.open("student.dat",ios::binary|ios::app);
 stuu.getdata();
 outFile.write(reinterpret_cast<char *> ( &stuu), sizeof(student));
 outFile.close();
     cout<<"\n\nStudent record Has Been Created ";
 cin.ignore();
 cin.get();
}

void display_all()
{
 student stuu;
 ifstream inFile;
 inFile.open("student.dat",ios::binary);
 if(!inFile)
 {
 cout<<"File could not be open !! Press any Key...";
 cin.ignore();
 cin.get();
 return;
 }
 cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
 while(inFile.read(reinterpret_cast<char *> ( &stuu), sizeof(student)))
 {
 stuu.showdata();
 cout<<"\n\n====================================\n";
 }
 inFile.close();
 cin.ignore();
 cin.get();
}

void display_sp(int n)
{
 student stuu;
 ifstream inFile;
 inFile.open("student.dat",ios::binary);
 if(!inFile)
 {
 cout<<"File could not be open !! Press any Key...";
 cin.ignore();
 cin.get();
 return;
 }
 bool flag=false;
 while(inFile.read(reinterpret_cast<char *> ( &stuu), sizeof(student)))
 {
 if (stuu.retrollno()==n)
 {
     stuu.showdata();
  flag=true;
 }
 }
 inFile.close();
 if(flag==false)
 cout<<"\n\nrecord not exist";
 cin.ignore();
 cin.get();
}

void modifyStudent(int n)
{
 bool found=false;
 student stuu;
 fstream File;
 File.open("student.dat",ios::binary|ios::in|ios::out);
 if(!File)
 {
 cout<<"File could not be open !! Press any Key...";
 cin.ignore();
 cin.get();
 return;
 }
     while(!File.eof() && found==false)
 {

 File.read(reinterpret_cast<char *> ( &stuu), sizeof(student));
 if (stuu.retrollno()==n)
 {
 stuu.showdata();
 cout<<"\n\nPlease Enter The New Details of student"<<endl;
 stuu.getdata();
      int pos=(-1)*static_cast<int>(sizeof (stuu));
      File.seekp(pos,ios::cur);
      File.write(reinterpret_cast<char *> ( &stuu), sizeof(student));
      cout<<"\n\n\t Record Updated";
      found=true;
 }
 }
 File.close();
 if(found==false)
 cout<<"\n\n Record Not Found ";
 cin.ignore();
 cin.get();
}

void deleteStudent(int n)
{
 student stuu;
 ifstream inFile;
 inFile.open("student.dat",ios::binary);
 if(!inFile)
 {
 cout<<"File could not be open !! Press any Key...";
 cin.ignore();
 cin.get();
 return;
 }
 ofstream outFile;
 outFile.open("Temp.dat",ios::out);
 inFile.seekg(0,ios::beg);
 while(inFile.read(reinterpret_cast<char *> ( &stuu), sizeof(student)))
 {
 if (stuu.retrollno()!=n)
 {
 outFile.write(reinterpret_cast<char *> ( &stuu), sizeof(student));
 }
 }
 outFile.close();
 inFile.close();
 remove("student.dat");
 rename("Temp.dat","student.dat");
 cout<<"\n\n\tRecord Deleted ..";
 cin.ignore();
 cin.get();
}

void classResult()
{
 student stuu;
 ifstream inFile;
 inFile.open("student.dat",ios::binary);
 if(!inFile)
 {
 cout<<"File could not be open !! Press any Key...";
 cin.ignore();
 cin.get();
 return;
 }
 cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
 cout<<"=========================================================================\n";
 cout<<"R.No         Name                   P   C   M   E   CS    %age    grades"<<endl;

 

 cout<<"=========================================================================\n";
 while(inFile.read(reinterpret_cast<char *> ( &stuu), sizeof(student)))
 {
 stuu.showTable();
 }
 cin.ignore();
 cin.get();
 inFile.close();
}

void result()
{
 char ch;
 int rno;
 system("cls");
 cout<<"\n\n\n\tRESULT MENU";
 cout<<"\n\n\n\t1. Class Result";
 cout<<"\n\n\t2. Student Report Card";
 cout<<"\n\n\t3. Back to Main Menu";
 cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
 cin>>ch;
 system("cls");
 switch(ch)
 {
 case '1' : classResult(); break;
 case '2' : cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
 display_sp(rno); break;
 case '3' : break;
 default: cout<<"\a";
 }
}

void intro()
{
 cout<<"\n\n\n\t\t WELCOME TO STUDENT REPORT CARD PROJECT";
 cout<<"\n\n\n\tPress Enter To Continue\n\n";
 
 cin.get();
}

void entry_menu()
{
 char ch;
 int num;
 system("cls");
 cout<<"\n\n\n\tENTRY MENU";
 cout<<"\n\n\t1.CREATE STUDENT RECORD";
 cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
 cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
 cout<<"\n\n\t4.MODIFY STUDENT RECORD";
 cout<<"\n\n\t5.DELETE STUDENT RECORD";
 cout<<"\n\n\t6.BACK TO MAIN MENU";
 cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
 cin>>ch;
 system("cls");
 switch(ch)
 {
 case '1': write_student(); break;
 case '2': display_all(); break;
 case '3': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
 display_sp(num); break;
 case '4': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
 modifyStudent(num);break;
 case '5': cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
 deleteStudent(num);break;
 case '6': break;
 default: cout<<"\a"; entry_menu();
 }
}
