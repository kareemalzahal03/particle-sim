/usr/bin/arch -x86_64 g++ -std=c++20 src/* -I include/ -I/usr/local/Cellar/sfml/2.6.1/include -o prog -L/usr/local/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
./prog
#g++ src/* -I include/ -I/usr/local/Cellar/sfml/2.6.1/include -o prog -L/usr/local/lib/ -lsfml-graphics -lsfml-system -lsfml-window
