#!/bin/zsh
rm -rf txt
for (( i=1; i<=56; i++ ))
do
	echo "\n$i"
	/bin/echo -n "a" >> txt
	/bin/echo -n "MY: "
	echo $(./ft_ssl md5 -q txt)
	/bin/echo -n "OR: "
	echo $(md5 -q txt)
done
