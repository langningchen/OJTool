#!/bin/fish
echo -e "\033[33m"
echo "OJ  Copyright (C) 2024  langningchen"
echo "This program comes with ABSOLUTELY NO WARRANTY."
echo "This is free software, and you are welcome to redistribute it under certain conditions."
echo -e "\033[0m"

cmake -B Build
cmake --build Build