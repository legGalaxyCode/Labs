#include<cmath>
#include<iostream>
#include<string>
using namespace std;

class Dictionary {
private:
    unsigned int count;
    string word;
    string* phrases;
    string* new_phrases;
public:
    Dictionary(unsigned int a) {
        count = a;
        count++;
        phrases = new string [count];
        cout << "Введите фразы:" << endl;
        for (int i = 0; i < (count); i++) {
            string temp;
            getline(cin, temp);
            phrases[i] = temp;
        };
        count--;
    }
    void set_word() {
        cout << "Напишите слово для поиска: ";
        cin >> word;
    }
    void get_word()const 
    {
        cout << word;
    }
    void get_elem()const 
    {
        for (int i = 0; i < count; i++) {
            cout << phrases[i] << endl;
        };
    }
    void find() 
    {
        if (word == "") {
            cout << "error" << endl;
        }
        else if (word != "") {
            for (unsigned int i = 0; i < count; i++) {
                int c = phrases[i].find(word);
                if (c == -1) {
                    continue;
                }
                else if (c != -1) {
                    unsigned int length = word.length();
                    cout << length;
                };
            };
        }
    }
    void sort_a() //length
    {

    }
    void sort_b() //alphabet
    {

    }
};

int main()
{
    setlocale(LC_ALL, "ru");
    unsigned int t;
    cout << "Введите количество фраз: ";
    cin >> t;
    Dictionary phrase(t);
    phrase.set_word();
    phrase.find();
}

