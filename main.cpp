# include <iostream>
# include <map>
# include <sys/socket.h>
# include <vector>
# include <arpa/inet.h>
# include <fstream>
# include "sqlite3.h"
signed int main() {
      sqlite3 *Db;
      std::cout << sqlite3_open("Users.db", &Db) << " - Opening database result\n";
      
      std::fstream File("Log.txt", std::ios::app);
      signed int MainSocket{socket(AF_INET, SOCK_STREAM, 0)};
      struct sockaddr_in SocketAddres;
      SocketAddres.sin_family = AF_INET;
      SocketAddres.sin_port = htons(32323);
      // inet_aton("0.0.0.0", &SocketAddres.sin_addr.s_addr);
      // printf("%s\n", INADDR_ANY);
      SocketAddres.sin_addr.s_addr = htonl(INADDR_ANY); // 0.0.0.0
      signed int result = bind(MainSocket, (const sockaddr *)(&SocketAddres), 
            sizeof(SocketAddres));
      listen(MainSocket, SOMAXCONN);
      signed int SlaveSocket = accept(MainSocket, 0, 0);
      std::cout << "Connection established\n";
      char Buffer[1024];
      std::string StringBuffer{};
      recv(SlaveSocket, Buffer, 1024, MSG_NOSIGNAL);
      printf("%s\n", Buffer);
      char ToSend[2]{"1"}; 
      send(SlaveSocket, ToSend, 16, MSG_NOSIGNAL);

     // std::cout << sqlite3_exec(Db, Buffer, NULL, NULL, NULL);
      
      
      File << Buffer;
      StringBuffer += Buffer;
      StringBuffer += "\n";
      File.close();      
      std::cout << "\nFin\n";
      
      shutdown(SlaveSocket, SHUT_RDWR);
      shutdown(MainSocket, SHUT_RDWR);

      
      
}
