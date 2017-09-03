#!/bin/bash
tests=(*.tst);
for test in ${tests[@]};
do
  if [[
        $(../../tools/./HardwareSimulator.sh $test |
        grep -c "Comparison ended successfully") == 1
      ]];
  then
    echo $test " | PASSED";
  else
    echo $test " | FAIL";
  fi
done
