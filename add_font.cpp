#include <iostream>
#include <string>
#include <cctype>

#include "fonts.h"
#include "util.h"

using namespace std;

static string to_lower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

int add_font() {
    string font_name, font_style, file_name;

    cout << "Enter font name: ";
    getline(cin, font_name);
    font_name = to_lower(font_name);

    cout << "Enter font style: ";
    getline(cin, font_style);
    font_style = to_lower(font_style);

    cout << "Enter file name: ";
    getline(cin, file_name);

    if (fonts.count(font_name)) {
        if (fonts[font_name].count(font_style)) {
            cout << "Error: Style already exists.\n";
            return 0;
        }
        fonts[font_name][font_style] = file_name;
    } else {
        fonts[font_name] = {{font_style, file_name}};
    }

    cout << "Font added successfully.\n";
    return 0;
}
