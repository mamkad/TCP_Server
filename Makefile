CMP = g++
STD = -std=c++17

App: String.o Log.o Config.o Socket.o Connection.o Main.o Full Clear
	
Clear:
	rm ./Bin/*.o

String.o:
	$(CMP) -c ./DataStructs/String/String.cpp -o ./Bin/String.o $(STD)

Log.o:
	$(CMP) -c ./Log/Log.cpp -o ./Bin/Log.o $(STD)

Config.o:
	$(CMP) -c ./Config/Config.cpp -o ./Bin/Config.o $(STD)

Socket.o:
	$(CMP) -c ./Network/Socket/Socket.cpp -o ./Bin/Socket.o $(STD)

Connection.o:
	$(CMP) -c ./Network/Connection/Connection.cpp -o ./Bin/Connection.o $(STD)

Host.o:
	$(CMP) -c ./Network/Host/Host.cpp -o ./Bin/Host.o $(STD)

Main.o:
	$(CMP) -c ./Main/Main.cpp -o ./Bin/Main.o $(STD) 

Full:
	$(CMP) -o ./Bin/t ./Bin/String.o ./Bin/Log.o ./Bin/Config.o ./Bin/Socket.o ./Bin/Connection.o  ./Bin/Main.o -pthread
