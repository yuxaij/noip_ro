echo "4 1">1.in
echo "5 1" >2.in
echo "10 6" >3.in
echo "12 6" >4.in
echo "11 50" >5.in 
echo "9 50" >6.in
echo "47 6" >7.in
echo "50 6" >8.in
echo "48 50" >9.in
echo "49 50" >10.in

g++ -o $1 $1.cpp -O2

for i in {1..10}
do
./$1 <$i.in >$i.ans
done

rm $1
mv *.in ../data
mv *.ans ../data
