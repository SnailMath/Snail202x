# Snail202x
_If you want to install Hollyhock2, click here: https://github.com/SnailMath/hollyhock-2 _

Snail202x is a program to modify the firmware of the calculator fx-cp400 with a modification, e.g. Hollyhock (or the old LoaderII).
Snail202x contains the zlib libary. Aditionally, "Resource Hacker" and the Calculator os updater are needed. Snail202x.exe will show an error, when these programs are not present.
Because the os updater for the calculator is not available for Linux, this program needs to be (compiled and) executed under Windows.

##Usage of Snail202x.exe
The executable Snail202x.exe needs to be in a folder called Snail202x on the Desktop (so Snail2021.exe needs to be in a folder called Snail2021).
When you extract it from a release (for example from HollyHock) you can just extract the .zip to the Desktop.

The mod, that should be applied to the firmware, should be placed in a file called `mod.txt` in the same folder as the executable .exe file.

Structure of mod.txt
```
'ver02.01.2000 'The version number of the OS to modify. If this does not match with the firmware, Snail202x will throw an error. This is optional.
80123456: 'The Address of the first modification in hexadecimal
0000000000000000 'The data of this modification in hex. This will be put into the firmware. 

'You can add comments starting with The single quotation mark ' (similar to casio basic). Comments end with the end of the line.

*  'Use the Star between multiple modifications, if there are more than one.

80223344: 'The next modification (there is no limit to modifications)
11 'The modification data, at least one byte.
22 'The data can be multiple lines long.

'There is no * after the last modification

```
The final release can contain a mod.txt file, that is created when no mod.txt file exists. 
The Snail2021.exe included

##compiling of Snail202x
You need minGW to compile this.

Download the minGW installer and install the following:

- `mingw32-base-bin` (from All Packages -> MinGW -> MinGW Base System)
- `mingw32-libz-dev` (from All Packages -> MinGW -> MinGW Libaries -> MinGW Standard Libaries)


