#include <iostream>
#include <cstdio>
#include <windows.h>
#include <process.h>
#include<limits>
#include<vector>

using namespace std;
int n; // количество кусков - норма
const int m = 1; // количество производителей
int k;  // количество потребителей
HANDLE hMutex;
int num = 0;
int gum = 0;

DWORD WINAPI Povar(void *arg) {
    while (true) {
        WaitForSingleObject(hMutex, INFINITE);
        printf(" I am a Cook \n ");
        if (n == 0) {
            printf(" Cook is cooking \n");
            n = 5;
            printf("Cook made %d pieces of meat\n", n);
        }
        printf(" Now the pot has some meat, so I can go to sleep \n");

        Sleep(1000);
        ReleaseSemaphore(hMutex, 1, nullptr);
        Sleep(1000);
    }
};


DWORD WINAPI Kanibal(void *arg) {
    while (true) {
        WaitForSingleObject(hMutex, INFINITE);

        if (n == 0) {
            printf(" Kanibal  %d isn't eating, the pot is empty \n ", gum % k + 1);
            gum++;
            Sleep(1000);
        } else {
            printf(" Kanibal number %d eats a piece of meat = %d\n", num % k + 1, n);
            n--;
            num++;
            gum = num;
            Sleep(1000);

            //return 0;
        }

        ReleaseSemaphore(hMutex, 1, nullptr);
        Sleep(1000);
    }

    return 0;
};

int checkInput(const string &message) {
    while (true) {
        cout << message;
        int num1;
        cin >> num1;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "You should enter a number [15; 100]" << endl;
        } else if (num1 < 15 || num1 > 100) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "You should enter a number [15; 100]" << endl;
        } else
            return num1;
    }
}

int checkInput1(const string &message) {
    while (true) {
        cout << message;
        int num1;
        cin >> num1;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "You should enter a number [1; 100]" << endl;
        } else if (num1 < 1 || num1 > 100) {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "You should enter a number [1; 100]" << endl;
        } else
            return num1;
    }
}

int main() {
    cout << "Hi, the lunch will last for 2 minuets\n" << endl;
    k = checkInput("Enter number of kanibals [15; 100]: ");
    n = checkInput1("Enter number of slices of intellectual meat [1; 100]): ");
    cout << "\n There are " << n << " kanibals and " << m << " slices of meat\n and only one povar\n" << endl;
    auto *dwThreadId = new DWORD[k + m];
    auto *hThread = new HANDLE[k + m];

    hMutex = CreateSemaphore(nullptr, 1, 1, nullptr);

    for (int j = 0; j < m; j++) {
        hThread[j] = CreateThread(nullptr, 0, &Povar, 0, 0, &dwThreadId[j]);
    }

    for (int i = m; i < k + m; i++) {
        hThread[i] = CreateThread(nullptr, 0, &Kanibal, 0, 0, &dwThreadId[i]);
    }

    WaitForMultipleObjects(11, hThread, TRUE, 120000);
    delete[] dwThreadId;
    delete[] hThread;
    return 0;
}