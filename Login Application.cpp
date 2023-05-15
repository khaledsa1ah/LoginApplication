// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login_Application.cpp
// Last Modification Date: 15/5/2022
// Author1 and ID and Group: Abdulrahman Gamal 20210223
// Author2 and ID and Group: Ali Tariq 20210252
// Author3 and ID and Group: Khaled Salah 20211033
// Teaching Assistant: Eng. Yousra & Eng. Eman

#include <bits/stdc++.h>
#include "Login Application library.h"
#include "Login Application library.cpp"
using namespace std;

int main() {
    cout<<"Welcome to login App!\n";
    loadUsers();
    while (!Exit){
        int choice = mainMenu();
        switch (choice) {
            case 1:
                Registration();
                break;
            case 2:
                login();
                break;
            case 3:
                changePassword();
                break;
            default:
                Exit = true;
                break;
        }
    }
    cout<<"Thanks for using our login App!";

}
