CFLAGS=-Wall -Wextra
SRC_DIR=src/

all: install

install:
	sudo apt install python3-pip pwgen gcc
	sudo pip3 install pandas
	gcc $(CFLAGS) sort-data.c -o sort-data

compile: sort-data.c
	gcc $(CFLAGS) sort-data.c -o sort-data

generate:
	@echo Start Generating Data 
	@echo 1.000 Record DataSet ...
	generate-dataset.sh dt_1000.dat 100
	@echo 100.000 Record DataSet ...
	generate-dataset.sh dt_100000.dat 100
	@echo 10.000.000 Record DataSet ...
	generate-dataset.sh dt_10000000.dat 100
	@echo End of Data Generation

sort_all: bash_sort c_sort py_sort

graph: generate-graph.py
	@python3 generate-graph.py

sort_graph: generate-graph.py
	@python3 generate-graph.py dt_%d.dt
	
bash_sort:
	@echo ================== Bash Sort ==================
	@echo 1000 Records
	@./sort-data.sh dt_1000.dt
	@echo 100000 Records
	@./sort-data.sh dt_100000.dt
	@echo 10000000 Records
	@./sort-data.sh dt_10000000.dt 
	@echo ================================================


c_sort:
	@echo ==================== C Sort ====================
	@echo 1000 Records
	@./sort-data dt_1000.dt
	@echo 100000 Records
	@./sort-data dt_100000.dt 
	@echo 10000000 Records
	@./sort-data dt_10000000.dt
	@echo =================================================

py_sort:
	@echo ================== Python Sort ==================
	@echo 1000 Records
	@python3 sort-data.py dt_1000.dt
	@echo 100000 Records
	@python3 sort-data.py dt_100000.dt
	@echo 10000000 Records
	@python3 sort-data.py dt_10000000.dt 
	@echo =================================================


clean:
	rm -rf *sorted*