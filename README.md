# Programming Language II

&nbsp;

## Laboratory grade calculation formula (to confirm)

`50% (Pass Tests - based on lectures) + 50% (UnitTests from every classes)` \
**Presence at the classes is obligatory.** \
**Only one unjustified absence is allowed.**
&nbsp;

## Laboratory - upload of the results

Zip the complete C++ module (like Basics) and upload to UPEL to proper destination. \
Add your Student Identifier as the suffix to the filename. \
Filename pattern: \<ModuleName\>\_\<StudentIdentifier\>.zip \
Example filename: **Basics_284818.zip** \
The results **must** be uploaded by midnight the day before class (Monday, 12:00 PM), otherwise, they will not be considered. \
A file with a file name which not fulfill the required pattern will be **rejected**.
&nbsp;

# Requirements

**Compiler**: GCC 11 \
**System**: Ubuntu 22.04 (native instalation / wsl2 / docker)
<br/><br/>

# Docker - Windows/Linux/Mac

1. Install Docker engine on your machine
2. Install VSCode on your machine
3. Look here: https://code.visualstudio.com/docs/devcontainers/containers
4. Follow tutorial from here: https://code.visualstudio.com/docs/devcontainers/tutorial but instead "New dev Container" click "Open Folder in Cointainer" - The package with workspace contains Dockerfile and .devcontainer.json, "Open Folder in Cointainer" will use it.

# Windows WSL2

1. Install WSL2 in your windows, instruction: https://learn.microsoft.com/en-us/windows/wsl/install
2. Install Ubuntu 22.04.3 LTS from MS Store, link here: https://apps.microsoft.com/detail/9pn20msr04dw?hl=en-US&gl=US
3. Install VSCode on windows with WSL extention
4. Connect from vscode to WSL
5. Follow Ubuntu 22.04 post install setup

# Ubuntu 22.04

### Required system packages install command

```
sudo apt install -y gcc-11 g++-11 gdb cmake clang-format
```

### Required (or at least recommended) VsCode extensions:

```
code --install-extension ms-vscode.cmake-tools
code --install-extension ms-vscode.cpptools
code --install-extension ms-vscode.cpptools-extension-pack
code --install-extension ms-vscode.cpptools-themes
code --install-extension xaver.clang-format
code --install-extension matepek.vscode-catch2-test-adapter
```

# Workspace configuration

### Clang formatter

How to configure default C++ formater:

1. Open any C++ file
2. Crtl + Shift + P
3. Find 'Format document with' and press Enter
4. Select 'Configure default formatter'
5. Select 'Clang-Format'

**Formatter usage:** Ctrl + Shift + I

## Building single test file

1. Open the CMake extension tab on the left side
2. Configure your project (needed only at the very first time or after build directory removal)
3. Find the desired test target you would like to build
4. Use 'Build' option to build a test from the specified source file
   **Important**: Verify if your build was successful - check terminal output, there should not be any errors
   &nbsp;

## Running single test file (after build)

1. Open the Testing extension tab on the left side
2. Choose test/tests you would like to run
3. Run your test using option 'Run Test' or 'Run Tests
4. When you did a good job, the test will be marked with green color, red otherwise.
5. When one of the tests will fail, you can check the reason by clicking on the red status icon.
   **Important**: You **must** rebuild every test after changing something in your code. Otherwise, you will be testing the older version of the code.
   &nbsp;

## Basics

#### Scope of Basics classes

1. naming convention (presentation of well-formatted example file) + code formatting
2. base types (int, float, bool, etc.)
3. flow control (if, case, ternary operator, etc.)
4. loops (while, for, do while)

#### Usefull links and material for Basics classes

- Lecture: <https://home.agh.edu.pl/~mdig/dokuwiki/doku.php?id=teaching:courses:agh:weaiiib:cs:pl2:2022_23_l:start>
- Data types: <https://www.w3schools.com/cpp/cpp_data_types.asp>
- Operators: <https://www.w3schools.com/cpp/cpp_operators.asp>
- Conditions: <https://www.w3schools.com/cpp/cpp_conditions.asp>
- Switch: <https://www.w3schools.com/cpp/cpp_switch.asp>
- Ternary operator: <https://www.w3schools.com/cpp/cpp_conditions_shorthand.asp>
- For loop: <https://www.w3schools.com/cpp/cpp_for_loop.asp>
- While loop: <https://www.w3schools.com/cpp/cpp_while_loop.asp>
  &nbsp;

# Basics2

#### Usefull links and material for Basics classes

- auto: <https://en.cppreference.com/w/cpp/language/auto>
- const: <https://en.cppreference.com/w/cpp/language/cv>
- constexpr: <https://en.cppreference.com/w/cpp/language/constexpr>
- range-based for: <https://en.cppreference.com/w/cpp/language/range-for>
- comments: <https://en.cppreference.com/w/cpp/comment>
- scope: <https://en.cppreference.com/w/cpp/language/scope>
- variables: <https://www.w3schools.com/cpp/cpp_variables.asp>
- sizeof: <https://en.cppreference.com/w/cpp/language/sizeof>
  &nbsp;

## Functions

#### Scope of Functions classes

1. Introduction of compilation warning flags
2. Introduction of doxygen documentation
3. Functions - copy, reference, const reference arguments
4. Functions - return values, default arguments
5. Functions - recursion, overload
6. Functions - template

#### Usefull links and material for Functions classes

- Lecture: <https://home.agh.edu.pl/~mdig/dokuwiki/lib/exe/fetch.php?media=teaching:courses:agh:weaiiib:cs:pl2:2021_22_l:3_c_functions.pdf>
- Doxygen: <https://www.doxygen.nl/manual/docblocks.html>
- GCC warning options: <https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html>
- Functions: <https://www.w3schools.com/cpp/cpp_functions.asp>
- Functions: <https://en.cppreference.com/w/cpp/language/functions>
- Function Parameters: <https://www.w3schools.com/cpp/cpp_function_param.asp>
- Function Overloading: <https://www.w3schools.com/cpp/cpp_function_overloading.asp>
- Recursion: <https://www.w3schools.com/cpp/cpp_functions_recursion.asp>
- Template: <https://en.cppreference.com/w/cpp/language/function_template>

## Containers

#### Scope of Containers classes

1. Introduction to the most popular C++ containers (std::map, std::set, std::vector)
2. Lambda functions introduction
3. Extension of std::pair, std::string and std::array knowledge
4. Container std::vector
5. Container std::set
6. Container std::map

#### Usefull links and material for Containers classes

- Lecture - not available
- Containers overview: <https://en.cppreference.com/w/cpp/container>
- Lambda functions: <https://en.cppreference.com/w/cpp/language/lambda>
- Algorithms library: <https://en.cppreference.com/w/cpp/algorithm>
- Numeric library: <https://en.cppreference.com/w/cpp/header/numeric>
- std::vector: <https://en.cppreference.com/w/cpp/container/vector>
- std::set: <https://en.cppreference.com/w/cpp/container/set>

## Structures/Classes - basics

#### Scope of Structures/Classes - basics

1. Aggregate initialization
2. Designated initializers
3. Static/non-static data members & member functions
4. Const/non-const data members & member functions
5. Operator overloading
6. Member access operators
7. std::variant

#### Usefull links and material for Structures/Classes - basics

- Lecture - not available
- aggregate initialization: <https://en.cppreference.com/w/cpp/language/aggregate_initialization>
- classes: <https://en.cppreference.com/w/cpp/language/classes>
- data members: <https://en.cppreference.com/w/cpp/language/data_members>
- member functions: <https://en.cppreference.com/w/cpp/language/member_functions>
- Static data members: <https://en.cppreference.com/w/cpp/language/static#Static_data_members>
- Static member functions: <https://en.cppreference.com/w/cpp/language/static#Static_member_functions>
- operators: <https://en.cppreference.com/w/cpp/language/operators>
- operator member access: <https://en.cppreference.com/w/cpp/language/operator_member_access>
- std::variant: <https://en.cppreference.com/w/cpp/utility/variant>

## Classes

#### Scope of Classes

1. Inheritance
2. Polymorphism
3. Factory
4. Iterator class
5. Enumerator class

#### Usefull links and material for Classes

- Lecture - not available
- Classes: <https://www.geeksforgeeks.org/c-classes-and-objects/>
- Inheritance: <https://www.geeksforgeeks.org/inheritance-in-c/>
- Virtual functions: <https://www.geeksforgeeks.org/virtual-function-cpp/>
- Interface class: <https://www.geeksforgeeks.org/cpp-program-to-create-an-interface/>
- Polymorphism: <https://www.w3schools.com/cpp/cpp_polymorphism.asp>
- Factory: <https://www.geeksforgeeks.org/factory-method-for-designing-pattern/>
- Iterator: <https://en.cppreference.com/w/cpp/iterator/iterator>
- Enumerator class: <https://en.cppreference.com/w/cpp/language/enum>
- New/Delete: <https://www.geeksforgeeks.org/new-and-delete-operators-in-cpp-for-dynamic-memory/>

## SmartPointers

#### Scope of SmartPointers

1. Smart Pointers
2. Forward declaration
3. Regex
4. std::thread
5. std::mutex

#### Usefull links and material for SmartPointers

- Smart Pointers: <https://en.cppreference.com/book/intro/smart_pointers>
- Smart Pointers: <https://www.geeksforgeeks.org/smart-pointers-cpp/>
- Regex: <https://en.cppreference.com/w/cpp/regex>
- Forward declaration: <https://www.geeksforgeeks.org/what-are-forward-declarations-in-c/>
- std::thread: <https://en.cppreference.com/w/cpp/thread/thread>
- std::mutex: <https://en.cppreference.com/w/cpp/thread/mutex>

#### Scope of Gdb

1. GDB debugger
2. GDB in VSCode
3. Basic commands in gdb
4. C++ Debugging

#### Usefull links and material for Gdb

- Simple list of simple GDB commands: https://linuxhint.com/list-gdb-commands/
- GDB in VSCode: https://code.visualstudio.com/docs/cpp/cpp-debug
- VSCode Config for Linux: https://code.visualstudio.com/docs/cpp/config-linux
- GDB running from the terminal: https://www.geeksforgeeks.org/gdb-command-in-linux-with-examples/
- Online GDB playground: https://www.onlinegdb.com/
- Full GDB documentation: https://sourceware.org/gdb/current/onlinedocs/gdb.html/
- Getting started tutorial: https://developers.redhat.com/blog/2021/04/30/the-gdb-developers-gnu-debugger-tutorial-part-1-getting-started-with-the-debugger#
- Getting started tutorial part 2 : https://developers.redhat.com/articles/2022/01/10/gdb-developers-gnu-debugger-tutorial-part-2-all-about-debuginfo
