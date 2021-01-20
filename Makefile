
CXX = g++
LDLIBS=-lsfml-network  -lsfml-graphics  -lsfml-window  -lsfml-system
CPPFLAGS= ./src/

SRCS = game.cpp	Menu.cpp	RoomList.cpp  Server.cpp  Client.cpp  GameRoom.cpp MultiGame.cpp
OBJS = game.o Menu.o RoomList.o  Server.o Client.o  GameRoom.o	MultiGame.o

all	:	main	clean

main:	main.o	${OBJS}
	g++ -o main main.o ${OBJS} ${LDLIBS}
main.o:	main.cpp
	g++ -c main.cpp
game.o: ${CPPFLAGS}game.cpp
	${CXX} -c ${CPPFLAGS}game.cpp
Menu.o: ${CPPFLAGS}Menu.cpp
	${CXX} -c ${CPPFLAGS}Menu.cpp
RoomList.o: ${CPPFLAGS}RoomList.cpp
	${CXX} -c ${CPPFLAGS}RoomList.cpp
Server.o: ${CPPFLAGS}Server.cpp
	${CXX} -c ${CPPFLAGS}Server.cpp
Client.o: ${CPPFLAGS}Client.cpp
	${CXX} -c ${CPPFLAGS}Client.cpp
GameRoom.o: ${CPPFLAGS}GameRoom.cpp
	${CXX} -c ${CPPFLAGS}GameRoom.cpp
MultiGame.o: ${CPPFLAGS}MultiGame.cpp
	${CXX} -c ${CPPFLAGS}MultiGame.cpp
clean:
	rm -f *.o *~
