#!/bin/bash
echo "first tests"


for i in {1..5}
do
  echo $i
  cat firstTests/test$i | ./a.out 100 | diff firstTests/wzor$i -

done
