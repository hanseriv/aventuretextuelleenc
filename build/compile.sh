cd ..
gcc -c *.c -Wall -std=c89 -Wextra  -Og 
mv *.o ./compilation
cd compilation
gcc -o  ../build/aventure_c *.o -std=c89 

