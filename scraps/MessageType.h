#ifndef TB_MESSAGETYPE
#define TB_MESSAGETYPE

namespace TorrentialBits {
    enum MessageType {
        choke = 0,
        unchoke = 1,
        interested = 2,
        disinterested = 3,
        have = 4,
        bitfield = 5,
        request = 6,
        piece = 7,
    };
}

#endif