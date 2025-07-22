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

## for bash scripting
### [source](https://xdaforums.com/t/recovery-root-twrp-3-2-1-1-magisk-v14-samsung-galaxy-tab-a6-sm-t280-sm-t285.3475381/post-87438849)
```bash
# Patch image to include additional 512 Bytes Header found on SM-T280 devices
if [ "$(dd if=$BOOTIMAGE count=4 bs=1)" = "DHTB" ]; then 
  ui_print "- Found DHTB Header at 0x0000, expecting ANDR at 0x0200"
  if [ "$(dd if=$BOOTIMAGE count=4 bs=1 skip=512)" = "ANDR" ]; then
    ui_print "- Found ANDR Header at 0x0200, patching boot.img"
    dd if=$BOOTIMAGE of=/sutmp/prefix.img count=8 bs=1
    dd if=/dev/zero of=/sutmp/prefix-pad.img count=504 bs=1
    cat /sutmp/prefix.img /sutmp/prefix-pad.img /sutmp/boot.img > /sutmp/patched.img
    rm /sutmp/boot.img
    mv /sutmp/patched.img /sutmp/boot.img
  else
    ui_print "- ANDR Header NOT found at 0x0200, boot.img may not work!"
  fi
else
  ui_print "- DHTB Header at 0x0000 NOT found, skipping step"
fi
```

## LICENSE
licenced under GPL v3 licence <br>

![GPLV3](https://www.gnu.org/graphics/gplv3-127x51.png "gplv3")
