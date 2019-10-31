cp $1 ./std.cpp

g++ -o checker checker.cpp -O2
g++ -o std std.cpp -O2

if [ $? -ne 0 ]; 
then
   echo "fail to compile $1 as ./std.cpp"
   rm checker
   rm std.cpp
   exit
fi

for i in {1..20}
do
    ./checker <$i.in >checker.tmp
    mv checker.tmp $i.in
    echo "uniquilze $i.in."
    ./std <$i.in >$i.ans
    echo "rebuild $i.ans."
done

rm checker
rm std
rm std.cpp


