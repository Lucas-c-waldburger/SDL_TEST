
#ifndef Flags_hpp
#define Flags_hpp

enum FlAG_VALUES
{
    quit = 1 << 0,
    renderTypedText = 1 << 1,
    startScroll = 1 << 2,
    scrollingTextFull = 1 << 3,
    transferToScrolling = 1 << 4,
};

struct GameFlags
{
    uint8_t flagValue = 0;

    bool isSet(uint8_t flag) { return (flagValue & flag); }
    void setFlag(uint8_t flag) { flagValue |= flag; }
    void unsetFlag(uint8_t flag) { flagValue &= (~flag); }
};

#endif /* Flags_hpp */
