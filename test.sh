#!/bin/bash
echo "first tests"


for i in {1..5}
do
  echo $i
  cat tests/firstTests/test$i | ./a.out 100 | diff tests/firstTests/wzor$i -

done
echo "other tests"
for i in {1..10}
do
echo $i
cat tests/testyFB/d$i | ./a.out 16 | diff tests/testyFB/W$i -

done
