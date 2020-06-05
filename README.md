# XS4GCR

XS4GCR implements the cross-sections for galactic cosmic ray propagation models

References:
- arXiv:1904.10220 
- arXiv:1711.09616

### Installation

- XS4GCR requires GSL library and C, C++, Fortran compilers. 

- We provide some examples of using, each of them can be installed this way:
```
mkdir build ; cd build 
cmake .. 
make xsec_example1 
```

### Documentation

- Code documentation is in progress. 

- XS4GCR documentation requires Doxygen installed.

- To create:
```
cd build
make doc
```

### Data

- Data files necessary for XS4GCR are downloaded from a Dropbox repository during installation.

- Data size is approximately 10 Mb
