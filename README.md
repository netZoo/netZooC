README file for PANDA_v2.c.
Written by Kimberly Glass (kglass@jimmy.harvard.edu), available under GPL.  As academic code it is provided without warranty.  Please contact the author with any comments/questions/concerns.
Last updated July, 2014.

PANDA is written in c++ and can be compiled by:
g++ PANDA_vc.c -o PANDA
To improve runtime speed, it is also highly encouraged to include an optimazation flag:
g++ PANDA_v2.c -O3 -o PANDA

Running the program without any parameters will return a usage function:

./PANDA
Useage ./PANDA
-e (required) file of expression values (can alternately be a list of gene names)
-m (required) pair file of motif edges
-p (optional) pair file of PPI edges
-o (optional) tag for output files
-a (optional) value to be used for update variable, alpha (default=0.1)
Additional options (see README): 
-k (optional) kill the program after it has run k steps (default=1000)
-n (optional) output a "stats" file every n steps (default, no stats file)
-w (optional) file with list of covariate weights
-l (optional) leave out the lth sample when building the network
-j (optional) retain only j samples when building the network
-r (optional) randomization options
-s (optional) value to seed the random number generator (defaults to system time)
-v (optional) verbose output options

There are two required parameters, the names for two input files: a tab-delimited text file with the gene expression values and a tab-delimited text file with motif information.  You may also choose to specify an string to generate output file names, the default value for this is "PANDA_prediction".

examples:
./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -o ToyOutput
./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -p ToyPPIData.txt -a 0.25 -o ToyOutput

Running these examples will produce a network file: ToyOutput_FinalNetwork.pairs

DATA:
Within the "YeastData" directory, the file "YeastNetwork_allTFxGene" contains the final z-score edge weights for the networks analyzed in "Passing Messages between Biological Networks to Refine Predicted Interactions."  This folder also contains the expression, motif and PPI data files used to generate the networks.  Please see the supplemental material of the publication for more information on this data.

The "ToyData" directory has some small 'toy' datafiles that can be used to quickly run/understand PANDA.

FILE FORMATS:
Expression data file: In the expression data file the first column must contain gene names, and each subsequent column should contain expression values for those genes across conditions/samples (see "ToyExpressionData.txt").  Note that if fewer than three conditions are contained in the expression data file, PANDA will initialize the co-regulatory network to an identity matrix. This file can also contain header lines, so long as those lines are preceeded by a hashtag (#).

Motif data file: The motif data file contains three columns (see "ToyMotifData.txt").  The first column should contain regulators, the second those regulator's target genes, and the third, an initial weight to give the interactions (recommend 1).  Any potential regulator to gene interaction not specified in this file is given a default interaction weight of 0.  Any interaction that is multiply defined will be given a weight equal to the sum of the weights given to the instances of that interaction.  Note that PANDA will give an warning message if a gene in the motif file is not contained in the expression data file. This file cannot contain header lines.

Protein interaction file: The protein interaction file (optional) contains three columns (see "ToyPPIData.txt").  The first two columns should contain a pair of regulators, and the third, an initial weight to give the interactions (recommend 1).  Note that the program will give an warning message if a regulator in this file is not contained in the motif data. This file cannot contain header lines.

Outputted network files (including "stats" files):  The network files contain four columns:
TF \t Gene \t Motif-prediction \t PANDA-prediction
The values in the fourth, "PANDA-prediction", column, can loosely be interpreted as Z-scores.

ADDITIONAL OPTIONS:
PANDA allows the user to specify a number of options. Some of these have been implemented as we apply the PANDA algorithm to other systems.  Any comments/questions/suggestions are welcomes (email: kglass@jimmy.harvard.edu).

"-a" allows a user to specify a different value for the update parameter, alpha.  Larger values of alpha causes quicker convergence, and often greater "mixing" of motif and non-motif edges.  Recommend values between 0.05 and 0.25. (Author note: The default of 0.1 was chosen since as ChIP-seq validation of human networks appears to show this gives the most accurate results. However for quicker analysis I strongly suggest starting with 0.25 as there is only a small loss in accuracy but an immense speed-up in time).
example: ./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -a 0.25 -o ToyOutput

"-k" sets the maximum number of iterations PANDA can run before exiting.
example: ./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -k 2 -o ToyOutput

"-n" tells PANDA to print the network every N steps, instead of just the final predicted network.
example: ./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -n 5 -o ToyOutput

"-w" triggers PANDA to calculate a weighted Pearson (in lieu of the standard Pearson correlation), using weights specified in a "covariate weight file."  The file should contain a single column of numbers.  Each row in the file corresponds directly to a column in the expression data file.
example usage: ./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -w ToyWeights.txt -o ToyOutput

"-l" can be used to leave out a specified expression sample when building the network. 1 leaves out the first sample, 2 leaves out the second sample, etc.
example usage: ./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -l 10 -o ToyOutput (leaves out the 10th column of the expression data when building the network)

"-j" can be used to jack-knife (random sampling without replacement) the samples in the original expression data. The value indicates the number of samples to use building the network, so this value should be less than the total number of samples and greater than two (since one needs at least three data points to calculate a correlation).
example usage: ./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -j 40 -o ToyOutput (chooses 40 random expression samples/conditions to build network)

"-r" allows the user to specify several different randomization options.  "-r 1" swaps gene labels, such that each row in the expression data is assigned to a random gene.  "-r 2" swaps condition labels, such that each column in the expression data is assigned to a random weight value in the covariate weight file.  "-r 3" assigns each condition a random weight value and prints out these values.  If used in conjuction with the "-w" option, only conditions that have an original weight value greater than zero are assigned random weight values.
examples: ./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -r 1 -o ToyOutput
./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -w ToyWeights.txt -r 2 -o ToyOutput

"-s" allows the user to seed the random number generator (which otherwise defaults to the current system time). Must be an integer greater than zero.
example: ./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -r 1 -s 1000 -o ToyOutput

"-v" triggers several verbose output options.  "-v 1" tells PANDA to print out the mean and standard-deviation of the availability and responsibility at each iteration.  "-v 2" tells PANDA to write files containing all three networks (gene-gene co-regulatory, TF-gene regulatory, and TF-TF co-regulating) at both the initial and final states (producing six files).  The gene-gene co-regulatory networks can be very large, so use this option with caution.
example usage: ./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -v 1 -o ToyOutput
