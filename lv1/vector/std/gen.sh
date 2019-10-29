g++ -o make make.cpp -O2
./make 1000 1 >1.in
./make 999 1 >2.in
./make 8000 1 >3.in
./make 7894 1 >4.in
./make 99999 0 >5.in
./make 99998 0 >6.in
./make 100000 0 >7.in
./make 99999 1 >8.in
./make 99998 1 >9.in
./make 100000 1 >10.in

g++ -o $1 $1.cpp -O2

for i in {1..10}
do
./$1 <$i.in >$i.ans
done

rm make
rm $1
mv *.in ../data
mv *.ans ../data
