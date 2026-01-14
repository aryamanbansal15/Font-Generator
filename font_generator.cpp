#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include "fonts.h"
#include "util.h"

using namespace std;

/* Helpers */
static string to_lower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

vector<string> hex_code(char a, string filename, double size);
vector<vector<int>> binary_code(unsigned char* bitmap, int w, int h);
vector<vector<int>> binary_code_space(unsigned char* bitmap, int w, int h);

string file_name(const string& font_name, const string& font_style) {
    return "Fonts/" + fonts[font_name][font_style];
}

/* MAIN FUNCTION */
vector<vector<string>> hex_code_text() {
    string text, font_name, font_style;
    double size;

    cout << "Enter the text: ";
    getline(cin, text);

    /* FONT NAME */
    while (true) {
        cout << "Enter font name: ";
        getline(cin, font_name);
        font_name = to_lower(font_name);

        if (fonts.find(font_name) != fonts.end())
            break;

        cout << "Font not found. Try again.\n";
    }

    /* FONT STYLE */
    while (true) {
        cout << "Available styles:\n";
        for (auto& s : fonts[font_name])
            cout << " - " << s.first << "\n";

        cout << "Enter font style: ";
        getline(cin, font_style);
        font_style = to_lower(font_style);

        if (fonts[font_name].find(font_style) != fonts[font_name].end())
            break;

        cout << "Invalid style. Try again.\n";
    }

    cout << "Enter font size: ";
    cin >> size;
    cin.ignore();

    string filename = file_name(font_name, font_style);

    vector<vector<string>> output(text.size());
    for (size_t i = 0; i < text.size(); i++)
        {
            output[i] = hex_code(text[i], filename, size);
            for (int j = 0; j < output[i].size(); j++)
                cout << output[i][j] << '\n';
        }
    return output;
}

/* CHARACTER → HEX */
vector<string> hex_code(char a, string filename, double size) {
    char temp = a;
    if(a == ' '){
        a = 'n';
    }

    ifstream file(filename, ios::binary);
    if (!file) return {};

    vector<unsigned char> buffer(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    stbtt_fontinfo font;
    stbtt_InitFont(&font, buffer.data(), 0);

    float scale = stbtt_ScaleForPixelHeight(&font, size);

    int w, h, xoff, yoff;
    unsigned char* bitmap =
        stbtt_GetCodepointBitmap(&font, 0, scale, a, &w, &h, &xoff, &yoff);
    
    vector<vector<int>> bin;

    if (temp == ' ') {
        bin = binary_code_space(bitmap, w, h);
    }
    else {
        bin = binary_code(bitmap, w, h);
    }
    vector<string> hex_rows;

    for (auto& row : bin) {
        string bits;
        for (int b : row) bits += (b ? '1' : '0');

        int pad = (4 - bits.size() % 4) % 4;
        bits = string(pad, '0') + bits;

        string hex;
        for (size_t i = 0; i < bits.size(); i += 4)
            hex += "0123456789ABCDEF"[stoi(bits.substr(i, 4), nullptr, 2)];

        hex_rows.push_back(hex);
    }

    stbtt_FreeBitmap(bitmap, nullptr);
    return hex_rows;
}

/* BITMAP → BINARY */
vector<vector<int>> binary_code(unsigned char* bitmap, int w, int h) {
    vector<vector<int>> bin(h, vector<int>(w));

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            bin[y][x] = bitmap[y * w + x] > 0;
            cout << (bin[y][x] ? '.' : ' ');
        }
        cout << '\n';
    }
    return bin;
}

/* BITMAP → BINARY (for whitespace)*/
vector<vector<int>> binary_code_space(unsigned char* bitmap, int w, int h) {
    vector<vector<int>> bin(h, vector<int>(w));

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            bin[y][x] = 0;
            cout << (bin[y][x] ? '.' : ' ');
        }
        cout << '\n';
    }
    return bin;
}