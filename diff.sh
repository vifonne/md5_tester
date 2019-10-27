#!/bin/bash
rm -rf txt
letter="a"
max=100
multiplication_factor=45
echo "===== Tests $max times with letter $letter  ====="
sleep 1
for (( i=1; i<=$max; i++ ))
do
	echo "==== $i ===="
	echo -n "$letter" >> txt
	my=$(./ft_ssl md5 -q txt)
	or=$(md5 -q txt)
	difference=$(diff <(echo "$my") <(echo "$or"))
	if [ -z "$difference" ]
	then
		echo "OK"
	else
		echo "KO"
		echo $difference
		exit
	fi
	echo ""
done
echo "===== Tests $max with random text ====="
sleep 1
for (( i=1; i<=$max; i++ ))
do
	echo "==== $i ===="
	random=$(LC_CTYPE=C tr -dc A-Za-z0-9_\!\@\#\$\%\^\&\*\(\)-+= < /dev/urandom | head -c $(echo "$i*$multiplication_factor" | bc) | xargs)
	echo -n "$letter" >> txt
	my=$(./ft_ssl md5 -q txt)
	or=$(md5 -q txt)
	difference=$(diff <(echo "$my") <(echo "$or"))
	if [ -z "$difference" ]
	then
		echo "OK"
	else
		echo "KO"
		echo $difference
		exit
	fi
	echo ""
done
rm -rf txt
exit
