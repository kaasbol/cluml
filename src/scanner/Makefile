PGM=scanner

test: clean clumlscanner clumltest clean

clumlscanner:
	g++ *.cpp *.cc -o $(PGM) 

clumltest:
	./$(PGM) < CLUMLText.txt

clean:
	rm -rf *.o $(PGM)
