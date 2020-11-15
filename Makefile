build: subnetter

subnetter: subnetter.cpp
	g++ ./subnetter.cpp -o subnetter -Wall -O2

clean:
	rm -f subnetter

run: subnetter
	./subnetter < in.txt
