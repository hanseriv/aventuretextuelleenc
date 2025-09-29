cd ..
gcc -c *.c -Wall -std=c89 -Wextra  -Og -ggdb -fsanitize=address
mv *.o ./compilation
cd compilation
gcc -o  ../build/aventure_c_debug *.o -std=c89 -fsanitize=address -static-libasan

