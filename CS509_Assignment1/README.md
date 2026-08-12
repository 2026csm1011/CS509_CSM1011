Assignment 1 - Matrix Multiplication and CSR Graph

It covers basic matrix multiplication, blocked matrix multiplication for better performance, and converting graph edge lists into Compressed Sparse Row (CSR) format.

Files Included

1:-Driver/main.cpp: Main program file that takes arguments to run either GEMM or CSR.

2:-src/simple_gemm.cpp: Simple matrix multiplication logic.

3:-src/blocking_gemm.cpp: Blocked matrix multiplication logic.

4:-src/csr.cpp: Converts graph files to CSR format (row_ptr, col_idx, values).

5:-src/generator.cpp: Generates test text files for matrices and graphs.

6:-menu.cpp: A simple menu-driven interface to run everything easily.

7:-tests/: Folder containing sample input text file

Step to Compile and Run (run all this commond in terminal under CS509_Individual)

Step 1: Generate Test Cases

a:-) g++ -std=c++11 CS509_Assignment1/src/generator.cpp -o generator.exe

b:-) ./generator.exe

it will generate test cases according to given input so that all required input matrices and graph text files are ready.

Step 2: Compile the program
Open your terminal in the project folder and run this command:

a:-) g++ -std=c++11 common_wrapper/wrapper.cpp CS509_Assignment1/src/simple_gemm.cpp CS509_Assignment1/src/blocking_gemm.cpp CS509_Assignment1/src/csr.cpp -o wrapper.exe

Step 3: Step 3: Run the Common Wrapper & Select Assignment1 option to excute (run its in common_wrapper)

a:-) ./wrapper.exe

then option visible to select:

1. Run Assignment 1
0. Exit

after selectig option 1, there will be option visible:

1. Run GEMM (Simple & Blocking)
2. Run CSR Graph Test
0. Exit

now select and according to availble test cases give input and see output with excution time.


