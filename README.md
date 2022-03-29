# Basic usage

```
# initialisation
bash --rcfile environment # intialise environment
./configure # prepare makefile and clang compilation dictionary
mk # run compilation

# data analysis (all steps, all good datasets)
./configure.analysis # prepare analysis makefile
make -f makefile.analysis -j # run the analysis (this make take few hours)

# estimate of systematics
cd studies/systematics/
./run_all

```

# Structure of the repository

The philosophy is that there are
  * _analysis steps_ (represented by .cc files in the main directory)
  * applied to _datasets_ (represented by directories with config files, e.g. `data/fill7280/Totem1/` with `config.py`).

Some steps are applied to data from a single diagonal, some to both diagonals together (combined diagonals). Exceptionally, background estimation also works with anti-diagonals.

A step is applied to a dataset with the `./run` script. The syntax is as follows:
```
./run <option> <src file> <option> <dir1> <dir2> ...
```
This will apply the step represented by `<src file>` to dataset `<dir1>`, `<dir2>`, ... with the specified options. The most important option is `-d` which allows to select for which diagonals the step shall be exectued. The default is `45b_56t`, `45t_56b` and `combined`.


# Datasets

The main collection of datasets is in `data/fill*`. They are split by the fill. Each directory contains subdirectories `Totem1` and `ZeroBias` - they refer to the trigger stream. The former is used for most of the analysis, the latter for some efficiency corrections.

The config files are built in hierarchical manner. Some settings are applicable to all fills, some to just one fill, some to a single trigger. The basic config (common to all datasets) is in `config_base.py` in the top directory.

The input files (from CMSSW reco) are listed in `input_files.py` file in the dataset directory. Some directories don't include this file, they can reuse the "distilled" ntuples from other datasets.

# Config files

The config files use the same syntax as the CMSSW files.

Each file should define several objects. For example `cfg_45b_56b` will contain the configuration for the diagonal 45 bottom - 56 top.

Each configuration object has several entries:
  * `timestamp0`: timestamps used in the analysis are UNIX timestamp - timestamp0
  * `timestamp_min` and `timestamp_max`: timestamp interval
  * `env`: configuration of the "Environment" class, i.e. conditions/non-event data such as optics
  * `anal`: analysis settings (some details below)

Some of the analysis parameters:
  * `excl_timeIntervals`: time intervals excluded from the analysis
  * `excl_bunches`, `excl_runs`, `excl_lsIntervals`: excluded bunch number, runs and LS intervals
  * `alignment_sources`: sources of alignment corrections
  * `post_reco_adjustments`: per arm post-reco adjustments
  * `t_min`, `t_max`: range for |t| binning (where we expect to have acceptance)
  * `t_min_full`, `t_max_full`: range for |t| histograms, with some extra space at the edges for unfolding correction etc.
  * `t_min_crop`, `t_max_crop`: the final dsigma/dt will be cropped to this interval (we don't trust data outside)
  * `n_si`: selection cuts are applied at this level.
  * `cut*_a`, `cut*_c`, `cut*_si`: cut parameters - slope, offset and tolerance
  * `fc_L`, `fc_R`, `fc_G`: fiducial cuts (in theta*_y vs theta*_x space) for the left arm, the right arm and global
  * `vtx_*_min`, `vtx_*_max`: reco vertex restrictions
  * `si_th_*_*`: resultion paramters for reconstructed angles
  * `use_resolution_fits`: if empirically determined resolution shall be used. When false the `si_th_*` parameters are used instead.
  * `use_3outof4_efficiency_fits`: whether the empirically determined 3/4 efficiencies shall be used. When false, `inefficiency_3outof4` will be used.
  * `use_pileup_efficiency_fits`: whether the empirically determined pile-up correction shall be used. When false, `inefficiency_pile_up` will be used.
  * `use_background_fits`: whether to use the empirically determined background correction shall be used. When false, `bckg_corr` will be used.
  * `inefficiency_trigger`: trigger inefficiency
  * `inefficiency_DAQ`: DAQ inefficiency
  * `L_int`: effective integrated luminosity
  * `norm_corr`: additional normalisation correction
  * `binnings`: list of |t| binnings to be used in the analysis

# Common code

The often reused code is in the `classes` directory.
  * `AcceptanceCalculator.hh`: code for calculating the acceptance corrections.
  * `Analysis.hh`: structure that holds the analysis settings
    * `EvaluateCuts`: checks if the event fullfills the elastic tagging cuts
    * `SkipEvent`: checks if the event should be skipped (following the configured criteria)
  * `command_line_tools.hh`: tools to parse the command line arguments
  * `common_algorithms.hh`
    * `DoGlobalReconstruction`: only double-arm kinematics reconstruction
    * `DoReconstruction`: full kinematics reconstruction
    * `BuildBinning`: builds a binning accroding to a set of rules
  * `common_alignment.hh`: tools for handling alignment corrections
  * `common_event.hh`: elementry hit and event data
  * `common_init.hh`: tools to parse the config python files
  * `Config.hh`: structure to hold the basic dataset parameters (timestamps, ...)
  * `Environment.hh`: structure to hold conditions data (beam momentum, optics, ...)
  * `FiducialCut.hh`: fiducial cut in theta*_y vs theta*_x plane
  * `Kinematics.hh`: structure to hold the elastic-event kinematics
  * `numerical_integration.hh`: tools for numerical integration
  * `Stat.hh`: basic statistical tools


# Analysis steps

The source code representing the analysis steps is in the top directory.
  * `distill.cc`: reduces the original CMSSW files to "distilled" ntuples containing only data useful for the analysis.
  * `distributions.cc`: applies elastic tagging, make LOTS plots ... the main part of the analysis.
  * `alignment.cc`: runs the alignment on top of the output from distributions.cc.
  * `alignment_fit.cc`: fits the results from alignment.cc.
  * `alignment_final.cc`: an independent alignment check - looks for the symmetry point of the theta*_y vs theta*_x distribution.
  * `distributions_anti.cc`: similar to distributions.cc, just for anti-diagonals. Inverts y sign for one of the diagonals to create a fake elastic signal.
  * `background_fit.cc`: on top of the output from distributions.cc and distributions_anti.cc, estimates the background fraction.
  * `eff3outof4.cc`: 3/4 efficiency calculation, on top of distributions.cc.
  * `eff3outof4_details.cc`: 3/4 efficiency calculation with many details. Runs on the original CMSSW input, takes time.
  * `eff3outof4_fit.cc`: runs fits on the results of eff3outof4.cc.
  * `pileup.cc`: estimates the pile-up inefficiency. Runs on the original CMSSW input, zero bias triggr, takes very long.
  * `process_timber.cc`: a tool to process the input from Timber
  * `resolution_fit.cc`: estimates the time dependence of resolution parameters, on top of distributions.cc.
  * `unfolding_cf_mc.cc`: estimation of the unsmearing correction, MC method, takes long for a decent statistics.
  * `unfolding_cf_ni.cc`: estimation of the unsmearing correction, numerical integration method, fast.

There are dependencies among the steps. In order to respect them, best to use the `makefile.analysis`.

Since some of corrections are determine during the analysis, two iterations (at least) must be made. For the first iteration, it is handy to run the `distributions.cc` step with the `bootstrap` parameter, in order to take the initial corrections from constants in the config file.

# Results

Results from each analysis step are saved in a ROOT file (accompanied with a log) in the dataset directory (e.g. data/fill7280/Totem1/). The file name is composed of the step name and the diagonal (e.g. distill_45b_56t.root). The contents of the ROOT file are logically organised in directories.

For instance, the contents of the `distributions.cc` results comprise:
  * `metadata`: auxiliary plots, e.g. rate comparison
  * `hit distributions`: hit distributions, for different combinations before/after alignment, before/after elastic tagging
  * `alignment`: input to `alignment.cc`
  * `elastic cuts`: detailed plots for each of the elastic tagging cuts
  * `selected - hits`, `selected - angles` and `selected - vertex`: plots after elastic selection (and before acceptance correction), for hits, reco angles and reco vertex
  * `optics`: input for optics matching
  * `binning`: plots of bin width vs |t|
  * `time dependences`: time dependence graphs for many parameters of interest, e.g. resolution
  * `fiducial cuts`: fiducial contours
  * `acceptance correction`: plots related to acceptance correction (elastic tagging included), separately for each binning considered
  * `normalization`: t distributions after acceptance correction and normalisation, separately for each binning
  * `normalization+unfolding`: as in `normalization`, here the unfolding is included in addition

Note that some results may not be saved, depending on the `details` flag passed to `distributions.cc`.

Since each dataset and each diagonal is processed separately, we need a tool to merge all results together. This tools is in `data/merge.cc`, its output is (by default) saved to `data/merged.root`. The output has a form
```
<binning> / <dataset collection> / <diagonal collection> / <histogram>
```
The "dataset collection" can be a single dataset (e.g. a fill) or multiple datasets. For example, "merged" represents all datasets together. Similarly, "diagonal collection" can be a single diagonal or "combined", i.e. the two diagonals together. "histogram" can either be "h_dsdt", i.e. the differential cross-section, or "h_dNdt", histogram of number of events per bin.

# Systematics

# Plots


# TODO
 1) Prepare analysis makefile: `./configure.analysis`. `-skip-long` option can be passed to skip the very long steps where changes are rare (pile up from ZeroBias).




# Automated test
 * go to the base directory (where `run` file is)
 * execute `test/run_test`
