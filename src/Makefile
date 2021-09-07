CFLAGS=-Wall -Wextra
SRC_DIR=src/

all: install

install:
	sudo apt install python3-pip pwgen gcc
	sudo pip3 install pandas matplotlib
	gcc $(CFLAGS) sort-data.c -o sort-data

compile: sort-data.c
	gcc $(CFLAGS) sort-data.c -o sort-data

generate:
	@echo Start Generating Data 
	@echo 1.000 Record DataSet ...
	generate-dataset.sh dt_1000.dat 1000
	@echo 100.000 Record DataSet ...
	generate-dataset.sh dt_100000.dat 100000
	@echo 10.000.000 Record DataSet ...
	generate-dataset.sh dt_1000000.dat 1000000
	@echo End of Data Generation

sort_all: bash_sort c_sort py_sort

graph: generate-graph.py
	@python3 generate-graph.py

sort_graph: generate-graph.py
	@python3 generate-graph.py dt_%d.dat

bash_sort:
	@echo ================== Bash Sort ==================
	@echo 1000 Records
	@./sort-data.sh dt_1000.dat
	@echo 100000 Records
	@./sort-data.sh dt_100000.dat
	@echo 1000000 Records
	@./sort-data.sh dt_1000000.dat 
	@echo ================================================


c_sort:
	@echo ==================== C Sort ====================
	@echo 1000 Records
	@./sort-data dt_1000.dat
	@echo 100000 Records
	@./sort-data dt_100000.dat 
	@echo 1000000 Records
	@./sort-data dt_1000000.dat
	@echo =================================================

py_sort:
	@echo ================== Python Sort ==================
	@echo 1000 Records
	@python3 sort-data.py dt_1000.dat
	@echo 100000 Records
	@python3 sort-data.py dt_100000.dat
	@echo 1000000 Records
	@python3 sort-data.py dt_1000000.dat 
	@echo =================================================


clean:
	rm -rf *sorted*