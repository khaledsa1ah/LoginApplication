// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login_header.h
// Last Modification Date: 15/5/2022
// Author1 and ID and Group: Abdulrahman Gamal 20210223
// Author2 and ID and Group: Ali Tariq 20210252
// Author3 and ID and Group: Khaled Salah 20211033
// Teaching Assistant: Eng. Yousra & Eng. Eman
#ifndef LOGIN_APPLICATION_LOGIN_APPLICATION_LIBRARY_H
#define LOGIN_APPLICATION_LOGIN_APPLICATION_LIBRARY_H
using namespace std;
struct UserProfile{
    string name,email,password,phoneNumber;
};
bool Exit = false;
map<string,UserProfile>users;
set<string>emails;
void loadUsers();
void Registration();


#endif //LOGIN_APPLICATION_LOGIN_APPLICATION_LIBRARY_H
