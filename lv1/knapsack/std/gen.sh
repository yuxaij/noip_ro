g++ -o make make.cpp -O2
./make 10 1000 98 100 0 >1.in
./make 1000 1000 96 150 0 >2.in
./make 10 200000 100 200 1 >3.in
./make 1000 200000 99 250 1 >4.in
./make 10 200000 97 150 2 >5.in
./make 1000 200000 94 200 2 >6.in
./make 10 200000 92 170 0 >7.in
./make 1000 200000 91 280 0 >8.in
./make 10 200000 90 160 0 >9.in
./make 200000 200000 100 200 0 >10.in

g++ -o $1 $1.cpp -O2

for i in {1..10}
do
./$1 <$i.in >$i.ans
done

rm make
rm $1
mv *.in ../data
mv *.ans ../data
