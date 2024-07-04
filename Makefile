CC := gcc
OUTDIR := out
.PHONY: build clean

build:
	mkdir -pv $(OUTDIR)
	$(CC) appendheader.c -o $(OUTDIR)/appendheader

# caution!!! can be dangerous
clean:
	rm -rvf ./$(OUTDIR)