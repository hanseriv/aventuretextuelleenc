gcc -c -ggdb *.c -Wall -std=c89 -Wextra
mv *.o ./compilation
cd compilation
gcc -o  ../build/aventure_c *.o -Wall -std=c89
cd ..