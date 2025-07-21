# appendheader - add DHTB to boot.img
![build appendheader](https://github.com/19atlas/appendheader/actions/workflows/c-cpp.yml/badge.svg) <br>
For every device that need "DHTB" string to boot <br>
written in c <br>
Tried and worked for gtexswifi ✅️

## minimal usage
`./appendheader -i [input file]` <br>
default output file name is `boot.img`

## add SEANDROIDENFORCE
`./appendheader -s [input file]` <br>
and you don't see red text

## advanced usage
` ./appendheader -i [input file] -o [output file name]` <br>
for save input and output files (because why not)

## LICENSE
licenced under GPL v3 licence <br>

![GPLV3](https://www.gnu.org/graphics/gplv3-127x51.png "gplv3")