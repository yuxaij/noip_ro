python3 make.py 1000 1.in normal normal onerep_ab5 reprep_all7 reprep_ab3
python3 make.py 1000 2.in normal normal onerep_ab4 reprep_all6 reprep_ab5
python3 make.py 200000 3.in normal onlyone1 onerep_ab4 reprep_all6 reprep_ab5
python3 make.py 200000 4.in normal onlyone20 onerep_ab4 reprep_all7 reprep_ab20
python3 make.py 200000 5.in kill_hash1 onlyone3 onerep_ab4 reprep_all6 reprep_ab100
python3 make.py 200000 6.in kill_hash1 onlyone2 onerep_ab4 reprep_all5 reprep_ab20
python3 make.py 1000000 7.in kill_hash1 kill_hash2 onerep_ab4 reprep_all4 reprep_ab10
python3 make.py 1000000 8.in kill_hash2 onlyone1 onerep_ab4 reprep_all100 reprep_ab5
python3 make.py 1000000 9.in kill_hash3 onlyone1 onerep_ab4 reprep_all67 reprep_ab32
python3 make.py 1000000 10.in onlyone1 onlyone2 onerep_ab4 onlyone3 reprep_ab10

g++ -o $1 ../$1.cpp -O2

for i in {1..10}
do
./$1 <$i.in >$i.ans
done

rm $1
mv *.in ../../data
mv *.ans ../../data

python3 make.py 0 0 0
