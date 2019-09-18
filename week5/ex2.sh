touch file

while true
do
  if ln file file.lock
  then
    last_num=$(tail -n 1 file)
    echo $(($last_num + 1)) >> file

    rm file.lock
  fi
done
