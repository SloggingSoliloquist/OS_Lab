#!/bin/bash

read -p "Enter operand1 operation operand2: " a op b

case $op in
+) res=$(echo "$a $op $b" | bc -l);;
-) echo "sum= $(expr $a - $b)" ;;
\*) res=$(echo "$a $op $b" | bc -l) ;;
/) res=$(echo "$a $op $b" | bc -l) ;;
%) res=$(echo "$a $op $b" | bc -l) ;; 
esac




