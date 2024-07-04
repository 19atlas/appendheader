# appendheader - add DHTB to boot.img
For every device that needs the "DHTB" string to boot <br>
written in c

## minimal usage
`./appendheader -i [input file]` <br>
default output file name is `boot.img`

## advanced usage
` ./appendheader -i [input file] -o [output file name] --stay` <br>
for save input and output files (because why not)