// ────── setup ─────────────────────────────────────────────────────────────────────────────────────────────┐

#ifdef _WIN32
#include <windows.h>
int windows_nonsense = (SetConsoleOutputCP(65001), SetConsoleMode(GetStdHandle(-11), 7));
#endif

#include <iostream>
#include <filesystem>

using namespace std;
using namespace std::filesystem;

#define bold    "\e[1m"
#define red     "\e[31m"
#define reset   "\e[m"

void recurse(path, string = "");
error_code err;

// ────── main ──────────────────────────────────────────────────────────────────────────────────────────────┤

int main(int, char** argv)
{
    cout << '\n';

    if (!argv[1] || !is_directory(argv[1], err)) return cout << red << "⚠ invalid directory\n\n" << reset, 1;

    path target = argv[1];

    cout << bold << target.string() << '\n' << reset;
    recurse(target);

    cout << '\n';
}

// ────── recursion ─────────────────────────────────────────────────────────────────────────────────────────┤

void recurse(path target, string depth)
{
    directory_iterator it(target, err), end;

    while (it != end)
    {
        directory_entry entry = *it;
        bool last = (++it == end);

        string pfx = last ? "└─ " : "├─ ";
        string ind = last ? "   " : "│  ";

        cout << depth << pfx << entry.path().filename().string() << '\n';

        if (is_directory(entry, err) && !is_symlink(entry)) recurse(entry, depth + ind);
    }
}

// ──────────────────────────────────────────────────────────────────────────────────────────────────────────┘
