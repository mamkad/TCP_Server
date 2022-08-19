CMP = g++

app: String.o Config.o Connection.o Host.o Main.o
	$(CMP) -o ./Bin/t ./Bin/String.o ./Bin/Config.o ./Bin/Connection.o ./Bin/Host.o ./Bin/Main.o -pthread

clear:
	rm *.o

String.o:
	$(CMP) -c ./DataStructs/String/String.cpp -o ./Bin/String.o

Config.o:
	$(CMP) -c ./Config/Config.cpp -o ./Bin/Config.o

Connection.o:
	$(CMP) -c ./Network/Host/Connection.cpp -o ./Bin/Connection.o

Host.o:
	$(CMP) -c ./Network/Host/Host.cpp -o ./Bin/Host.o

Main.o:
	$(CMP) -c ./Main/Main.cpp -o ./Bin/Main.o 
