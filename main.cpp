#include "src/game.h"
#include "src/Menu.h"
#include "src/RoomList.h"
#include "src/GameRoom.h"
#include "src/Server.h"
#include "src/Client.h"
#include "src/MultiGame.h"

using namespace std;
using namespace sf;

void hhhhh(vector<sf::Text> PList){
    cout<<"PLIST:  ";
    for(auto const& value: PList) {
        cout<<value.getString().toAnsiString()<<"  ";
    }
    cout<<endl;
}

int main()
{
    int lop=0;
    RenderWindow window(VideoMode(320, 480), "Tetris game");
    window.setFramerateLimit(50);
    Menu menu(window);
    if (menu.selectedItemIndex == 1)
    {//-----Become Server--------------------------------
        GameRoom gameroom(window);//Lay ten nguoi choi
        gameroom.dienten(window);
        Server server(window, gameroom.PName);
        while (window.isOpen())//Trong phong Game
        {
            if (server.DoneWaiting == 1)
            {
                server.InitiatePoint();
                server.BroadcastOK();
                break;
            }
            else
            {
                server.Waiting(window);
                gameroom.vaophong(server.PList , window);
            }
        }
        MultiGame run;
        while (window.isOpen())//Vao Game
        {
            run.ChayGame(window);
            run.PrintVector(window, server.PList, server.PPoint);
            window.display();
            server.RecScore();//Recei Score fromCLient and send to them all
            if (run.changescore)
            {
              server.PPoint[0].setString(to_string(run.Score));
                server.BroadcastScore(to_string(run.Score), 0);
            }
            if (run.IsGameOver && run.ss){
              server.changeColors(0);
              server.BroadcastScore("death", 0);
              run.ss==false;
            }
            if (server.CheckGameOver()) {
              server.BroadcastScore("TheGameIsOver", 0);
              break;
            }
        }
        server.calculatePoint();
        while(window.isOpen()){
          run.AnoundWinner(window, server.PList, server.PPoint);
        }
    }
    else if (menu.selectedItemIndex == 2)//--Become Guest----------------------
    {
        //RoomList roomlist(window);
        GameRoom gameroom(window);//Lay ten nguoi choi
        gameroom.isGuest = true;
        gameroom.dienten(window);
        //gameroom.IPss.erase (0,1);

        Client guest(gameroom.IPss);//Connect to Sever
        //Client guest("192.168.1.26");//Connect to Sever

        guest.SendPoint(gameroom.PName);

        while (window.isOpen())
        {

          if (guest.ReceivedName != true)     guest.ReceiName(window);
          else guest.Waiting(window);

            gameroom.vaophong(guest.PList , window);
            if (guest.DoneWaiting == 1)
            {
                guest.InitiatePoint();
                break;
            }
        }
        MultiGame run;
        while (window.isOpen())//Vao Game
        {
            run.ChayGame(window);
            run.PrintVector(window, guest.PList, guest.PPoint);
            window.display();
            if (run.changescore == 1)
            {
                guest.SendPoint(to_string(run.Score));
            }
            if (run.IsGameOver){
              guest.SendPoint("death");
            }
            guest.ReceiveScore();
            if(guest.IsGameOver) break;
        }
        guest.calculatePoint();
        while(window.isOpen()){
          run.AnoundWinner(window, guest.PList, guest.PPoint);
        }
    }
    else//----------Single Player---------------
    {
        Game run;
        while (window.isOpen())
        {
            run.ChayGame(window);
        }
    }
    return 0;
}
