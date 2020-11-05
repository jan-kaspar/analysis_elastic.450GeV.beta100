# Initialisation
 1) Initialise environment: `bash --rcfile environment`.

 2) Prepare compilation dictionary: `./build_compile_commands_json`



# Standard analysis flow

 1) Prepare skimmed/distilled ntuples:
 `./run distill.cc data/fill*/Totem1/`

 2) Run distributions with no auxiliary input (bootstrap):
 `./run distributions.cc data/fill*/Totem1/ -O "-bootstrap 1"`

 3) Fit angular resolution time dependence:
 `./run resolution_fit.cc data/fill*/Totem1/`

 4) Re-run distributions (this time with the auxiliary input):
 `./run distributions.cc data/fill*/Totem1/`



# Automated test
 * go to the base directory (where `run` file is)
 * execute `test/run_test`
