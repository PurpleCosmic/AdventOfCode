cat day3input | paste -s | sed "s/\(do()\|don't()\)/\n\1/g" | grep 'do()' | grep -Eo 'mul\([0-9]{1,3},[0-9]{1,3}\)' | sed 's/mul(\([0-9][0-9]*\),\([0-9][0-9]*\).*$/\1*\2/g' | paste -sd+ | bc
