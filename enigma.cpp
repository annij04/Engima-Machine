#include <iostream>
#include <string>
#include <vector>

using namespace std;

class EnigmaMachine {
    private:
    //rotors are randomly generated
    string rotor = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string plugboard = "ZYXWVUTSRQKLMNOPJIHGFEDCBA"; //only first ten characters are inversed
    string letter_swap = "ZYXWVUTSRQPONMLKJIHGFEDCBA";

    public:
    // process a one character
    char encrypt_char(char c, size_t rotor1Pos, size_t rotor2Pos, size_t rotor3Pos) {
        //change to uppercase if not already
        c = char(toupper(c));

        // PLUGBOARD 
        size_t index = size_t(c - 'A');
        c = plugboard[index % 26];

        // ROTOR 
        c = rotor[size_t(size_t(c - 'A') + rotor1Pos) % 26];
        c = rotor[size_t(size_t(c - 'A') + rotor2Pos) % 26];
        c = rotor[size_t(size_t(c - 'A') + rotor3Pos) % 26];

        // REFLECTOR
        c = letter_swap[size_t(c - 'A')];
        // Reverse rotor
        c = (size_t(c - 'A') - rotor3Pos + 26) % 26 + 'A';
        c = (size_t(c - 'A') - rotor2Pos + 26) % 26 + 'A';
        c = (size_t(c - 'A') - rotor1Pos + 26) % 26 + 'A';
        // Plugboard 
        index = size_t(c - int('A'));
        c = plugboard[index % 26];

        return c;
    }
};



int main() {
    cout << "ENIGMA MACHINE DEMONSTRATION" << endl;
    cout << "Encryption Steps" << endl;
    cout << "Step 1: Character goes through pluboard and gets reflected." << endl;
    cout << "Step 2: Character goes through three rotors: fast, medium and slow." << endl;
    cout << "Step 3: Character goes through a relfector. The reflector has three parts:" << endl;
    cout << "   Part A: Character is swapped with its inverse (similar to plugboard)." << endl;
    cout << "   Part B: Character travels backwards through the three rotors." << endl;
    cout << "   Part C: Character goes through the plugboard again." << endl << endl;
    cout << "Characters that aren't reflected: KLMNOP" << endl << endl;
    EnigmaMachine enigma;

    // DEMONSTRATION    
    while (true) {
        cout << "Enter Message" << endl;
        string message;
        getline(cin, message);
        if (message == "QUIT" || message == "quit") { 
            cout << "THANK YOU" << endl;
            return 0; 
        }
        size_t rotor1Pos = 0, rotor2Pos = 0, rotor3Pos = 0;
        string encrypted_message = "";

        for (size_t i = 0; i < message.size(); ++i) {
            if (isalpha(message[i])) {
                char encrypted_char = enigma.encrypt_char(message[i], rotor1Pos, rotor2Pos, rotor3Pos);
                encrypted_message += encrypted_char;
                //TODO:
                cout << message[i] << " to " << encrypted_char << " " << "Rotor positions " << rotor1Pos << " " << rotor2Pos << " " << rotor3Pos << endl;

                //rotate the rotors
                rotor1Pos = (rotor1Pos + 1) % 26;
                if (rotor1Pos == 0) { //gone through the first rotor
                    rotor2Pos = (rotor2Pos + 1) % 26;
                    if (rotor2Pos == 0) {
                        rotor3Pos = (rotor3Pos + 1) % 26;
                    }
                }
            } 
            else {
                cout << message[i];
                encrypted_message += message[i]; //not in alphabet (spaces, symbols etc)
            }
        }
        cout << endl;
        cout  << "Original Message: " << message << endl;
        cout << "Encrypted Message: " << encrypted_message << endl << endl;

    }
    cout << endl << endl;

    return 0;
}


// messages: Hello 
// Encrypt this message.
// HHH
// AAAOOO
// NNNN
// This means that even if the same letter is typed multiple times in a row, a different letter is outputted each time, adding to the cipher's complexity. 
// MATH214
// this is an encrypted message
// THIS MESSAGE WILL ROTATE ROTOR ONE AND ROTOR TWO

// SINCE EACH ROTOR ONLY ROTATES AFTER A PREVIOUS ROTOR HAS ROTATED TWENTY SIX TIMES, THE THIRD ROTOR WOULD ONLY ROTATE AFTER EVERY 26 * 26 = 676 CHARACTERS.
