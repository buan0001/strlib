# This is a simple terminal-based converter program written in C.

**Important note: To run the program you need a C-compiler! The bash script relies on the gcc compiler being installed**

## Running the program
1. Download the project files to a specified folder
2. Open a bash terminal if you want to use the bash script, alternatively use any other shell
3. Navigate to the folder containing the project files
4. Either use the simple provided bash script:
    * Enter `./br.sh` to run the bash script
    * If all goes well, the program should compile and run, maybe
5. Or manually build and combine the files by pasting the following commands:
    1. `gcc -c *.c`
    2. `gcc -o runnable *.o`
    3. `./runnable`
6. Now the program should be running, allowing you to convert between different numbers