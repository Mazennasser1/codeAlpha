#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <fstream>
using namespace std;


// Function prototypes
void menu();
//void encrypt_fience();
void dencrypt_fience();

// Function for rail fence cipher encryption
void encrypt_fience(int &key){
    // Input the word to be ciphered

    string content;
    string Filename;
    string word;
    cout << "enter the file  name that you want to cipher: ";
    getline(cin, Filename);
    ifstream encryptFile(Filename);

    while(true){
        if (!encryptFile) {
            cout << "unable to open the file";
            cout <<endl<< "try again: ";
            getline(cin, Filename);
            encryptFile.open(Filename);

        }else{
            cout << "The file open successfully. "<<endl;
            break;
        }
    }
    while (true) {
        cout << "enter how many rails: ";
        cin >> key;
        cin.ignore();
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "invalid input. please enter a valid option\n";
        } else {
            break;
        }
    }
    const int originalkey =key;
    while(getline(encryptFile,word)){
        key = originalkey;
        // Calculate rail fence cipher
        int size_word = word.size();
        int rails = originalkey;
        int equation = 2 * (originalkey - 1);
        string final_word;
        for (int j = 0; j < rails; ++j) {
            int i = j;
            while (i < size_word) {
                final_word += word[i];
                i += equation;
                if (j != 0 && j != rails - 1 && i - 2 * j < size_word) {
                    final_word += word[i - 2 * j];
                }
            }
            --key;
        }

        // Convert the ciphered word to lower/upper case alternately
        int sizefinal = final_word.size();
        for (int i = 0; i < sizefinal; i++) {
            if (islower(final_word[i])) {
                final_word[i] = toupper(final_word[i]);
            } else {
                final_word[i] = tolower(final_word[i]);
            }
        }
        content+=final_word + "\n";
    }
    encryptFile.close();
    ofstream outfile(Filename);
    if (!outfile){
        cout << "error opening for writing." << endl;
        return;
    }
    outfile << content;
    outfile.close();


    cout << "your file encrypted successfully"<<endl;
    menu();
}

// Function for rail fence cipher decryption
void dencrypt_fience() {
    int key;
    string word;
    string filename;

    // Input the word to be deciphered
    cout << "enter the file name you want to decipher: ";
    getline(cin, filename);
    ifstream decipherFile(filename);
    while(true){
        if(!decipherFile){
            cout << "unable to open this file!"<<endl;
            cout << "try again: ";
            getline(cin,filename);
            decipherFile.open(filename);
        }else{
            cout << " File open successfully" << endl;
            break;
        }
    }

    // Input the number of rails
    while (true) {
        cout << "enter how many rails: ";
        cin >> key;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "invalid input. please enter a valid option\n";
        } else {
            break;
        }
    }


    const int originalkey = key;
    string content;
    while(getline(decipherFile,word)) {
        // Perform rail fence cipher decryption
        int size_word = word.size();
        int rails = originalkey;
        string fw(size_word, ' ');
        bool down = true;
        int num = 0;
        for (int i = 0; i < rails; i++) {
            int j = i;
            while (j < size_word) {
                fw[j] = word[num++];
                if (i == 0 || i == rails - 1) {
                    j += 2 * (rails - 1);
                } else {
                    if (down) {
                        j += 2 * (rails - 1 - i);
                    } else {
                        j += 2 * i;
                    }
                    down = !down;
                }
            }
        }

        // Convert the deciphered word to lower/upper case alternately
        for (int i = 0; i < fw.size(); i++) {
            if (islower(fw[i])) {
                fw[i] = toupper(fw[i]);
            } else {
                fw[i] = tolower(fw[i]);
            }
        }
        content+=fw + "\n";
    }
    decipherFile.close();
    ofstream outfile(filename);
    outfile << content;
    outfile.close();

    // Output the deciphered word
    cout << endl<< "your file decrypted successfully!" << endl;
    cout << endl;
    menu();
}

// Function for displaying menu options
void menu() {
    char x;
    int keys;
    cout << "(A) cipher\n" << "(B) decipher\n" << "(C) end\n";
    cin >> x;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (x == 'a' || x == 'A') {
        encrypt_fience(keys);
    } else if (x == 'b' || x == 'B') {
        dencrypt_fience();
    } else if (x == 'c' || x == 'C') {
        cout << "thank you";
    } else {
        cout << "invalid option\n";
        menu();
    }
}

int main() {
    // Start the program by displaying the menu
    menu();
    return 0;
}