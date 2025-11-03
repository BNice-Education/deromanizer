// Program: Number Deromanizer 1.0
// Author: Bruce Nebergall
// Last updated: 2025-11-3
// Purpose: Collect and store a Roman numeral; print it as Roman or Decimal.

#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

class RomanType { // Class definition
public:
    RomanType() = default; // Constructs at default state

    explicit RomanType(std::string roman) { setRoman(std::move(roman)); }

    // Normalizes, validates, commits to private member of RomanType class, then converts
    void setRoman(std::string roman) {
        normalize(roman);
        validateRoman(roman);
        roman_ = std::move(roman);
        decimal_ = romanToDecimal(roman_);
    }

    // Accessors 
    int toDecimal() const { return decimal_; }
    const std::string& toRoman() const { return roman_; }

    // Simple printers '\n'
    void printRoman() const { std::cout << roman_ << '\n'; }
    void printDecimal() const { std::cout << decimal_ << '\n'; }

private:
    // Remove whitespace and convert to uppercase letters
    static void normalize(std::string& s) {
        std::string t;
        t.reserve(s.size());
        for (char c : s) {
            const unsigned char uc = static_cast<unsigned char>(c);
            if (!std::isspace(uc)) t.push_back(static_cast<char>(std::toupper(uc)));
        }
        s.swap(t);
    }

    // rules: valid symbols, repeat limits, allowed subtractives.
    static void validateRoman(const std::string& s) {
        if (s.empty()) throw std::invalid_argument("Empty input; please enter a Roman numeral.");

        for (char c : s) {
            if (romanValue(c) == 0)
                throw std::invalid_argument("Invalid character: '" + std::string(1, c) + "'. Valid: I V X L C D M.");
        }

        // No repeats for V, L, D; at most 3 for I, X, C, M.
        auto noRepeat = [](char c){ return c=='V'||c=='L'||c=='D'; };
        int run = 1;
        for (std::size_t i = 1; i < s.size(); ++i) {
            run = (s[i] == s[i-1]) ? run + 1 : 1;
            if ((noRepeat(s[i]) && run > 1) || run > 3) {
                throw std::invalid_argument("Too many repeated characters in sequence.");
            }
        }

        // Only IV, IX, XL, XC, CD, CM allowed when smaller precedes larger.
        for (std::size_t i = 0; i + 1 < s.size(); ++i) {
            int a = romanValue(s[i]), b = romanValue(s[i+1]);
            if (a < b) {
                std::string pair{s[i], s[i+1]};
                if (!(pair=="IV"||pair=="IX"||pair=="XL"||pair=="XC"||pair=="CD"||pair=="CM"))
                    throw std::invalid_argument("Invalid subtractive pair: '" + pair + "'.");
            }
        }
    }

    static constexpr int romanValue(char c) noexcept {
        switch (c) {
            case 'I': return 1;   case 'V': return 5;   case 'X': return 10;   case 'L': return 50;
            case 'C': return 100; case 'D': return 500; case 'M': return 1000; default:  return 0;
        }
    }

    // Single-pass lookahead conversion
    static int romanToDecimal(const std::string& s) noexcept {
        int total = 0;
        for (std::size_t i = 0; i < s.size();) {
            int v = romanValue(s[i]);
            if (i + 1 < s.size()) {
                int next = romanValue(s[i + 1]);
                if (v < next) { total += (next - v); i += 2; continue; }
            }
            total += v; ++i;
        }
        return total;
    }

private:
    std::string roman_{};
    int         decimal_{0};
};

int main() {

    RomanType number; // holds current working value, initialized default

    for (;;) {
        std::cout << "Please enter a Roman numeral (or 'q' to quit): ";
        std::string romanLine;
        if (!std::getline(std::cin, romanLine)) break; // EOF/stream error
        if (romanLine == "q" || romanLine == "Q") break;

        try {
            number.setRoman(romanLine); // normalize, validate, convert, store
        } catch (const std::exception& e) {
            std::cerr << "Invalid input: " << e.what() << '\n';
            continue;
        }

        std::cout << "Print as (r)oman or (d)ecimal? (any other input prints both): ";
        std::string option;
        std::getline(std::cin, option);

        // Normalize the first character
        const char choice =
            option.empty() ? '\0' : static_cast<char>(std::tolower(static_cast<unsigned char>(option[0])));

        if (choice == 'r') {
            number.printRoman();
        } else if (choice == 'd') {
            number.printDecimal();
        } else {
            std::cout << "You entered: ";
            number.printRoman();
            std::cout << "Converted to decimal: ";
            number.printDecimal();
        }
    }
    return 0;
}
