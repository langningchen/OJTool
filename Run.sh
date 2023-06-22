#!/bin/fish
cmake -B build
cmake --build build
set Username (cat ~/XMOJ/Username)
set Password (cat ~/XMOJ/Password)
./build/main -u $Username -p $Password -oj XMOJ -o GetQuestionDetail -q 1000
