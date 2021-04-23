# Initialisation
 1) Initialise environment: `bash --rcfile environment`.

 2) Prepare makefile and clang compilation dictionary: `./configure`

 3) Run compilation: `mk`



# Standard analysis
 1) Prepare analysis makefile: `./configure.analysis`. `-skip-long` option can be passed to skip the very long steps where changes are rare (pile up from ZeroBias).

 2) Run the analysis: `make -f makefile.analysis -j8`

 3) Estimate of systematics
    * `cd studies/systematics/`
    * `./run_all`



# Automated test
 * go to the base directory (where `run` file is)
 * execute `test/run_test`
