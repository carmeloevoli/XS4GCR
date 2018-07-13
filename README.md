# D2XSECS

D2XSECS implements the cross-sections for galactic cosmic ray propagation models as described in arXiv:1711.09616.

### Installation

- D2XSECS requires GSL library and C, C++, Fortran compilers. 

- We provide some examples of using, each of them can be installed this way:
```
mkdir build ; cd build 
cmake .. 
make xsec_example1 
```

### Documentation

- Code documentation is in progress. 

- D2XSECS documentation requires Doxygen installed.

- To create:
```
cd build
make doc
```

### Data

- Data files necessary for D2XSECS are downloaded from a Dropbox repository during installation.

- Data size is approximately 10 Mb
