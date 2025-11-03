--------------------------------------------------------------------------------
Number Deromanizer 1.0
Author: Bruce Nebergall
Last updated: 2025-11-3
--------------------------------------------------------------------------------

SUMMARY
-------
A small C++ console application that collects a Roman numeral from the user,
validates it, converts it to a decimal value, and prints the result as Roman
or Decimal on request.


FEATURES
--------
- Accepts inputs like "mcxiv" or "M C X I V" and normalizes to uppercase
  without spaces (e.g., "MCXIV").
- Validates using strict textbook rules:
    * Allowed characters: I, V, X, L, C, D, M
    * Repeats: I/X/C/M ≤ 3 in a row; V/L/D must not repeat
    * Subtractive pairs only: IV, IX, XL, XC, CD, CM (smaller precedes larger)
- Converts with a single-pass lookahead algorithm (O(n)).
- Prints Roman or Decimal on demand; if neither R nor D is chosen, prints both.
- Clear error messages for invalid input; reprompt loop.


REQUIREMENTS
------------
- Compiler: C++17 or newer
- OS: Windows, Linux, or macOS
- Single source file build 


BUILD
-----
Windows (MSVC, from "Developer Command Prompt"):
    cl /std:c++17 /EHsc /W4 /Zi romanizer_main.cpp /Fe:NumberDeromanizer.exe

Windows (MinGW-w64 g++):
    g++ -std=c++17 -Wall -Wextra -O2 -g romanizer_main.cpp -o NumberDeromanizer.exe

Linux/macOS (g++ or clang++):
    g++ -std=c++17 -Wall -Wextra -O2 -g romanizer_main.cpp -o number-deromanizer


RUN
---
Windows:
    NumberDeromanizer.exe

Linux/macOS:
    ./number-deromanizer


PROGRAM OVERVIEW
----------------
Main loop:
  1) Prompt for Roman numeral (getline).
  2) number.setRoman(input)   // normalize → validate → store (move) → convert
  3) Prompt for output format (R/D/other) and print accordingly.

Class (RomanType) responsibilities:
  - setRoman(std::string)         : normalize, validate, store (move), convert
  - toRoman() / toDecimal()       : accessors (no conversion)
  - printRoman() / printDecimal() : convenience output
  - Private helpers               : normalize, validateRoman, romanValue, romanToDecimal

Class invariant:
  After any successful call to setRoman, roman_ and decimal_ represent the same value.




CONSIDERATIONS / LIMITATIONS
-----------------
- Classical Roman numerals only
- Input is normalized by removing all whitespace and uppercasing letters



-----------------
- romanizer_main.cpp       
- README.txt



CONTACT
-------
Author: Bruce Nebergall
