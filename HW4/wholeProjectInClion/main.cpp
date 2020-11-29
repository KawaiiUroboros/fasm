#include <iostream>
#include <map>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <string>

using namespace std;
map<char, string> cypherDic;

void start() {
    char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                          'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    string nums[26] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12",
                        "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26" };
    int cube;
    string temp;
    cout << "Your cypher table:\n";
    for (char & i : alphabet) {
        do {
            cube = rand() % 26;
        } while (nums[cube] == "-1");

        temp = nums[cube];
        cypherDic[i] = nums[cube];
        nums[cube] = "-1";
        cout << i << ": " << cypherDic[i] << "\n";
    }
    cout<< "enter your message\n";
}
string translate(string s) {
    string y = "";
    for (char & i : s){
        if(cypherDic.count(i)==0){
            y+=i;
        }else{
            y += cypherDic[i];}}

    return y ;
}

void run(vector<string> str) {
    string w[str.size()];
#pragma omp parallel
    {
#pragma omp for
        for (int q = 0; q < str.size(); ++q) {
            w[q] = translate(str[q]);
        }
    }
    for(int i;i< w->size();i++){
        cout<<w[i]<<"\n";
    }
}

int main() {
    cout << "Write your message. To write a new word for a line press Enter. To stop write type 'end' and press Enter.\n";
    string countStr = "start", ans = "";
    vector<string> str;
    start();
    cin >> countStr;
    while (countStr != "end") {
        str.push_back(countStr);
        cin >> countStr;
    }
    run(str);
    return 0;
}