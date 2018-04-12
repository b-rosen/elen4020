The github repo can be accessed thusly:

https://github.com/b-rosen/elen4020.git

Use the "Lab 3 - Final (Amended)" commit for both the code and reports branches (the older one is incorrect)

README.txt on the master branch will give instructions on how to access the lab submissions.

We have used python 3 for this lab, with the mrjob mapreduce library.

IMPORTANT! The code is not designed to run in parallel. They will only work if the code is run inline. Additionally, do NOT run the code with any flags in the command. Only use the commands given in this file.

##########################################################################################

To use the multiplication algorithm run:

python (or python3) algorithmName.py inputfile.txt inputfile2.txt > outputfile.txt

replacing the placeholder names appropriately. Note that the first input file must contain an A and the second a B for it to function properly. Algorithm-A.py and Algorithm-B.py are the two algorithms, while GraphCount.py is used for the graph node length calculator. matrixGenerator.py is used to generate the small and large matrix test files, while SquareMatrix.py is used to multiply a matrix by itself.

##########################################################################################

To perform the cubing of the matrix for the graph section:

1. Run SquareMatrix.py with the input file and output to another file (say "temp.txt").

2. Run GraphCount.py with temp.txt and the original input file as an input and another file as output (say "out.txt"). Ensure that the first input file is named 'outNetwork.list'. This will print the connected nodes with paths of length 3, as well as the count of paths with length 3. The results are only shown once (i.e. 32 43 means there is a bi-directional connection).