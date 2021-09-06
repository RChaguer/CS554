import pandas as pd
import os, sys, time

def usage():
    print('Usage: ' + sys.argv[0] + ' <file>')

def sort(filename):
    # Verify File Existence
    if not os.path.exists(filename):
        print("Error : " + filename + " does not exist.")

    # Output Configuration
    outputFilename = "sorted_" + filename  

    # Read and Sort Data File 
    df = pd.read_csv(filename, index_col=False , header=None, names=['int32', 'string'], sep=' ')
    df = df.sort_values(by=['int32'])

    # Delete File if exists
    if os.path.exists(outputFilename):
        os.remove(outputFilename)
    
    # Export Sorted File
    df.to_csv(outputFilename, header=False, index=False, sep=' ')
    

if __name__ == "__main__":
    # Input Arguments Verification
    args = sys.argv[1:]

    if len(args) < 1:
        usage()
        exit(-1)  

    t0 = time.time()

    # Main function
    sort(args[0])

    execution_time = time.time() - t0
    print("Execution Time : " , execution_time)
