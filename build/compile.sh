cd ..
gcc -c *.c -Wall -std=c89 -Wextra -ggdb3  -Og -fsanitize=address
mv *.o ./compilation
cd compilation
gcc -o  ../build/aventure_c *.o -std=c89 
