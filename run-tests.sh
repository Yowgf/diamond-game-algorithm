# Input variables
STEM=$1
OUT=.$2
NUM_TESTS=$3
# Temporary output file
TMP_OUT=temp$OUT


# Test with all the testcases
for i in $(seq 0 $(( $NUM_TESTS - 1 )) ); do
	testin=$(printf $STEM$i$IN)
	testout=$(printf $STEM$i$OUT)
	echo $testin
	./tp2 ./testcases/$testin > $TMP_OUT 2> /dev/null
	if ! diff -qwB ./testcases/$testout $TMP_OUT &> /dev/null; then
		echo "Test $testin failed"
	else
		echo "Test $testin passed"
	fi
done;
# Remove temporary output
rm $TMP_OUT
