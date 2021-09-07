import time
import sys
import subprocess
import matplotlib.pyplot as plt

isGen = True
default_name = "bench_data_%d.dat"
records = [1000, 100000, 1000000]
languages = ['Bash', 'Python', 'C']
colors = {'Bash': "b", 'Python': "r", 'C': "g"}
suffix = {'Bash': ".sh", 'Python': ".py", 'C': ""}
prefix = {'Bash': "./", 'Python': "python3 ", 'C': "./"}


def generateData(name, records):
    cmd = "./generate-dataset.sh " + name + " " + str(records)
    t0 = time.time()
    subprocess.call(cmd, shell=True)
    return time.time() - t0


def sortData(name, language):
    cmd = prefix[language] + "sort-data" + suffix[language] + \
        " " + name + \
        " | awk '{print $5}' | tr -d 's'"
    dt = subprocess.check_output(cmd, shell=True, text=True)
    return float(dt.replace(',', '.'))


def generateAllData():
    generation_time = []
    for i in records:
        generation_time.append(generateData(default_name % (i), i))
    return generation_time


def generateAllStats():
    statistics = {}
    for l in languages:
        sort_time = []
        for i in records:
            sort_time.append(sortData(default_name % (i), l))
        statistics[l] = sort_time
    return statistics


def createGraph(generation_time, statistics):
    if (isGen):
        fig, axs = plt.subplots(2)
        axs[1].set_title("Generation Benchmark")
        axs[1].plot(records, generation_time)
        axs[1].set_xlabel('Records')
        axs[1].set_ylabel('Time in Seconds')
    else:
        fig, axs = plt.subplots()
        axs = [axs]

    axs[0].set_title("Sort Benchmark")
    for l in languages:
        axs[0].plot(records, statistics[l], colors[l] + "o-", label=l)
    axs[0].set_xlabel('Records')
    axs[0].set_ylabel('Time in Seconds')
    axs[0].set_xscale('log')
    axs[0].legend()

    fig.tight_layout()
    plt.savefig("benchmark_graph.png")
    plt.show()


if __name__ == "__main__":
    args = sys.argv[1:]

    if len(args) > 0:
        default_name = args[0]
        isGen = False

    generation_time = generateAllData() if isGen else None
    stats = generateAllStats()
    createGraph(generation_time, stats)
