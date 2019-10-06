# Functions

## PANDA

Description:

	PANDA is an algorithm that creates gene regulatory network through passing messages between gene expression networks,
	TF-Gene motif priors, and TF-TF PPI networks.

Inputs:

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

Outputs:

	(tag_for_output_file)_FinalNetwork.pairs: Bipartite gene-TF regulatory network where
	each line represents an edge in the graph (a TF-GENE pair).

Examples: 

	./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -o ToyOutput
	./PANDA -e ToyExpressionData.txt -m ToyMotifData.txt -p ToyPPIData.txt -a 0.25 -o ToyOutput

Publications:

	https://doi.org/10.1371/journal.pone.0064832

Authors:

	Kimberley Glass

Changelog:

	Version 1 Modifications (May 2013):
	1) added "randomseed" variable which allows the user to specific the random number generator seed
	("srand(randomseed)").  This is useful when doing paired randomizations (e.g. if one wants the gene labels to
	be swapped the same way for two different sets of input data).
	2) added in a second method of randweights (randweight=2 set by specifying -r 3 at the command prompt).  This
	generates a random-weight value for any covariate weight that was initially greater than zero, but leaves
	zero weights unchanged.
	3) Removed criteria that a protein in the PPI must be a member of the regulatory prior.  Instead add in any
	"new" proteins into the regulatory prior assuming no known regulatory interactions.
	4) Removed criteria that the TF/motif in the regulatory prior must also be a gene in the expression data. 
	This allows regulators to take names that aren't gene names (e.g. a regulator could be TAL1::GATA1, but the
	genes are in RefSeq annotation).  One limitation is that correlation in expresion levels between "TFs" and
	genes is no longer calculated.  This information, however, was never used by PANDA, so removing the
	calculation had the added benefit of freeing up memory.
	5) added in another verboseoutput option.  Now setting "-v 2" at the command prompt will cause PANDA to print
	out additional files recording the initial and final protein-interaction and co-regulatory networks.  Changed
	the behavior of the code such that an initial regulatory network is only printed out when using this option.
	6) Increased the number of Regulators allowed by Program to 1000.
	7) Modified function that reads in regulatory and co-regulating information such that it can handle
	multiple instances.  Single instances in the input files will result in the initial value being set equal to
	the value in the "weight" column.  If an interaction is multiply defined, the initial value will be set
	equal to the sum of values associated with these instances in the "weight" column.  Undefined instances
	are given a default value of 0.
	Version 2 Modifications (July 2014):
	1) added in "LeaveOutSample" to leave out a single sample from the network reconstruction.
	2) fixed missing string termination that could cause the terminal window to become bold.
	3) added in the "JackKnife" option to designate number of samples to use in a jack-knife network.
	4) modified the ReadInExpression function to allow users to add additional rows to their expression file (likely
	header rows), so long as the first character in these rows is a hashtag (#).
	5) Changed length of "TF" in regulation struct to be 64 characters, in preparation to longer miRNA names.
	6) Created default value for outtag so that the -o command-line option is now optional instead of required.
	7) Defined MAXGENES, MAXTFS, MAXCONDITIONS, BUFSIZE, and MAXPATHLENGTH to allow easier manipulation of these
	values should they need to be altered.
	8) Added some additional outputs that tell the user what the code is doing.
	9) Put in catch when normalizing the prior for the case where a TF and its potential target gene both have no
	targets/inputs (variance of 0 in the prior).
	10) removed index, indegree and outdegree parts of the genes and regulation structures as they were not being used.
	11) Restructured code so that there are much fewer global variables and most are declared locally.
	12) Modified ReadInExpression function to sum over multiple entries of a gene in the expression file.
	13) Added in program exits triggers for if input files have more than MAXGENES MAXTFS or MAXCONDITIONS.
	Potential Future improvements:
	* change the Genes.corr and Regulation.P from symmetrix matrices to vectors to save on memory space (especially
	for the former)
	* remove the exp and stderr portions of the Genes and Regulation structs and make them local vectors (currently
	they are only used to normalize the initial PPI and corr matrices and nothing else).
	* parralize the code by adding options for multi-threading for-loops using the openmp library, shoud enhance speed.

## PUMA

Description:

        PUMA, or PANDA Using MicroRNA Associations, is an extension of the gene regulatory network reconstruction algorithm PANDA.
        PUMA can reconstruct gene regulatory networks using both transcription factors and microRNAs as regulators of mRNA expression levels.

Inputs:

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

Outputs:

        (tag_for_output_file)_FinalNetwork.pairs: Bipartite gene-TF regulatory network where
        each line represents an edge in the graph (a TF-GENE pair).

Examples:

        To run PUMA with the assumption that all regulators can form complexes (estimate *responsibility* for all regulators, *eg* a gene regulatory prior with transcription factors only):
        ./PUMA -e ToyExpressionData.txt -m ToyMotifData.txt -o ToyOutput

        To tell PUMA to discriminate between regulators that can, and regulators that cannot cannot form complexes (for example a list of microRNAs in `miRlist.txt`), run:
        ./PUMA -e ToyExpressionData.txt -m ToyMotifData.txt -u ToyMiRList.txt -o ToyOutput

Publications:

        https://www.ncbi.nlm.nih.gov/pubmed/28506242

Authors:

        Marieke Kuijjer

