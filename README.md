# CS554 Homework \#0 : Linux & computer systems  

# Team members
- Ismail Elomari Alaoui
- Reda Chaguer

## Project structure
This project has our homework report where all questions are answered and screenshot, one Makefile to simplify intallation, compilation & execution and one source folder which contains 8 files (5 scipts & 3 generated data files):

- generate-data.sh 

- sort-data.sh

- sort-data.c

- sort-data.py 

- generate-graph.py

- dt_*.dt where * is in [1000, 100000, 10000000]

## Install Requirements
Our code requires some external libraries and packages which you might not have, such as gcc, pwgen, pandas ...

First of all, if you want to simplify usage, you are encouraged to install make if you do not have it on you computer, the command is `sudo apt install make`

In order to install all the requirements, naviguate to the root of the project and execute the following command `make install`

This command installs all the requirements and compiles the C code. You can recompile it, if needed, later using: `make compile` or the full command `gcc -Wall -Wextra src/sort-data.c -o sort-data`

## Instructions

- In order to generate data sets, you can use `make generate` which has predefined arguments. This command generates 3 files dt_*.dt where * is in [1000, 100000, 10000000]. Moreover, you can execute the data generation script manually as follow: `./src/generate-dataset.sh <output file name> <number of records>` if you are at the root of the project, or `./generate-dataset.sh <output file name> <number of records>` if you have naviguated to the source folder.

- In order to sort data using bash, you can use `make bash_sort` which sorts the 3 data files present in the source folder. Furthermore, you can sort the data of your custom file with the following command: `./src/sort-data.sh <input data file>`. Make sure your input data file is not a path (it should be just the name of the file and you have to execute the script from the same folder as this custom file) as our scripts return a file named `bash_sorted_<input data file>`. 

- In order to sort data using C, you can use `make c_sort` which sorts the 3 data files present in the source folder. Furthermore, you can sort the data of your custom file with the following command: `./src/sort-data <input data file>`. Make sure your input data file is not a path (it should be just the name of the file and you have to execute the script from the same folder as this custom file) as our scripts return a file named `C_sorted_<input data file>`. 

- In order to sort data using Python, you can use `make py_sort` which sorts the 3 data files present in the source folder. Furthermore, you can sort the data of your custom file with the following command: `./src/sort-data.py <input data file>`. Make sure your input data file is not a path (it should be just the name of the file and you have to execute the script from the same folder as this custom file) as our scripts return a file named `py_sorted_<input data file>`.

- You can also generate a graph for the time taken to generate the data and the time taken to sort the data at the 3 different scales across the 3 different approaches with one of the following commands: `make graph` or direcltly `./src/generate-graph.py`