#ifndef SOCIAL_H
#define SOCIAL_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;

// colors for styling the project
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"

#define STOP 0 
#define MAX_POSTS 100
#define MAX_COMMENTS 100

// structure for a post
typedef struct POST_ {
    string post_content;
    int like = 0;
    string comment[MAX_COMMENTS];
    int commentCnt = 0;
    void createPost();
    void viewPost();
} POST;

// structure for user 
typedef struct USER_ {
    string fullname;
    int age;
    string email;
    string cnic;
    string contact;
    string state;
    string password;
    string gender;
    int followers = 0;
    int following = 0;
    POST post[MAX_POSTS];
    int postCnt = 0;
    void signup(); // takes user credentials as input
    void extractDetailsFromCnic(const string&);  // extracts details from cnic
} USER;


const int MAX_SIZE = 100;
string Admin[MAX_SIZE][2]; // saves username and password
int adminCnt = 0;

const int MAX_USERS = 100;
USER user[MAX_USERS]; // max users

string fullName; string Gender; int Age; string State;

// validating the cnic
bool validateCnic(const string&);
// validating contact number
bool validateContact(const string&);
//validating password
bool validatePassword(const string&);
// validating email address
bool validateEmail(const string&);
// function for decorate
void decorationBar(const string&);
//password instructions
void passwordInstructions();
// takes login credentials from user
void login(string &, string &); 
// checks if email already exist in Admin.txt or not
bool checkExistingEmail(const string&);
// extracts words from a line
void extractWordsFromLine(string line, string words[], int&);
// displays logo
void displayAppLogo();
// get the current time 
string getCurrentTime();
// menu
void menu(void);
// shows user profile
void showProfile(USER *user);
// converts lowercase string to uppercase string
string toUpperCase(const string& str);

bool validateCnic(const string &cnic) {
    for(int i = 0; i < cnic.length(); ++i) {
        if(!(cnic[i] >= '0' && cnic[i] <= '9')) {
            return false;
        }
    }
    return cnic.length() == 13;
}

bool validatePassword(const string &password) {
    bool has_special = false, has_upper = false, has_lower = false, has_digit = false;

    // password length must be greater than 8
    if(password.length() < 8) {
        return false;
    }

    // checks every character of a password 
    for(int i = 0; i < password.length(); i++) {
        if(password[i] >= 'A' && password[i] <= 'Z') {
            has_upper = true;
        } else if(password[i] >= 'a' && password[i] <= 'z') {
            has_lower = true;
        } else if(password[i] >= '0' && password[i] <= '9') {
            has_digit = true;
        } else {
            has_special = true;
        }
    }

    return has_digit && has_lower && has_special && has_upper;
}


bool validateContact(const string &contact) {
    // checks every character of a contact
    for(int i = 0; i < contact.length(); i++) {
        if(!(contact[i] >= '0' && contact[i] <= '9')) {
            return false;
        }
    }
    return contact.length() == 11;
}


bool validateEmail(const string &email) {
    // checks if email ends with "@gmail.com"
    for(int i = 0; i <= email.length() - 10; ++i) {
        if(email.substr(i, 10) == "@gmail.com") {
            return true;
        }
    }
    return false;
}

// takes credentials of user
void USER::signup() {

    string line = "----------------| Sign Up Menu | ------------------";    
    cout << GREEN;
    decorationBar(line);
    cout << BLUE; // text color will change to Blue
    cout << "\tEnter your full name: ";
    cin.ignore();
    getline(cin, fullname);
    // validating email address
    cout << "\tEnter your email:     ";
    cin >> email;

    while(!validateEmail(email)) {
        cout << "\tTry again!:           ";
        cin >> email;
    }

    if(checkExistingEmail(email)) {
        cout << '\n' << RED;
        line = "Email already exists! Try a differnt one!";
        decorationBar(line);
        do {
            cout << "\tTry again!:           ";
            cin >> email;
        } while(!validateEmail(email));
    } 

    passwordInstructions(); // shows passowrd Instructions
    cout << BLUE << "\tEnter your password:  ";
    cin >> password;

    while(!validatePassword(password)) {
        cout << "\tTry again!:           ";
        cin >> password;
    }

    string confirm_password;
    cout << "\tConfirm password:     ";
    cin >> confirm_password;

    while(confirm_password != password) {
        cout << "\tTry again!:           ";
        cin >> confirm_password;
    }void displayAppLogo();


    cout << "\tEnter your cnic:      ";
    cin >> cnic;

    while(!validateCnic(cnic)) {
        cout << "\tTry again!:           ";
        cin >> cnic;
    }

    extractDetailsFromCnic(cnic); // fucntion for extracting data from cnic

    cout << "\tEnter your age:       ";
    cin >> age;

    while(!(age > 0 && age < 100)) {
        cout << "\tTry again!:           ";
        cin >> age;
    }
    
    cout << "\tEnter your contact:   ";
    cin >> contact;

    while(!validateContact(contact)) { // function to check number's length should be correct
        cout << "\tTry again!:           ";
        cin >> contact;
    }

    fullName = fullname; Age = age; State = state; Gender = gender; 

    //saves email and password in Admin array
    Admin[adminCnt][0] = email;
    Admin[adminCnt][1] = password;
    adminCnt++;
    
    system("clear");

    cout << GREEN;
    line = "---------| Account Created Successfully! | --------";
    decorationBar(line);

    showProfile(&user[adminCnt - 1]);
}

void login(string &email, string &password) {
    string line = "-----------------| Login Menu | -------------------";
    decorationBar(line);
    cout << BLUE;
    cout << "\tEnter your email:     ";
    cin >> email;
    cout << "\tEnter your password:  ";
    cin >> password;

    bool found = false;

    for (int i = 0; i < MAX_USERS; ++i) {
        if (Admin[i][0] == email && Admin[i][1] == password) {
            showProfile(&user[i]);
            found = true;
            break;  // Exit the loop once a matching user is found
        }
    }

    if (!found) {
        line =  "-| Incorrect username or password. Try again! |-";
        cout << RED;
        decorationBar(line);
    }
}



void decorationBar(const string &line) {
    cout << "\n---------------------------------------------------\n";
    cout << line << '\n';
    cout << "---------------------------------------------------\n\n" << BLUE;
}


void USER:: extractDetailsFromCnic(const string &cnic) {
    // last digit of cnic shows gender if odd then the person is male otherwise female
    if((cnic[12] - '0') & 1) { 
        gender = "Male";
    } else {
        gender = "Female";
    }

    //first digit of cnic shows state of Pakistan
    switch (cnic[0] - '0')
    {
    case 1:
        state = "KPK";
        break;
    case 2:
        state = "FATA";
        break;
    case 3:
        state = "Punjab";
        break;
    case 4:
        state = "Sindh";
        break;
    case 5:
        state = "Balochistan";
        break;
    case 6:
        state = "Islamabad";
        break;
    case 7:
        state = "Gilgit Baltistan"; 
        break;
    default:
        break;
    }
}



void passwordInstructions() {
    cout << RED;
    cout << "\n---------------------------------------------------\n"
         << "--| Password must be 8 characters long          |--\n" 
         << "--| Password must have one uppercase character  |--\n" 
         << "--| Password must have one lowercase character  |--\n" 
         << "--| Password must have one special character    |--\n"
         << "---------------------------------------------------\n\n" << BLUE; // reset to Blue color
}


// checks if email already exist in Admin.txt or not
bool checkExistingEmail(const string &email) {

    for(int i = 0; i < adminCnt; i++) {
        if(Admin[i][0] == email) {
            return true;
        }
    }
    return false;
}


// extracts words from a line
void extractWordsFromLine(string line, string words[], int &totalWords) {
    int idx = 0;
    for(int i = 0; i < line.length(); ++i) {
        if(line[i] != ' ') {
            words[idx] += line[i];
        } else {
            idx++;
        }
    }
    totalWords = idx;
}


// displays app logo
void displayAppLogo() {
    cout << YELLOW;
    cout << "\n\t\t-|-----------------------------------------------|-\n";
    cout << "\t\t-|       MAQSOOD'S SOCIAL APP SIMULATOR!         |-\n";
    cout << "\t\t-|-----------------------------------------------|-\n\n" << BLUE;
}



// creates a post
void POST::createPost() {
    string line = "---------------| Create a post | ------------------";

    cout << YELLOW;
    decorationBar(line);
    cout << RED;
    cout << "---------------------------------------------------\n"
         << "------| Time: " << getCurrentTime() << "  [ Enter '#' to end ] |-----\n"
         << "---------------------------------------------------\n" << BLUE;

    string usrInput;
    
    getline(cin, usrInput); 
    while(usrInput != "#") {
        post_content = post_content + " " + usrInput;
        getline(cin, usrInput); 
    }

    system("clear"); // clears the screen
    line = "----------| Post Created Successfully! | ----------";
    cout << GREEN;
    decorationBar(line);
}


void POST::viewPost() {
    
    string choice;
    int totalWords;
    string words[200];
    string line = "--------------| Displaying a post | ---------------";
    
    displayAppLogo();
    cout << GREEN;
    decorationBar(line);

    cout << YELLOW;
    cout << "----------------------------------------------------\n";
    extractWordsFromLine(post_content, words, totalWords); // extracting words from post_content
    
    for(int i = 0; i < totalWords; i++) {
        if(i > 0 && i % 10 == 0) {
            cout << '\n';
        }
        cout << words[i] << ' ';
    }

    cout << "\n----------------------------------------------------\n";
    cout << "( Like = " << like << " )          ( Comment = " << commentCnt << " )\n";
    cout << "----------------------------------------------------\n";
    cout << "\t1 for Like\n\t2 for comment\n\t3 for view comments\n\t(0 for quit): ";
    cin >> choice;

    if(choice == "1") {
        cout << "Like added\n";
        like++;
    } else if(choice == "2") {
        cin.ignore();
        cout << "Type comment: ";
        getline(cin, comment[commentCnt++]);
    } else if(choice == "3") {
        cout << '\n';
        for(int i = 0; comment[i] != "\0"; ++i) {
            cout << i + 1 << ": " << comment[i] << '\n';
        }
    } else if(choice == "0"){
        return;
    }
}

// gets the current time
string getCurrentTime() {
   
    auto currentTime = chrono::system_clock::now();
    time_t currentTime_t = chrono::system_clock::to_time_t(currentTime);
    tm* currentTime_tm = localtime(&currentTime_t);
    return to_string(currentTime_tm->tm_hour) + ":" + to_string(currentTime_tm->tm_min) + ":" + to_string(currentTime_tm->tm_sec);
}


// menu 
void menu(void) {
    system("clear"); // clears the screen
    int choice;
    string user_email, user_password;

    while(true) {
        displayAppLogo();
        cout << "\n\t1 - for Login\n\t2 - for Signup\n\t(0 for quit): ";
        cin >> choice;

        while(!(choice >= 0 && choice <= 2)) {
            displayAppLogo();
            cout << "\n\t1 - for Login\n\t2 - for Signup\n\t(0 for quit): ";
            cin >> choice;
        }

        if(choice == 1) {
            login(user_email, user_password);
            system("clear"); // clears the screen
        } 
        else if(choice == 2) {
            user[adminCnt++].signup();
        } 
        else {
            system("clear");
            string line =  "---------------| Have a GOOD DAY :) |--------------";
            cout << YELLOW;
            decorationBar(line);
            return;
        }

    }
}

// profile of user
void showProfile(USER *user) {
    
    while (true) {
        system("clear");
        displayAppLogo();

        string line = "-----------------| PROFILE MENU :) |---------------";
        cout << YELLOW;
        decorationBar(line);
        int choice;

        cout << '\t' << toUpperCase(fullName) << "\tBorn in " << (2024 - Age) << " (" << Age << " years old)\n";
        cout << "\tFrom " << State << "\tGender : " << Gender << '\n';

        cout << "\n\t1 - for create post\n\t2 - for view posts\n\t(0 to quit): ";
        cin >> choice;

        while (!(choice >= 0 && choice < 3)) {
            displayAppLogo();
            cout << "\n\t1 - for create post\n\t2 - for view posts\n\t(0 to quit): ";
            cin >> choice;
        }

        switch (choice) {

            case 0:
                system("clear"); // clears the screen
                return;

            case 1:
                if (user->postCnt < MAX_POSTS) {
                    user->post[user->postCnt++].createPost();
                }
                break;

            case 2:
                if (user->post->post_content.empty()) {
                    line = "--------| You haven't created a post yet! |---------";
                    cout << RED;
                    decorationBar(line);
                    break;
                }
                for (int i = 0; i < user->postCnt; ++i) {
                    user->post[i].viewPost();
                }
                break;

            default:
                break;
        }
    }
}


//converts string to uppercase
string toUpperCase(const string& str) {
    string result = str;

    for (char& c : result) {
        if (islower(c)) {
            c = toupper(c);
        }
    }

    return result;
}


#endif