# TorrentialBits

## Completion Outline:

### 1.a - (5%)

Defines is responsible for reading and storing values from the Common.cfg file. _Fully Implemented_

**Files**: include/Defines.h src/Defines.cpp

### 1.b - (5%)

PeerInfo is responsible for reading PeerInfo.cfg (and dealing with the internal state in general). _Fully Implemented_

**Files**: include/PeerInfo.h src/PeerInfo.cpp

### 1.c - (5%)

TCP Connections are successfully made between peers and data is transmitted. The primary agents are Client and Server. _Fully Implemented_

**Files**: include/Client.h include/Server.h src/Client.cpp src/Server.cpp

### 1.d - (5%)

Some pieces are exchanged (though the protocol is not fully implemented). Peer would terminate if all files were recieved. _Partially Implemented_

**Files**: include/Client.h include/Server.h src/Client.cpp src/Server.cpp

### 2.a - (5%)

Handshake message is properly sent and handled by the server and client. _Fully Implemented_

**Files**: include/Client.h include/Server.h src/Client.cpp src/Server.cpp

### 2.b - (5%)

Bitfield message is exchanged and used by server to modify local data. _Fully Implemented_

**Files**: include/Client.h include/Server.h include/PeerInfo.h src/Client.cpp src/Server.cpp src/PeerInfo.cpp

### 2.c - (5%)

Some logic, but not successfully sent. Properly handled when recieved. _Partially Implemented_

**Files**: include/ClientController.h include/ServerController.h src/ClientController.cpp src/ServerController.cpp

### 2.d - (5%)

Some choke messages are sent, but handling and logic is flawed. _Partially Implemented_

**Files**: include/ClientController.h include/ServerController.h src/ClientController.cpp src/ServerController.cpp

### 2.e - (5%)

_No Implementation_

### 3.a-d - (20%)

Attempted but incomplete and disfunctional. _Partially Implemented_

**Files**: include/ClientController.h src/ClientController.cpp

### 3.e - (5%)

Our model only has this message sent in response to a request, and the server successfully sends these messages. _Fully Implemented_

**Files**: include/ServerController.h src/ServerController.cpp

### 3.f - (5%)

Have messages are recieved by the server and update bitfield inside of PeerInfo. _Fully Implemented_

**Files**: include/ServerController.h include/PeerInfo.h src/ServerController.cpp src/PeerInfo.cpp

### 4-5 - (20%)

_No Implementation_