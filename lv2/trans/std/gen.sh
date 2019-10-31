g++ -o make make.cpp -O2

declare -a ps=(1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000)

./make 200 80 ${ps[1]} ${ps[2]} >1.in
./make 300 100 ${ps[7]} ${ps[9]} >2.in
./make 1400 720 ${ps[2]} ${ps[3]} >3.in
./make 1500 564 ${ps[6]} ${ps[9]} >4.in
./make 4800 3179 ${ps[3]} ${ps[4]} >5.in
./make 5000 2286 ${ps[7]} ${ps[9]} >6.in
./make 200000 128731 ${ps[5]} ${ps[6]} >7.in
./make 200000 92263 ${ps[8]} ${ps[9]} >8.in
./make 3000000 950000 ${ps[6]} ${ps[7]} >9.in
./make 3000000 900000 ${ps[4]} ${ps[9]} >10.in

g++ -o $1 $1.cpp -O2

for i in {1..10}
do
./$1 <$i.in >$i.ans
echo "fin $i."
done

rm $1
mv *.in ../data
mv *.ans ../data
rm make
