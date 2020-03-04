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
    unsigned int count; //всего фраз
    unsigned int new_count; //фраз без слова
    int a_count;
    int lang; //выбор языка
    string word; //слово для поиска
    string* phrases; //массив со всеми фразами
    string* new_phrases; //массив с фразами, где есть слово
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
        //count--;
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
        else if (word != "") { //баги реализации ввода рандомных символов все равно будет работать
            cout << "Нажмите 1, если фраза на английском. Нажмите 0, если фраза на русском. ";
            cin >> lang;
            if (lang == 1) {
                setlocale(LC_ALL, "eng");
                transform(word.begin(), word.end(), word.begin(), (int(*)(int))tolower);
            }
            else if (lang == 0) {
                setlocale(LC_ALL, "rus");
                transform(word.begin(), word.end(), word.begin(), (int(*)(int))tolower);
            }
            static int counter = 0;
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
                int c = phrases[i].find(word); //работает для совпадения: фраза: покакает, слово: пока, совпадение будет
                if (c == -1) {
                    continue;
                }
                else if (c != -1) {
                    new_phrases[counter] = phrases[i];
                    ++counter;
                    new_count = counter;
                    if (i == (count-1)) {
                        a_count = count - new_count;
                    }
                };
            }; 
        }
    }
    void sort_a1() //length phrases
    {
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < (count - 1); j++) {
                if (phrases[j].length() > phrases[j + 1].length()) {
                    string temp = phrases[j];
                    phrases[j] = phrases[j + 1];
                    phrases[j + 1] = temp;
                }
            }
        }
    }
    void sort_a2() //length new_phrases
    {
        for (int i = 0; i < new_count; i++) {
            for (int j = 0; j < (new_count - 1); j++) {
                if (new_phrases[j].length() > new_phrases[j + 1].length()) {
                    string temp = new_phrases[j];
                    new_phrases[j] = new_phrases[j + 1];
                    new_phrases[j + 1] = temp;
                }
            }
        }
    }
    void sort_b1() //alphabet phrases
    {
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < (count - 1); j++) {
                if (strcmp(phrases[j].c_str(), phrases[j+1].c_str()) > 0) {
                    string temp = phrases[j];
                    phrases[j] = phrases[j + 1];
                    phrases[j + 1] = temp;
                }
            }
        }
    }
    void sort_b2() //alphabet new_phrases
    {
        for (int i = 0; i < new_count; i++) {
            for (int j = 0; j < (new_count - 1); j++) {
                if (strcmp(new_phrases[j].c_str(), new_phrases[j + 1].c_str()) > 0) {
                    string temp = new_phrases[j];
                    new_phrases[j] = new_phrases[j + 1];
                    new_phrases[j + 1] = temp;
                }
            }
        }
    }
    void show_phrases()
    {
        if (lang == 1) {
            setlocale(LC_ALL, "eng");
        }
        cout << "Phrases without word:";
        for (int i = 0; i < count; i++) {
            cout << phrases[i] << endl;
        }
        cout << "Phrases with word:" << endl;
        for (int i = 0; i < new_count; i++) {
            cout << new_phrases[i] << endl;
        }
    }
    void correct_array() 
    {
        string* a_phrase = new string[a_count];
        for (int i = 0, b = 0; i < a_count, b < count; i++) {
            //final doing...
        }
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
    string* a_phrase;
    Dictionary phrase(t);

    phrase.set_word();
    phrase.find();
    phrase.sort_a1();
    phrase.sort_a2();

    phrase.show_phrases();
}

