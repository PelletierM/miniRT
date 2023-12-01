#!/bin/sh

GREEN="\033[0;32m"
RED="\033[0;31m"
WHITE="\033[0m"

echo -e "\n---- Testing with test_parsing ----\n"
for file in "./invalid"/*; do
	echo -e "${WHITE}$file"
	LINES=$(2>&1 ./test_parsing $file | grep "Error" | wc -l)
	if [ "$LINES" -gt 0 ]; then
		echo -e "${GREEN}Test passed\n"
	else
		echo -e "${RED}Test failed\n"
	fi
done
