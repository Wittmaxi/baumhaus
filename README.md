# Baumhaus -- CHESS ENGINE  

Chess engine using neural networking and revolutionary Pattern recognition paired with a candidate Move Ideology
</br>

OFFICIAL DISCORD SERVER: https://discord.gg/swTEcQW

## Dependencies

This engine uses C++ only and is aimed to work on any operating system without any external libraries. </br>
To use the engine, an XBoard compatible Chess-UI (Arena is a good free choice) is needed.</br>
</br>

## Compilation

### LINUX

On Linux, you can simply browse to the main folder of baumhaus and run </br>

 `$> make` </br>

The program will be found in the `bin/` folder. 

After that, add the created file (baumhaus) to your chess-UI

### WINDOWS

On Windows I would recommend using **mingw-w64** to emulate the linux environment. We don't recommend using the Visual Studio Compiler, as it may require extra header files (e.g. `stdafx.h`), which are not part of the project, nor should they be as we aim to be platform independant.

**mingw-w64** is a fork of MinGW with added features, such as support for *pthreads* which are needed for this project. Find out more and download at: https://mingw-w64.org/doku.php

In order to compile using the makefile, use `mingw32-make.exe` which should come as a part of the **mingw-w64** installation: <br>

 `$> mingw32-make` </br>

To clean the project, just use the clean target: <br>

 `$> mingw32-make clean` </br>

You will find the execuatable in the `bin\` folder.

You can now add the engine to an XBoard Compatible Chess UI.

### MAC

--Todo

## Options

 `-d` or `--debug` Launch the Engine with debugging enabled. This will turn on debug output, which may interfere XBoard protocol. Use for testing. </br>
 `-h` or `--help` Displays the help text for the engine, and shows available options and usage.
 
# Algorythmics

## Neural Network

Neural Networks will only be used when the engine has grown bigger

## Pattern recognition

### Getting the Pattern

# Git-Organisation

## Coding style.

These rules may not be the best, however they help keep a certain consistency in our project. Commits that dont follow these rules will be deleted.

### Indentation and parenthesis

EVERY STATEMENT SHOULD BE IN IT'S OWN LINE OF CODE!!! 

things like 
```
cout << "HI" ; cout << "HI";
```
are not goot. 
Rather use
```
cout << "HI";
cout << "HI";
```
ALWAYS indent with two spaces. Simulated spaces are ok

The curly brackets should be placed after the statement
e.g.:
```
if(true) {

}
```
NOT
```
if (true) 
{

}
```
### comments
You should comment as many lines as possible IN ADDITION to clear code!!!
NEVER put in comment that lie.

### variable-namings
For coding this project, we use camelCase in function and variable names. This means, every word in the name begins with a capital except for the first word.

EXAMPLES: 
```
mySimpleVariable
helloWorld
jamesBond
```
The variables should have meaningful names and shouldn't contain signs as they might be incompatible to some compilers.

### system
The engine has to be compatible with every XBoard compatible system. Therefore, no techniques should be used that might be in conflict with some Operating-Systems.

## Github

### Commiting
There are many different branches. Commit to the branch that fits best your code. Also, don't push to master.
 
### branching

Make a PR, when the feature in your branch is finished.
