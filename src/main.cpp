#include <iostream>
#include <memory>
#include <Peer.h>

using namespace std;
using namespace TorrentialBits;

int main()
{
    auto peer = unique_ptr<IPeer>(new Peer("127.0.0.1", 8008));
    peer->Start();
    cout << "Compiled and Ran :)" << endl;
    return 0;
}