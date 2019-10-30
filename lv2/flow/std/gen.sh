declare -a pn=(-1, 100, 100, 100, 1000, 2000, 50000, 50000, 50000, 50000, 50000)
declare -a pm=(-1, 400, 400, 400, 4000, 8000, 200000, 200000, 200000, 200000, 200000)
declare -a pc=(-1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1)

declare -a pt=(-1, 0, 1, 3, 10, 100000) 

g++ -o make_case make_case.cpp -O2

for i in {1..10}
do
    for j in {1..5}
    do
        ./make_case ${pn[$i]} ${pm[$i]} ${pt[$j]} ${pc[$i]} >${j}_${i}.cs
        sleep 1
    done
python make.py $i
done

g++ -o $1 $1.cpp -O2

for i in {1..10}
do
./$1 <$i.in >$i.ans
echo "finish $i"
done

rm $1
rm make_case
rm *.cs
mv *.in ../data
mv *.ans ../data
