# This is a homebrewed string library, sort of matching the string methods of the String object in JS - no regex methods for now, though

**Important note: To run the program you need a C-compiler! The bash script relies on the gcc compiler being installed**

## Running the program
1. Download the project files to a specified folder
2. Open a bash terminal if you want to use the bash script, alternatively use any other shell
3. Navigate to the folder containing the project files
4. Either use the simple provided bash or bat script. Alternatively, if you have Make, running `make start` also works.
5. Or manually build and combine the files by pasting the following commands:
    1. `gcc -c *.c`
    2. `gcc -o runnable *.o`
    3. `./runnable`
6. This will only run a bunch of tests for now - hopefully all passing - but if you're interested in using the library in other projects, simply copy the strlib.c and strlib.h and you're good to go
