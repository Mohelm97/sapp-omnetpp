import inet.common.packet.chunk.Chunk;
import inet.linklayer.common.MacAddress;
enum PSAMessageType
{
    Subscription = 0;
    Publication = 1;
    Acking = 2;
}

class PSAMessage extends inet::FieldsChunk {
    chunkLength = inet::B(6);
    uint8_t hopCount = 0;
    uint32_t nonce;
    PSAMessageType type;
    bool needAcking;
    string topic;
    string sourceNodeName;
    inet::MacAddress pathHops[];
}
