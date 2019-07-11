# build all executables
all: lyrebird_compose lyrebird_decompose

lyrebird_compose: lyrebird_compose.c
	gcc -g -Wall -lm -o lyrebird_compose lyrebird_compose.c

lyrebird_decompose: lyrebird_decompose.c
	gcc -g -Wall -lm -o lyrebird_decompose lyrebird_decompose.c

clean:
	$(RM) lyrebird_compose lyrebird_decompose