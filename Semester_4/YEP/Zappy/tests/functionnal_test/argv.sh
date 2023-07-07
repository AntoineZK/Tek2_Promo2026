#!/bin/bash

make re -C ../../

./../../zappy_server -p 8 -x 10 -y 10 -n team1 team2 -c 2 -f 100 > ../test_bash/test1.txt

sdiff -s ../test_bash/test1.txt ../test_bash/expect1.txt

if [ $? -eq 0 ]
then
    echo -e "\e[1;32mTest 1: OK\e[0m" ; sleep 0.2
else
    echo -e "\e[1;31mTest 1: KO\e[0m" ; sleep 0.2
fi

./../../zappy_server -p 2021 -x 10 -y 30 -n -c 2 -f 100 > ../test_bash/test2.txt

sdiff -s ../test_bash/test2.txt ../test_bash/expect2.txt

if [ $? -eq 0 ]
then
    echo -e "\e[1;32mTest 2: OK\e[0m" ; sleep 0.2
else
    echo -e "\e[1;31mTest 2: KO\e[0m" ; sleep 0.2
fi

./../../zappy_server -p 2021 -x 10 -y 40 -n team1 team2 -c 2 -f 100 > ../test_bash/test3.txt

sdiff -s ../test_bash/test3.txt ../test_bash/expect3.txt

if [ $? -eq 0 ]
then
    echo -e "\e[1;32mTest 3: OK\e[0m" ; sleep 0.2
else
    echo -e "\e[1;31mTest 3: KO\e[0m" ; sleep 0.2
fi

./../../zappy_server -p 2021 -x -1 -y 30 -n team1 team2 -c 2 -f 100 > ../test_bash/test4.txt

sdiff -s ../test_bash/test4.txt ../test_bash/expect3.txt

if [ $? -eq 0 ]
then
    echo -e "\e[1;32mTest 4: OK\e[0m" ; sleep 0.2
else
    echo -e "\e[1;31mTest 4: KO\e[0m" ; sleep 0.2
fi

./../../zappy_server -p 2021 -x -1 -y 30 -n team1 team2 -c -f 100 > ../test_bash/test5.txt

sdiff -s ../test_bash/test5.txt ../test_bash/expect5.txt

if [ $? -eq 0 ]
then
    echo -e "\e[1;32mTest 5: OK\e[0m" ; sleep 0.2
else
    echo -e "\e[1;31mTest 5: KO\e[0m" ; sleep 0.2
fi

./../../zappy_server > ../test_bash/test6.txt

sdiff -s ../test_bash/test6.txt ../test_bash/expect6.txt

if [ $? -eq 0 ]
then
    echo -e "\e[1;32mTest 6: OK\e[0m" ; sleep 0.2
else
    echo -e "\e[1;31mTest 6: KO\e[0m" ; sleep 0.2
fi

make fclean -C ../../

rm -f ../test_bash/test1.txt
rm -f ../test_bash/test2.txt
rm -f ../test_bash/test3.txt
rm -f ../test_bash/test4.txt
rm -f ../test_bash/test5.txt
rm -f ../test_bash/test6.txt
