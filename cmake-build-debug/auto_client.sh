#!/bin/bash

rm threshold.csv
touch threshold.csv

for i in 5 10 25 50 75 100 125 150 175 200 250 350 500 650 800
do
./mul_client $i 
done


