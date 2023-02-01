//Including header files
#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include <unistd.h>     //For sleep()
using namespace std;

//Cant store phone number in integer as even a long int can only store upto 9 values so we will use 
//string
//Global variables
string fname,lname,phone_num;         //firstname lastname and phone number

//Function prototyoing
void add_contact();
void search_contact();
void self_exit(); 
void help();
bool check_digits(string pn);
bool check_numbers(string pn);
bool alreadyexists();

int main()
{
    short int choice;
    system("cls");              //Clears the screen
    system("color 0A");         //Chnges the text to green keeps the backgorun black
    //07 for white and 0A for light green
    cout<<"\n\n\n\t\t\tContact Management System"<<endl;
    cout<<"\n\t1. Add contact\n\t2. Search Contact\n\t3. Help\n\t4. Exit";
    cout<<endl;
    cout<<"\t->Select your choice: ";
    cin>>choice;

    switch(choice){
        case 1:
        add_contact();
        break;
        case 2:
        search_contact();
        break;
        case 3:
        help();
        break;
        case 4:
        self_exit();
        break;
        default:
        cout<<"\n\n\t\tInvaild Input!!";
        cout<<"\n\tPress any key to continue";
        getch();            //Takes input of character and we dont have to press enter
        main();             //calling the main function
    }

    return 0;
}

void self_exit(){
    system("cls");           //Clears the screen
    cout<<"\n\n\n\t\tThank you for using !"<<endl;
    cout<<"\t\tExiting the system";
    exit(1);     //Allows us to terminate our programs exection whenever we want, without reaching
    //even before reaching return, WITH return we can only exit our program from main fucntion 
    //but exit lets us do it from anywhere 
    //1 is just a exit status not necessary(it can be either 0(success) or 1(failure),although they
    //dont mean anything)
}

void help(){
    system("cls");
    cout<<"\n\n\t\t\t\tHELP"<<endl;
    cout<<"\n\tYou are supposed to chose any option according to your wish";
    cout<<"\n\tOption 1 will let you add contacts";
    cout<<"\n\tOption 2 will let you search contacts stored in your system";
    cout<<"\n\tOption 3 will let you in on the help section";
    cout<<"\n\tOption 4 will let you exit the Contact Manager System";
    cout<<"\n\n\tYou will be redirected to main menu in 10 seconds....";
    sleep(10);
    main();
}

void add_contact(){

    //This will create a file in append mode, opened in append mode cause in deault output mode
    //it will overwrite data
    ofstream phone("number.txt",ios::app);

    system("cls");      //clearing the screen;
    cout<<"\n\n\tEnter the the first name: ";
    cin>>fname;
    cout<<"\n\tEnter the last name: ";
    cin>>lname;
    cout<<"\n\tEnter 10 digit phone number: ";
    cin>>phone_num;

    if(alreadyexists()==true){
        return;
    }

    if(check_digits(phone_num)==true){      //Checks if there are 10 digits in the number or not
        if(check_numbers(phone_num)==true){ //Check if all the chars input in string are int or not

        //stream.is_open returns wether stream is currently associated to file or not
        //returns true if file is open, flase if not
            if(phone.is_open()){
                phone<<"\n"<<fname<<" "<<lname<<" "<<phone_num;
                cout<<"\n\tContact saved successfully";
            }
            else{
                cout<<"\n\tError opening file";
            }
        }
        else{
            cout<<"\n\tPhone number must contain ONLY numbers";
        }
    }
    else{
        cout<<"\n\tA phone number must contain 10 digits";
    }
    phone.close();
    main();       //->This will work but bad practice
}

void search_contact(){
    bool found = false;
    ifstream myfile("number.txt");
    string keyword;
    cout<<"\n\tEnter a name to search: ";
    cin>>keyword;
    //while(myfile.eof()==0) could use this
    while(myfile>>fname>>lname>>phone_num){
        system("cls");
        if(keyword == fname || keyword == lname){
            cout<<"\n\n\n\t\tContact details...";
            cout<<"\n\n\t\tFirst name: "<<fname;
            cout<<"\n\t\tLast name: "<<lname;
            cout<<"\n\t\tPhone number: "<<phone_num;
            found = true;
            break;
        }
    }
    if(found==false){
        cout<<"\n\t\tNo contact found with given name found";
    }
    cout<<"\n\n\t\tYou will be redirected to main menu in 5 seconds....";
    sleep(5);
    main();  
}

bool check_digits(string pn){
    if(pn.length()==10){
        return true;
    }
    else{
        return false;
    }
}


//The ASSCI character for integers 0-9 lies between 48 and 57, so here we are type casting the
//characters '0','1'.....'9' into their ascii values annd checking if they lie between 48 and 57
bool check_numbers(string pn){
    bool check = true;
    for(int i=0;i<pn.length();++i){             
        if(!int(pn[i]>=48 && int(pn[i])<=57)){    //If they dont lie between them, then this means
            check = false;                        //that they are not integers and orignal condition
            break;                                //will give false and ! will make it true which will
        }                                         //change check's value to false
    }
    return check;
}

bool alreadyexists(){
    bool al = false;
    ifstream file("number.txt");
    string s1;
    while(file.eof()==0){
        file>>s1;
        //cout<<s1;
        if(s1 == fname || s1 == lname){
            cout<<"\n\tContact with the same name already exists";
            al = true;
            break;
        }
    }
    return al;
}