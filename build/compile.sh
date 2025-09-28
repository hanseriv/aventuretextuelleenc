cd ..
gcc -c *.c -Wall -std=c89 -Wextra -ggdb3  -Og 
mv *.o ./compilation
cd compilation
gcc -o  ../build/aventure_c *.o -std=c89 -w 
