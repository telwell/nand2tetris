#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
tests=(*.tst);
for test in ${tests[@]};
do
  if [[
        $(../../../tools/./HardwareSimulator.sh $test |
        grep -c "Comparison ended successfully") == 1
      ]];
  then
    echo -e $test " | ${GREEN}P${NC}";
  else
    echo -e $test " | ${RED}F${NC}";
  fi
done
