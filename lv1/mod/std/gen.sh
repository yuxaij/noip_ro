g++ -o make make.cpp -O2
./make 100000 1000000 1 >1.in
./make 100000 1000000 1 >2.in
./make 10000 1000000 0 >3.in
./make 10000 1000000 0 >4.in
./make 10000 1000000 0 >5.in
./make 100000 10000000 2 >6.in
./make 100000 10000000 2 >7.in
./make 100000 10000000 2 >8.in
./make 100000 10000000 0 >9.in
./make 100000 10000000 0 >10.in

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
