#ai.exe : test_bigint.cpp bigint.o func.o
#	g++ test_bigint.cpp bigint.o func.o

ar.exe : test_bigreal.cpp bigint.o bigreal.o func.o utility.o
	g++ test_bigreal.cpp bigint.o bigreal.o func.o utility.o

bigint.o : bigint.cpp bigint.h
	g++ -c bigint.cpp

bigreal.o : bigreal.cpp bigreal.h
	g++ -c bigreal.cpp

func.o : func.cpp func.h
	g++ -c func.cpp

utility.o : utility.cpp utility.h
	g++ -c utility.cpp
