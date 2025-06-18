#include "../commands/commands.h"

int logic(char* text) {
    char lastSymbol = '\0';
    int plusCount = 0;
    int minusCount = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        char chr = text[i];

        if (chr == '[' && text[i+1] == '-' && text[i+2] == ']') {
            zero();
            i += 2;
            continue;
        }

        if (lastSymbol != chr || (chr != '+' && chr != '-')) {
            if (lastSymbol == '+') {
                plus(plusCount);
            } else if (lastSymbol == '-') {
                minus(minusCount);
            }
            minusCount = 0;
            plusCount = 0;

            if (chr == '>') move_right();
            else if (chr == '<') move_left();
            else if (chr == '.') dot();
            else if (chr == '[') bracket_open();
            else if (chr == ']') bracket_close();
            else if (chr == ',') comma();
            else if (chr == '+') plusCount = 1;
            else if (chr == '-') minusCount = 1;
            else return -2;
        } else {
            if (chr == '+') plusCount++;
            else if (chr == '-') minusCount++;
        }
        lastSymbol = chr;
    }

    if (lastSymbol == '+') {
        plus(plusCount);
    } else if (lastSymbol == '-') {
        minus(minusCount);
    }

    return 0;
}