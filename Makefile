CMP = g++

app: String.o Config.o Connection.o Host.o Main.o
	$(CMP) -o ./Bin/t String.o Config.o Connection.o Host.o Main.o

end:
	rm *.o

String.o:
	$(CMP) -c ./DataStructs/String/String.cpp

Config.o:
	$(CMP) -c ./Config/Config.cpp

Connection.o:
	$(CMP) -c ./Network/Host/Connection.cpp

Host.o:
	$(CMP) -c ./Network/Host/Host.cpp

Main.o:
	$(CMP) -c ./Main/Main.cpp
