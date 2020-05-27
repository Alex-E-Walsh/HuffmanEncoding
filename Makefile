all: huffman
headers=bitstream.h

huffman: bitstream.o main.o
	g++ -o huffman $^

%.o: %.cpp $(headers)
	g++ -std=c++11 -c -o $@ $<

clean:
	rm -f huffman ./*.o
