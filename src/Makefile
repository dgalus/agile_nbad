all:
	g++ sniffer/*.cpp -o ../bin/sniffer -lpthread -lsqlite3 -ldl -std=c++17
	../bin/sniffer ../config/sample.json
	cd ../bin
	python3 -m venv venv
	./venv/bin/pip install -r ../src/anomaly_detection/requirements.txt
	cd ../src

install:
	echo "install"

clean:
	rm ../bin/*
	rm *.o


