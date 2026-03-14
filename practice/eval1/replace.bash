#!/bin/bash

for file in `ls`; do
echo "on Replacing first a with #: "
echo $(sed 's/a/#/' $file)
done

