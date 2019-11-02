
root=$PWD

shopt -s extglob

for d in */
do
    if [[ $d == lv* ]];
    then
        for p in $d*/
        do
            cd $p

            echo $p

            shopt -s extglob
            rm -r !(data|down|pre|resources|solution|statement|std|tables|conf.yaml)

            rm resources/* # no resources.
            rm pre/*       # no pres.

            cd $root
        done
    fi
    
done
