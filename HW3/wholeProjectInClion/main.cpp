#include <iostream>
#include <map>
#include <vector>

using namespace std;
map<char, string> cypherDic;
vector<string> message;

/// функци для шифрования и вывода одной строки
/// \param count номер строки
/// \return ничего
void *toCypherPart(void *count) {
    vector<string> newline;
    string line = message[(int64_t) count];
    for (int i = 0; i < line.capacity(); ++i) {
        if (cypherDic.count(line[i]) != 0) {
            newline.push_back(cypherDic[line[i]]);
        } else {
            newline.push_back(string(1,line[i]));
        }
    }
    for (int j = 0; j < newline.capacity(); ++j) {
        cout << newline[j];
    }
    cout << "\n";
}
// класс для шифрования
class CypherCode {
public:
    //func to cypher
    vector<string> toCypher(vector<string> message) {
        if(message.empty()){
            cout<< "message is empty, by";
            return message;
        }

        cout << "Your cyphered message:\n";
        std::vector<pthread_t> threads(message.capacity()); //Создание портфеля задач
        int line;
        for (std::vector<pthread_t>::iterator it = threads.begin();
             it != threads.end(); ++it) { //Выполнение задач в портфеле

            pthread_create(&*it, NULL, toCypherPart, (void *) line);
            pthread_join((pthread_t) *it, NULL);
            ++line;
        }

    }

    //alphabet
    char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                         'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    //cypher
    string nums[26] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12",
                       "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26"};

    CypherCode() {
        int cube;
        string temp;
        //cout << "Your cypher table:\n";
        for (int i = 0; i < 26; ++i) {

            do {
                cube = rand() % 26;
            } while (nums[cube] == "-1");

            temp = nums[cube];
            cypherDic[alphabet[i]] = nums[cube];
            nums[cube] = "-1";
           //cout << alphabet[i] << ": " << temp << "\n";
        }
    }

};

int main() {
    cout << "Write your message. To write a new line press Enter. To stop write type 'end' and press Enter.\n";
    string countStr = "start";
    cin >> countStr;
    while (countStr != "end") {
        message.push_back(countStr);
        cin >> countStr;
    }
    CypherCode().toCypher(message);
    return 0;
}
