#include <iostream>
#include <limits>
#include <cctype>
#include "fonts.h"
#include <string>

#include "util.h"

std::string to_lower(std::string s) {
    for (char &c : s)
        c = tolower(static_cast<unsigned char>(c));
    return s;
}

int main() {
    int choice = 0;

    while (true) {
        std::cout << "\nEnter your choice\n"
                  << "1 : Font Generator\n"
                  << "2 : Add a New Font\n"
                  << "3 : Exit\n> ";

        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                hex_code_text();
                break;

            case 2:
                add_font();
                break;

            case 3:
                return 0;

            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
}
