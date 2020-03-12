#include<cmath>
#include<cctype>
#include<algorithm>
#include<iostream>
#include <cstdlib>
#include<string>
#include<Windows.h>
using namespace std;

//zero error need to fix
//word find case need to fix

class Dictionary {
private:
    unsigned int count = 0; //all phrases count
    unsigned int new_count = 0; //phrases without word count
    unsigned int a_count = 0; //phrases with word count
    int word_len = 0; //word length
    int lang = 0; //language settings
    string word; //word
    string* phrases; //array with all phrases
    string* new_phrases; //array with word-phrases
    string* a_phrases; //array with none word-phrases
public:
    Dictionary(unsigned int a) {
        count = a;
        count++;
        phrases = new string [count];
        new_phrases = new string [count];
        a_phrases = new string [count];
        cout << "Input the pharses: " << endl;
        for (int i = 0; i < (count); i++) {
            string temp;
            getline(cin, temp);
            phrases[i] = temp;
        };
    }
    ~Dictionary() {
        for (int i = 0; i < count; i++) {
            delete[] phrases;
        }
        for (int i = 0; i < new_count; i++) {
            delete[] new_phrases;
        }
        for (int i = 0; i < a_count; i++) {
            delete[] a_phrases;
        }
    }
    void find() 
    {
        if (word == "") {
            cout << "error" << endl;
        }
        else if (word != "") { //bugs with random symbols
            cout << "Input 1 if u use english lang. Input 0 if u use russian lang. "; // 1 - eng, 0 - rus
            cin >> lang;
            if (lang == 1) {
                setlocale(LC_ALL, "eng");
                transform(word.begin(), word.end(), word.begin(), (int(*)(int))tolower); //to lower case all phrases in eng lang
            }
            else if (lang == 0) {
                setlocale(LC_ALL, "rus");
                transform(word.begin(), word.end(), word.begin(), (int(*)(int))tolower); //to lower case all phrases in rus lang
            }
            static int counter = 0;
            static int counter2 = 0;
            setlocale(LC_ALL, "rus");
            for (unsigned int i = 0; i < count; i++) {
                int c = phrases[i].find(word);//need tolower
                if ((c != -1 && phrases[i][c + word_len] != ' ' && phrases[i].length() != word_len && phrases[i][phrases[i].length() - 1] != word[word_len - 1]) || c == -1) {
                    a_phrases[counter2] = phrases[i];
                    a_count = ++counter2;
                }
                else if (c != -1 && (phrases[i][c+word_len] == ' ' || phrases[i].length() == word_len || phrases[i][phrases[i].length()-1] == word[word_len-1])) {
                    new_phrases[counter] = phrases[i];
                    new_count = ++counter;
                };
            }; 
        }
    }
    void main_sort() //length phrases bubble
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
    void sort_a1() //length new_phrases bubble
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
    void sort_a2() //length a_phrases bubble
    {
        for (int i = 0; i < a_count; i++) {
            for (int j = 0; j < (a_count - 1); j++) {
                if (a_phrases[j].length() > a_phrases[j + 1].length()) {
                    string temp = a_phrases[j];
                    a_phrases[j] = a_phrases[j + 1];
                    a_phrases[j + 1] = temp;
                }
            }
        }
    }
    void sort_b1() //alphabet new_phrases bubble
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
    void sort_b2() //alphabet a_phrases bubble
    {
        for (int i = 0; i < a_count; i++) {
            for (int j = 0; j < (a_count - 1); j++) {
                if (strcmp(a_phrases[j].c_str(), a_phrases[j + 1].c_str()) > 0) {
                    string temp = a_phrases[j];
                    a_phrases[j] = a_phrases[j + 1];
                    a_phrases[j + 1] = temp;
                }
            }
        }
    }
    void create_array() //this shit is blaming me in my stupidity, actually dont use it
    {
        a_phrases = new string[a_count];
        for (int i = 0; i < a_count; i++) {
            int cter = 0;
            for (int j = 0; j < new_count; j++) {
                for (int k = 0; k < count; k++) {
                    if (strcmp(new_phrases[j].c_str(), phrases[k].c_str()) != 0) {
                        for (int m = 0; m < a_count; m++) {
                            if (phrases[k] != a_phrases[m]) {
                                cter++;
                                if (cter == a_count) {
                                    a_phrases[i] = phrases[k]; 
                                    cter = 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    void set_word() {
        cout << "Input the word for searching: ";
        cin >> word;
        word_len = word.length();
    }
    void get_word()const
    {
        cout << word;
    }
    void get_all_phrases()const
    {
        for (int i = 0; i < count; i++) {
            cout << phrases[i] << endl;
        };
    }
    void show_phrases()
    {
        if (lang == 1) {
            setlocale(LC_ALL, "eng");
        }
        cout << "Phrases without word:" << endl;
        for (int i = 1; i < a_count; i++) {
            cout << a_phrases[i] << " " << i << endl;
        }
        cout << "Phrases with word:" << endl;
        for (int i = 0; i < new_count; i++) {
            cout << new_phrases[i] << endl;
        }
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned int t;
    cout << "Input the count of all phrases: ";
    cin >> t;
    Dictionary* dicts;
    dicts = new Dictionary(t);

    dicts->set_word();
    dicts->find();

    int in;
    int a_in;
    cout << "Phrases with word will sort by: 1 - lenght, 2 - alphabetical order: "; cin >> in; // 1 - len, 2 - alph
    if (in == 1) {
        dicts->sort_a1();
    }
    else if (in == 2) {
        dicts->sort_b1();
    }
    cout << "Phrases without word will sort by: 1 - length, 2 - alphabetical order: "; cin >> a_in; // 1 - len, 2 - alph
    if (in == 1) {
        dicts->sort_a2();
    }
    else if (in == 2) {
        dicts->sort_b2();
    }

    dicts->show_phrases();
}