#include "Server.h"


Server::Server(sf::RenderWindow &window, std::string PName)
{
    // TcpSocket socket[5];
    srand((unsigned) time(0));
    PORT = 8000;

    font.loadFromFile("IMG/simplistic_regular.ttf");
    socket.push_back(make_unique<TcpSocket>());
    cout<<"listening"<<endl;
    listener.listen(PORT);
    listener.setBlocking(false);
    takeIn(PName);//Dua ten vao Plist
}
void Server::BroadcastList(int i)
{
    packet.clear();
    string mess;
    for (int j=0; j<=index; j++)
    {
        mess = PList[j].getString().toAnsiString();
        packet<<mess;
    }
    int j=0;
    for(auto const& value: socket) {
      if(j==i){
        value->send(packet);
        break;
      }
      j++;
    }
    packet.clear();
}
void Server::BroadcastOK()
{
    string mess = "OK";
    packet<<mess;
    for(auto const& value: socket) {
        value->send(packet);
    }
    packet.clear();
}
void Server::BroadcastNewPlayer(string newPlayer)
{
    int i=0;
    packet.clear();
    packet<<"new Player";
    packet<<newPlayer;
    for(auto const& value: socket) {
      if (i>=index - 1) break;
        value->send(packet);
        i++;
    }
    packet.clear();
}

void Server::Waiting(sf::RenderWindow &window)
{
    while (window.pollEvent(e))
    {
        if (e.type == Event::Closed)
        window.close();
        if (e.type == Event::KeyPressed && e.key.code==Keyboard::Enter){
          if(isReady == index){
            DoneWaiting = 1;
          }
        }
    }
    if (listener.accept(*socket[index]) == Socket::Done)
    {
        socket[index]->setBlocking(false);
        socket[index]->receive(packet);//Read in PName
        packet>>str;
        packet.clear();
        if (str != "")
        {
            cout<<"Player : "+str<<endl;
            socket.push_back(make_unique<TcpSocket>());
            index++;
            takeIn(str);
            BroadcastList(index-1);
            BroadcastNewPlayer(str);
        }
    }
    for (int j=0; j<index; j++)
    {
        status = socket[j]->receive(packet);
        if (status == Socket::Disconnected)
        {
            socket.erase (socket.begin()+j);
            PList.erase (PList.begin()+j+1);
            index--;
            BroadcastScore("Disconnected", j+1);
        }
        else if (status == Socket::Done){
          string buf;
          packet>>buf;
          if (buf == "ready") {// receive player ready
            isReady++;
              PList[j+1].setFillColor(sf::Color::Green);
              BroadcastScore("ready", j+1);
          }
        }
    }
}

void Server::takeIn(std::string mess)
{
    PList.push_back(sf::Text());
    PList[index].setFont(font);
    PList[index].setFillColor(sf::Color::Red);
    PList[index].setString(mess);
    PList[index].setCharacterSize(20);
    PList[index].setPosition(sf::Vector2f(20, 480 / (MAX_NUMBER_OF_PLAYERS + 1) * (index+1)));
}

void Server::RecScore()
{
    std::string buf;
    for (int j=0; j<=index; j++)
    {
        status = socket[j]->receive(packet);
        if (status == Socket::Done)
        {
            buf.clear();
            packet>>buf;
            if (buf == "death") {//Receive Death message
                PList[j+1].setFillColor(sf::Color::Yellow);
                PPoint[j+1].setFillColor(sf::Color::Yellow);
                PGameOver[j+1]=1;
            }
            else  PPoint[j+1].setString(buf);// receive Score
            BroadcastScore(buf, j+1);
        }
        else if (status == Socket::Disconnected)
        {
            socket.erase (socket.begin()+j);
            PList.erase (PList.begin()+j+1);
            PPoint.erase (PPoint.begin()+j+1);
            PGameOver.erase (PGameOver.begin()+j+1);
            index--;
        }
    }
    packet.clear();
}
void Server::BroadcastScore(string buf, int j)
{
  packet.clear();
    packet<<buf;
    packet<<to_string(j);
    for(auto const& value: socket) {
        value->send(packet);
    }
    packet.clear();
}
void Server::InitiatePoint()
{
    for (int i=0; i<PList.size(); i++)
    {
        PGameOver.push_back(0);
        PList[i].setPosition(sf::Vector2f(220, 480 / (MAX_NUMBER_OF_PLAYERS + 1) * (i+1)));
        PList[i].setFillColor(sf::Color::Red);
        PPoint.push_back(sf::Text());
        PPoint[i].setFont(font);
        PPoint[i].setFillColor(sf::Color::Red);
        PPoint[i].setString("0");
        PPoint[i].setCharacterSize(20);
        PPoint[i].setPosition(sf::Vector2f(250, 20+480 /(MAX_NUMBER_OF_PLAYERS + 1) * (i+1)));
    }
}
bool Server::CheckGameOver()
{
    for(auto const& value: PGameOver) {
        if(value==0) return 0;
    }
    return 1;
}
void Server::changeColors(int i)
{
    PList[i].setFillColor(sf::Color::Yellow);
    PPoint[i].setFillColor(sf::Color::Yellow);
    PGameOver[i]=1;
}

void swap(int *a, int*b){
	int *c = a;
	a = b;
	b = c;
}
void Server::calculatePoint(){
      std::vector<int> sss;
      int i= 0 ;
      for(auto const& value: PPoint) {
          sss.push_back(stoi(value.getString().toAnsiString()));
          thu_tu.push_back(i);
          i++;
      }
      for(int counterrrs=i-1; counterrrs>=0; counterrrs--){
    		for (int j = 0; j < counterrrs; j++) {
    			if (sss[j]<sss[j+1]){
    				swap(sss[j],sss[j+1]);
            swap(thu_tu[j],thu_tu[j+1]);
    			}
    		}
    	}
      i=0;
      for(auto const& value: thu_tu)
      {
          PList[i].setPosition(sf::Vector2f(120, (480 / 7) * (value+1)));
          PPoint[i].setPosition(sf::Vector2f(140, 30+(480 /7) * (value+1)));
          i++;
      }
    }
