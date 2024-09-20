echo "Building project"
gcc -c *.c
gcc -o runnable *.o
echo "Build complete"
./runnable
