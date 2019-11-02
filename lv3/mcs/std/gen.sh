g++ -o make make.cpp -O2

./make 1000 1000 1 0 >1.in
./make 1000 1000 1 0 >2.in
./make 1000 1000 1 0 >3.in
./make 1000 1000 1 0 >4.in
./make 50000 100000 1 1 >5.in
./make 50000 100000 1 1 >6.in
./make 50000 100000 10 1 >7.in
./make 50000 100000 10 1 >8.in
./make 50000 100000 1 2 >9.in
./make 50000 100000 1 2 >10.in
./make 50000 100000 10 2 >11.in
./make 50000 100000 10 2 >12.in
./make 50000 100000 1 0 >13.in
./make 50000 100000 1 0 >14.in
./make 50000 100000 1 0 >15.in
./make 50000 100000 10 0 >16.in
./make 50000 100000 10 0 >17.in
./make 50000 100000 10 0 >18.in
./make 50000 100000 10 0 >19.in
./make 50000 3000000 1 0 >20.in

g++ -o $1 $1.cpp -O2

for i in {1..20}
do
./$1 <$i.in >$i.ans
echo "finish $i"
done

rm $1
rm make
mv *.in ../data
mv *.ans ../data
