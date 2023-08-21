#include "Utility.h"

int Utility::randomNumber(int minNum, int maxNum)
{
    std::random_device r;

    std::default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(minNum, maxNum);
    int mean = uniform_dist(e1);

    return mean;
}

void Utility::MaxScreen()
{
    HWND Hwnd = GetForegroundWindow();
    ShowWindow(Hwnd, SW_MAXIMIZE);
}

void Utility::SetupFont(int fontSize)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = fontSize;            // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_BOLD;
    //std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    SetCurrentConsoleFontEx(outputHandle, FALSE, &cfi);
}

void Utility::PositionText(int x, int y)
{
    COORD Coordinates = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(outputHandle, Coordinates);
}

void Utility::Print(Position pos, std::string s, int linelength)
{
    int spaces = 0;
    switch (pos)
    {
    case CENTRE: spaces = (linelength - s.size()) / 2.0f; break;
    case RIGHT: spaces = linelength - s.size(); break;
    }
    if (spaces > 0) std::cout << std::string(spaces, ' ');
    std::cout << s << '\n';
}

void Utility::ShowConsoleCursor(bool showFlag)
{
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(outputHandle, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(outputHandle, &cursorInfo);
}

void Utility::WrapText(std::string const& input, size_t width, std::ostream& os, size_t indent = 0) {
    std::istringstream in(input);

    os << std::string(indent, ' ');
    size_t current = indent;
    std::string word;

    while (in >> word) {
        if (current + word.size() > width) {
            os << "\n" << std::string(indent, ' ');
            current = indent;
            std::cout << " ";
        }
        os << word << ' ';
        current += word.size() + 1;
    }
}