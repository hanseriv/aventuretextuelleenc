cd ..
gcc -c -ggdb *.c -Wall -std=c89 -Wextra -pedantic
mv *.o ./compilation
cd compilation
gcc -o  ../build/aventure_c_linux *.o -Wall -std=c89 
