// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login_Library.cpp
// Last Modification Date: 15/5/2022
// Author1 and ID and Group: Abdulrahman Gamal 20210223
// Author2 and ID and Group: Ali Tariq 20210252
// Author3 and ID and Group: Khaled Salah 20211033
// Teaching Assistant: Eng. Yousra & Eng. Eman

#include <bits/stdc++.h>
#include <conio.h>
#include "Login Application library.h"

int mainMenu(){
    set<string>choices{"1","2","3","4"};
    string choice;
    while (!choices.count(choice)){
        cout<<"Choose the number the choice you want\n";
        cout<<"1-Register\n";
        cout<<"2-Login\n";
        cout<<"3-Change password\n";
        cout<<"4-Exit\n>>";
        cin>>choice;
    }
    return stoi(choice);
}

string encrypt(string password){
    for(auto &chr:password){
        chr = chr+1;
    }
    return password;
}

void decrypt(string &password){
    for(auto &chr:password){
        chr--;
    }
}

void loadUsers(){
    ifstream userFile("users.txt");
    while (!userFile.eof()){
        UserProfile nextUser;
        getline(userFile,nextUser.name,',');
        getline(userFile,nextUser.email,',');
        getline(userFile,nextUser.password,',');
        decrypt(nextUser.password);
        getline(userFile,nextUser.phoneNumber);
        users.insert({nextUser.name,nextUser});
        emails.insert(nextUser.email);
    }
}

void email_format(){
    cout << "Email must be in the format\n";
    cout << "alphabets or digit characters followed by @ then domain name and in the end (.com)\n";
}

void phone_number_format(){
    cout << "Phone number must be in the format\n";
    cout << "(010) or (011) or (012) or (015) + (8)digits\n";
}

void name_format(){
    cout << "User name must be in the format\n";
    cout << "only alphabetic letters or underscore(_)\n";
}

void password_format(){
    cout << "Password must be in the format\n";
    cout << "must contain at least one lower and one upper alphabetic characters and one digit and one symbol\n";
    cout << "the length of the password must be at least 8 letters\n";
}

bool validName(string &name){
    regex pattern("[a-z_A-Z]+");
    return regex_match(name,pattern);
}

bool validEmail(string &email){
    regex pattern(R"([\w]+[.]?[\w]+@[\w]+.com)");
    return regex_match(email,pattern);
}

bool validPhone(string &phone){
    regex pattern("01[0|1|2|5]{1}[0-9]{8}");
    return regex_match(phone,pattern);
}

bool validPassword(string &password){
    int specialChar=0,lowerChar=0,upperChar=0,digit=0;
    for(auto chr:password){
        if(isalpha(chr)){
            if(islower(chr)){
                lowerChar++;
            }
            else{
                upperChar++;
            }
        }
        else if(isdigit(chr)){
            digit++;
        }
        else{
            specialChar++;
        }
    }
    return specialChar*digit*upperChar*lowerChar;
}

string enterName(){
    string name;
    name_format();
    cout<<"Please enter your user name: ";
    cin>>name;
    while (!validName(name)){
        name_format();
        cout<<"Please enter a valid name: ";
        cin>>name;
    }
    return name;
}

string enterEmail(){
    string email;
    email_format();
    cout<<"Please enter your email: ";
    cin.clear(),cin.sync();
    cin>>email;
    while (emails.count(email) || !validEmail(email)){
        if(emails.count(email)){
            cout<<"This email has been taken by another user please enter a different one: ";
        }
        else{
            cout<<"Please enter a valid email: ";
        }
        email_format();
        cin>>email;
    }
    return email;
}

void coverPassword(string &password){
    char c;
    while (true){
        c = getch();
        if(c==13){
            break;
        }
        else if(c==8 && !password.empty()){
            password.pop_back();
            cout<<"\b \b";
        }
        else if(c!=8){
            cout<<'*';
            password.push_back(c);
        }
    }
    cout<<'\n';
}

string enterPassword(){
    string password;
    coverPassword(password);
    while (password.size()<8 || !validPassword(password)){
        if(password.size()<8){
            cout<<"Your password should be at least 8 character long\n";
        }
        else{
            cout<<"Wrong password format\n";
            password_format();
        }
        password="";
        cout<<"Enter your password: ";
        coverPassword(password);
    }

    string password2;
    cout<<"Please enter your password again: ";
    coverPassword(password2);
    while (password!=password2){
        cout<<"Passwords arent the same please enter your password again: ";
        coverPassword(password2);
    }
    return password;
}

void enterPhone(UserProfile &newUser){
    phone_number_format();
    cout<<"Please enter your phone number: ";
    cin>>newUser.phoneNumber;
    while (!validPhone(newUser.phoneNumber)){
        phone_number_format();
        cout<<"Please enter a valid phone number: ";
        cin>>newUser.phoneNumber;
    }
}

void addNewUser(UserProfile &newUser){
    ofstream userfile("users.txt",ios::app);
    userfile<<'\n';
    userfile<<newUser.name<<",";
    userfile<<newUser.email<<",";
    userfile<<encrypt(newUser.password)<<",";
    userfile<<newUser.phoneNumber;
    users.insert({newUser.name,newUser});
    emails.insert(newUser.email);
}

void UpdateFile(){
    ofstream userfile("users.txt",ios::out);
    for(auto &user:users){
        userfile<<user.second.name<<",";
        userfile<<user.second.email<<",";
        userfile<<encrypt(user.second.password)<<",";
        userfile<<user.second.phoneNumber<<'\n';
    }
}

void Registration(){
    UserProfile newUser;
    newUser.name = enterName();
    newUser.email = enterEmail();

    password_format();
    cout<<"Enter your password: ";
    newUser.password = enterPassword();
    enterPhone(newUser);
    addNewUser(newUser);
    cout<<"You have been registered successfully\n";
}

string login(){
    string userName;
    cout<<"Enter your username: ";
    cin>>userName;
    while (!users.count(userName) ){
        cout<<"This username is not registered\n";
        cout<<"Please enter a registered username: ";
        cin>>userName;
    }
    int trials = 2;
    string password;
    cout<<"Enter your password: ";
    coverPassword(password);
    while (users[userName].password!=password && trials!=0){
        trials--;
        cout<<"Failed login. Try again\n";
        cout<<"Enter your password: ";
        coverPassword(password);
    }
    if(trials==0){
        cout<<"You have been denied from accessing the system\n";
        return "";
    }
    cout<<"Successful login, welcome "<<userName<<endl;
    return userName;

}

void changePassword() {
    string userName = login();
    if(userName.empty()){
        return;
    }
    password_format();
    cout<<"Enter your new password: ";
    string newPassword = enterPassword();
    while(newPassword == users[userName].password)
    {
        cout << "New password cannot be the same as the old password\nPlease enter your new password\n>>";
        newPassword = enterPassword();
    }
    users[userName].password = newPassword;
    UpdateFile();
    cout<<"Your password has been changed successfully\n";
}


