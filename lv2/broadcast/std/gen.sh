g++ -o make random_make.cpp -O2

./make 300 30 >1.in
./make 1000 100 >2.in
./make 2000 300 >3.in
./make 20000 2000 >4.in
./make 20000 30000 >5.in 
./make 100000 8000 >6.in
./make 100000 10000 >7.in
./make 1000000 100000 >8.in
./make 1000000 50000 >9.in
./make 1000000 100000 >10.in

g++ -o $1 $1.cpp -O2

for i in {1..10}
do
echo $i
./$1 <$i.in >$i.ans
done

rm make
rm $1
mv *.in ../data
mv *.ans ../data

