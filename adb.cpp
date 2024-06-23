#include <iostream>
#include <cstdlib>
#include <sstream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

bool generateNextCombination(char* prefix, const char* charset, int charsetLength, int length) {
    for (int i = length - 1; i >= 0; --i) {
        if (prefix[i] != charset[charsetLength - 1]) {
            for (int j = 0; j < charsetLength - 1; ++j) {
                if (prefix[i] == charset[j]) {
                    prefix[i] = charset[j + 1];
                    for (int k = i + 1; k < length; ++k) {
                        prefix[k] = charset[0];
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void generateCombination(char* prefix, int length) {
    std::cout.write(prefix, length);
    std::cout << std::endl;
}

void sendtext(const std::string& text) {
    std::stringstream ss;
    ss << text;
    std::string command = "adb shell input text \"" + ss.str() + "\"";
    system(command.c_str());
}

void tap(int x, int y) {
    std::stringstream ss;
    ss << "adb shell input tap " << x << " " << y;
    system(ss.str().c_str());
}

void sendEnter() {
    std::string command = "adb shell input keyevent ENTER";
    system(command.c_str());
}

int main() {
    std::string charset = "QWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    int minLength = 8, maxLength = 8;

    int charsetLength = charset.length();
    int length = minLength;
    char* prefix = new char[length + 1];
    for (int i = 0; i < length; ++i) {
        prefix[i] = charset[0];
    }
    prefix[length] = '\0';

    while (true) {
        generateCombination(prefix, length);
        std::string text(prefix);

        if (!generateNextCombination(prefix, charset.c_str(), charsetLength, length)) {
            if (length < maxLength) {
                ++length;
                delete[] prefix;
                prefix = new char[length + 1];
                for (int i = 0; i < length; ++i) {
                    prefix[i] = charset[0];
                }
                prefix[length] = '\0';
            }
            else {
                break;
            }
        }
        system("cls");
        tap(548, 890);
        this_thread::sleep_for(seconds(1));
        cout << text << endl;
        sendtext(text);
        this_thread::sleep_for(seconds(1));
        tap(532, 1140);
        this_thread::sleep_for(seconds(1));
        tap(532, 1140);
        this_thread::sleep_for(seconds(1));

    }

    delete[] prefix;
    return 0;
}