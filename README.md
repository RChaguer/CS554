# CS554 Homework \#0 : Linux & computer systems

# Team members

- Ismail Elomari Alaoui
- Reda Chaguer

## Project structure

This project has our homework report where all questions are answered and screenshot and a source folder which contains a graph [benchmark_graph.png](src/benchmark_graph.png) representing generation & sorting times for all combinations and 6 files (5 scipts & a makefile to simplify intallation, compilation & execution):

- [Makefile](src/Makefile)

- [generate-data.sh](src/generate-data.sh)

- [sort-data.sh](src/sort-data.sh)

- [sort-data.c](src/sort-data.c) (The compiled executable [sort-data](src/sort-data) is also present)

- [sort-data.py](src/sort-data.py)

- [generate-graph.py](src/generate-graph.py)

## Install Requirements

Our code requires some external libraries and packages which you might not have, such as gcc, pwgen, pandas ...

First of all, if you want to simplify usage, you are encouraged to install "make" if you do not have it on you computer, the command is `sudo apt install make`

Furthermore, the minimal _python_ version required for this project is **3.8**.

Moreover, in order to install all the requirements, naviguate to the **source folder** of the project and execute the following command `make install`

This command installs all the requirements and compiles the C code. You can recompile it later, if needed, using: `make compile` or the full command `gcc -Wall -Wextra sort-data.c -o sort-data`

## Instructions

- To simplify execution, the Makefile is inside the source folder. So, naviguate to **src** before executing the commands shown below.

- In order to generate data sets, you can use `make generate` which has predefined arguments. This command generates 3 files dt\__.dat where _ is in [1000, 100000, 1000000]. Moreover, you can execute the data generation script manually as follow: `./generate-dataset.sh <output file name> <number of records>`.

- In order to sort data using bash, you can use `make bash_sort` which sorts the 3 data files present in the source folder. Furthermore, you can sort the data of your custom file with the following command: `./sort-data.sh <input data file>`. Make sure your input data file is not a path (the custom data file should be inside **src**). Thus, the execution of one of these commands returns a file named `bash_sorted_<input data file>`.

- In order to sort data using C, you can use `make c_sort` which sorts the 3 data files present in the source folder. Furthermore, you can sort the data of your custom file with the following command: `./sort-data <input data file>`. Make sure your input data file is not a path (the custom data file should be inside **src**). Thus, the execution of one of these commands returns a file named `C_sorted_<input data file>`.

- In order to sort data using Python, you can use `make py_sort` which sorts the 3 data files present in the source folder. Furthermore, you can sort the data of your custom file with the following command: `./sort-data.py <input data file>`. Make sure your input data file is not a path (the custom data file should be inside **src**). Thus, the execution of one of these commands returns a file named `py_sorted_<input data file>`.

- You can also generate a graph for the time taken to generate the data and the time taken to sort the data at the 3 different (and more 100, 1000, 10000, 100000, 1000000,10000000) scales across the 3 different approaches with one of the following commands: `make graph`. Make sure your input data file is not a path (the custom data file should be inside **src**).

If the data files are already present in the source folder (named dt\__.dat where _ is the scale of records), you can simply execute `make sort_graph` to get a graph representing just the time taken to sort the data at the 3 different scales across the 3 different approaches. This command does not return a graph for the data generation time.
