```
rm data/all-good/Totem1/*/*.{root,log}    # remove old files

./run distributions.cc data/all-good/Totem1/*/ -O "-bootstrap 1" -wait    # run distributions in "bootstrap" mode

./run resolution_fit.cc data/all-good/Totem1/*/ -wait   # run resolutions

./run eff3outof4.cc data/all-good/Totem1/*/ -wait    # run efficiencies
./run eff3outof4_fit.cc data/all-good/Totem1/*/ -wait

./run distributions.cc data/all-good/Totem1/*/ -wait    # re-run distributions
```
