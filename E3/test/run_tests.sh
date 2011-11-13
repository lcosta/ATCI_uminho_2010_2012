
while true
do 
    clear
    date
    gcc ./test_manager.c -o test_manager.c.bin && ./test_manager.c.bin && rm -f test_manager.c.bin
    sleep 10
done


#for file in ./test_*
#do
#	#if [ "${file}" == "/etc/resolv.conf" ]
#	#then
#		#countNameservers=$(grep -c nameserver /etc/resolv.conf)
#		
#		echo ${file}
#        gcc ${file} -o $(echo "${file}.bin")
#		
#		#break
#	#fi
#done

#find . -name "test_*" -exec gcc  -o  && cd build && ./$APP_EXE {} \;


#for test in `find . -name "test_*"`
#do
#        
#        
#        
#        if [ "$(ls $test)" ]
#        then
#                echo "$dirname is not empty; no action taken"
#        else
#                echo $test
#        fi
#done