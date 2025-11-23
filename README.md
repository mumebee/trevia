Trevia Demo Project

A simple C++ console program that helps users explore cities and local activities efficiently.
This is a demo version meant to test the core of the project: basic structures, functions, input handling, and navigation.

WHAT THIS DEMO INCLUDES
Structured C++ project (header + source files)
City selection
Activities list for each city
Safe input handling (invalid input won’t crash the program)
Organized files: main.cpp, functions.cpp, functions.h, structures.h, structures.cpp


FOLDER STRUCTURE

demo/

-- main.cpp

-- functions.cpp

-- functions.h

-- structures.h

-- README.md (this file)



LIBRARIES USED

Standard C++ libraries:


<iostream> - printing and reading

<string> - working with text

<vector> - storing activities

<cctype> - tolower()



AVAILABLE CITIES, FOR NOW

Tashkent

Samarkand

Bukhara



MAIN FEATURES

Consider user preferences:

- how many cities

- which cities

- what kind of activities

- budget



Invalid inputs automatically re-ask the user.



Display activities that perfectly fit the user's preferences, if any.

Then display recommended activities, if any:

- 'good' ones that match at least one of their "wishes"

- free ones if their budget is too small



HOW TO USE ON WINDOWS

1. Download demo.exe

2. Double click or run on your computer

3. Use it

4. Hit ENTER in the end to close it



HOW INPUT IS PROCESSES

Valid input (numbers or strings)

-> Program continues normally depending on which one is expected.


Invalid input (letters, symbols, empty input, duplicates, illogical ones...)

-> Program asks again.



COMPILATION

Used to compile all the files in this folder into a single .exe file:

g++ main.cpp functions.cpp structures.cpp -o demo.exe -static -static-libgcc -static-libstdc++



FUTURE PLANS

More activities, more cities, more countries

Location processing to give the best order to discover the locations in

Consider user's time

Web/app version