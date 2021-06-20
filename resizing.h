#include <iostream>
#include <stdexcept>
#include <Windows.h>

using namespace std;


void SetConsoleWindowSize(int x, int y)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    if (h == INVALID_HANDLE_VALUE)
        throw std::runtime_error("Unable to get stdout handle.");

    // If either dimension is greater than the largest console window we can have,
    // there is no point in attempting the change.
    {
        COORD largestSize = GetLargestConsoleWindowSize(h);
        if (x > largestSize.X)
            throw std::invalid_argument("The x dimension is too large.");
        if (y > largestSize.Y)
            throw std::invalid_argument("The y dimension is too large.");
    }


    CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
    if (!GetConsoleScreenBufferInfo(h, &bufferInfo))
        throw std::runtime_error("Unable to retrieve screen buffer info.");

    SMALL_RECT& winInfo = bufferInfo.srWindow;
    COORD windowSize = { (SHORT)(winInfo.Right - winInfo.Left + 1), (SHORT)(winInfo.Bottom - winInfo.Top + 1)};

    if (windowSize.X > x || windowSize.Y > y)
    {
        // window size needs to be adjusted before the buffer size can be reduced.
        SMALL_RECT info =
        {
            0,
            0,
            x < windowSize.X ? (SHORT)(x-1) : (SHORT)(windowSize.X-1),
            y < windowSize.Y ? (SHORT)(y-1) : (SHORT)(windowSize.Y-1)
        };

        if (!SetConsoleWindowInfo(h, TRUE, &info))
            throw std::runtime_error("Unable to resize window before resizing buffer.");
    }

    COORD size = { (SHORT)x, (SHORT)y };
    if (!SetConsoleScreenBufferSize(h, size))
        throw std::runtime_error("Unable to resize screen buffer.");


    SMALL_RECT info = { 0, 0, (SHORT)(x - 1), (SHORT)(y - 1) };
    if (!SetConsoleWindowInfo(h, TRUE, &info))
        throw std::runtime_error("Unable to resize window after resizing buffer.");
}



void ShowLastSystemError()
{
    LPSTR messageBuffer;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        0,          // source
        GetLastError(),
        0,          // lang
        (LPSTR)&messageBuffer,
        0,
        NULL);

    std::cerr << messageBuffer << '\n';
    LocalFree(messageBuffer);
}

COORD QueryUserForConsoleSize()
{
    COORD size = { 0, 0 };

    std::cout << "New console size: ";
    std::cin >> size.X >> size.Y;

    return size;
}
/*
int main()
{
    COORD consoleSize;

    std::cout << "An x or y size of 0 will terminate the program\n";
    while (consoleSize = QueryUserForConsoleSize(), consoleSize.X && consoleSize.Y)
    {
        try {
            SetConsoleWindowSize(consoleSize.X, consoleSize.Y);
        }

        catch (std::logic_error& ex)
        {
            std::cerr << ex.what() << '\n';
        }

        catch (std::exception& ex)
        {
            std::cerr << ex.what() << "\nSystem error: ";
            ShowLastSystemError();
        }
    }
}
*/
