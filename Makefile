
pcidump2json:
	gcc pcidump2json.c -o pcidump2json.elf -lpci

clean:
	rm *.o *.elf
