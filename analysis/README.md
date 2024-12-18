# Analysis code for MC output
- `GetL1Plot.C`: returns the pt, eta, phi plots for the leading 10 jets, 4 muons and 4 electrons
- 

Usage: 
```
root 'GetL1Plot.C("path/to/.root","plots_dir/")'

# example
root 'GetL1Plot.C("../data/1cms-pu60-sm-z2l-cut/Events/run_01/tag_1_delphes_events.root","plots/cms-pu60-sm-z2l/")'
```

```
root 'analysis/GetL1Info.C("path/to/root", "path/to/h5output", is_append_boolean)'

# example
root 'GetL1Info.C("../data/2atlas-pu-sm-cocktail/Events/run_01/tag_1_delphes_events.root", "h5_output/sm_mix.h5", 1)'
```