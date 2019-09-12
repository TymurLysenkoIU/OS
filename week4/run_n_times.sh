for i in `seq 1 $1`;
do
  echo "$i: running $2:"
  $2
done
