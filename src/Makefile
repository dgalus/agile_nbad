all:
	#sudo pacman -Sy geoip
	g++ sniffer/*.cpp -o ../bin/sniffer -lpthread -lsqlite3 -ldl -std=c++17
	g++ pcap_analyzer/*.cpp -o ../bin/pcap_analyzer -lpthread -lsqlite3 -ldl -std=c++17
	g++ port_scanner/*.cpp -o ../bin/port_scanner -lpthread -ldl -std=c++17
	#g++ message_router/*.cpp -o ../bin/message_router -lpthread -lsqlite3 -ldl -std=c++17
	#../bin/sniffer ../config/sample.json
	#cd ../bin
	#python3 -m venv venv
	#./venv/bin/pip install -r ../src/anomaly_detection/requirements.txt
	#cd ../src

install:
	echo "install"

clean:
	rm ../bin/*
	rm *.o


