# appendheader - add DHTB to boot.img
![build appendheader](https://github.com/19atlas/appendheader/actions/workflows/c-cpp.yml/badge.svg) <br>
For every device that need "DHTB" string to boot <br>
written in c <br>


## minimal usage
`./appendheader -i [input file]` <br>
default output file name is `boot.img`

## advanced usage
` ./appendheader -i [input file] -o [output file name] --stay` <br>
for save input and output files (because why not)
