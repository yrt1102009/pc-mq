ori_process_name=test
single_process_name=test_single 
multi_process_name=test_multi

rm *.o $single_process_name $multi_process_name $ori_process_name 2> /dev/null
runtimes=${1:-4096}

echo "run times is = $runtimes"
sed -i "s/const unsigned int MQ_SIZE.*/const unsigned int MQ_SIZE = $runtimes;/g"  template_mq.h

make clean 2> /dev/null
make

if [ ! -f $ori_process_name ]; then
	echo "single compile error;"
	exit 1
fi

mv $ori_process_name $single_process_name

if [ ! -f $single_process_name ]; then
	echo "single mv error;"
	exit 1
fi

make clean 2> /dev/null
make CFLAGS=-DMULTITHREAD

if [ ! -f $ori_process_name ]; then
	echo "multi compile error;"
	exit 1
fi

mv $ori_process_name $multi_process_name 

if [ ! -f $multi_process_name ]; then
	echo "multi mv error;"
	exit 1
fi
echo "single thread run time of $runtimes message:"
time ./$single_process_name 
echo "=================================="
echo "multi thread run time of $runtimes message:"
time ./$multi_process_name 
 