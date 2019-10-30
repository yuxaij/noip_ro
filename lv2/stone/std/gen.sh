g++ -o make make.cpp -O2

./make 10 5 >1.in
./make 10 6 >2.in
./make 12 4 >3.in
./make 12 5 >4.in
./make 15 2 >5.in
./make 15 2 >6.in
./make 15 2 >7.in
./make 15 5 >8.in
./make 15 6 >9.in
./make 15 6 >10.in

g++ -o $1 $1.cpp -O2

for i in {1..10}
do
./$1 <$i.in >$i.ans
echo "finish $i"
done

rm $1
rm make
mv *.in ../data
mv *.ans ../data
