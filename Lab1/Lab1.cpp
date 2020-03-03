#include<cmath>
#include<cctype>
#include<algorithm>
#include<iostream>
#include<string>
#include<Windows.h>
using namespace std;

//?: влияет ли регистр слова на поиск - не влияет

class Dictionary {
private:
    unsigned int count;
    unsigned int new_count;
    int lang;
    string word;
    string* phrases;
    string* new_phrases;
public:
    Dictionary(unsigned int a) {
        count = a;
        count++;
        phrases = new string [count];
        new_phrases = new string [count];
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
            cout << "Нажмите 1, если фраза на английском. Нажмите 0, если фраза на русском. ";
            cin >> lang;
            setlocale(LC_ALL, "rus");
            for (unsigned int i = 0; i < count; i++) {
                if (lang == 1) {
                    setlocale(LC_ALL, "eng");
                    transform(phrases[i].begin(), phrases[i].end(), phrases[i].begin(), (int(*)(int))tolower);
                }
                else if (lang == 0) {
                    setlocale(LC_ALL, "rus");
                    transform(phrases[i].begin(), phrases[i].end(), phrases[i].begin(), (int(*)(int))tolower);
                }
                int c = phrases[i].find(word);
                int f = phrases[i].rfind(word);
                if (c == -1) {
                    continue;
                }
                else if (c != -1) {
                    static int counter = 0;
                    new_phrases[counter] = phrases[i];
                    counter++;
                    string* a_phrases = new string[count];
                    for (int k = 0; k < count; k++) {
                        if (k = i) { a_phrases[k] = ""; };
                        a_phrases[k] = phrases[k];
                    }
                    if (i = count - 1) {
                        phrases = a_phrases;
                    }
                };
            }; 
        }
    }
    void show_phrases() 
    {
        if (lang == 1) {
            setlocale(LC_ALL, "eng");
        }
        cout << "Фразы со словом:" << endl;
        for (int i = 0; i < count; i++) {
            cout << phrases[i] << endl;
        }
        cout << "Фразы без слова:" << endl;
        for (int i = 0; i < count; i++) {
            cout << new_phrases[i] << endl;
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
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    unsigned int t;
    cout << "Введите количество фраз: ";
    cin >> t;
    Dictionary phrase(t);
    phrase.set_word();
    phrase.find();
    phrase.show_phrases();
}

