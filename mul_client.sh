touch threshold.csv
./mul_client 10 >> threshold.csv
./mul_client 25 >> threshold.csv

for((i=1;i<20;i++)){
((b_size=i*50))
./mul_client $b_size >> threshold.csv
cat threshold.csv
}

