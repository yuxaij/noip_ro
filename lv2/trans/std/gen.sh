echo -e "8 4\n0" >1.in
echo -e "18 30\n18" >2.in
echo -e "16 12\n8" >3.in
echo -e "49 49\n0" >4.in
echo -e "48 48\n0" >5.in
echo -e "50 100\n50" >6.in
echo -e "48 39\n13" >7.in
echo -e "49 67\n38" >8.in
echo -e "198 320\n173" >9.in
echo -e "200 250\n132" >10.in

g++ -o $1 $1.cpp -O2

for i in {1..10}
do
./$1 <$i.in >$i.ans
done

rm $1
mv *.in ../data
mv *.ans ../data
