find ./robot -iname "*.h" -exec bash -c 'scp -C {} robot@192.168.2.3:/home/robot/ev3_robot/$(ls {} | cut -c 3-;)' \;
find ./robot -iname "*.c" -exec bash -c 'scp -C {} robot@192.168.2.3:/home/robot/ev3_robot/$(ls {} | cut -c 3-;)' \;
#ssh robot@192.168.2.3 "cd ev3_robot; make;"
