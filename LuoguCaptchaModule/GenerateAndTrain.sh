#!/bin/bash
for i in {1..100}
do
    python ./GenerateData.py 10 24 1000
    echo "GenerateData $i% done"
done
python ./Train.py