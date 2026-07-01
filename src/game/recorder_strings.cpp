#include "string_base.h"

#define EOF (-1)

struct _iobuf;
typedef _iobuf FILE;
typedef unsigned short wchar_t;
extern "C" __declspec(dllimport) int __cdecl fgetc(FILE *stream);
extern "C" __declspec(dllimport) unsigned int __cdecl fread(void *buffer, unsigned int size, unsigned int count, FILE *stream);
extern "C" __declspec(dllimport) int __cdecl fclose(FILE *stream);
extern "C" __declspec(dllimport) FILE *__cdecl fopen(const char *filename, const char *mode);
extern "C" __declspec(dllimport) int __cdecl fgetpos(FILE *stream, int *pos);
extern "C" __declspec(dllimport) int __cdecl strncmp(const char *str1, const char *str2, unsigned int count);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *str);

class AsciiString {
public:
    AsciiString() { base()->StringBase<char>::StringBase(); }
    AsciiString(const AsciiString &that) { base()->StringBase<char>::StringBase(*that.base()); }
    AsciiString(const char *str) { base()->StringBase<char>::StringBase(str); }
    ~AsciiString() { base()->releaseBuffer(); }
    AsciiString &operator=(const AsciiString &that) { base()->set(*that.base()); return *this; }
    void clear() { base()->releaseBuffer(); }
    const char *str() const { return m_data != 0 ? &m_data->data[0] : ""; }
    void concat(const char *str)
    {
        const char *start = str;
        int len = 0;
        if (start != 0) {
            const char *end = str + 1;
            while (*str++) {
            }
            len = str - end;
        }
        base()->concat(start, len);
    }

private:
    StringBase<char> *base() { return (StringBase<char> *)this; }
    const StringBase<char> *base() const { return (const StringBase<char> *)this; }

private:
    StringBase<char>::Header *m_data;
};

class UnicodeString {
public:
    UnicodeString() { base()->StringBase<wchar_t>::StringBase(); }
    UnicodeString(const UnicodeString &that) { base()->StringBase<wchar_t>::StringBase(*that.base()); }
    UnicodeString(const wchar_t *str) { base()->StringBase<wchar_t>::StringBase(str); }
    ~UnicodeString() { base()->releaseBuffer(); }
    UnicodeString &operator=(const UnicodeString &that) { base()->set(*that.base()); return *this; }

private:
    StringBase<wchar_t> *base() { return (StringBase<wchar_t> *)this; }
    const StringBase<wchar_t> *base() const { return (const StringBase<wchar_t> *)this; }

private:
    StringBase<wchar_t>::Header *m_data;
};

UnicodeString readUnicodeString(FILE *file);

struct SystemTime {
    unsigned short year;
    unsigned short month;
    unsigned short dayOfWeek;
    unsigned short day;
    unsigned short hour;
    unsigned short minute;
    unsigned short second;
    unsigned short milliseconds;
};

class MessageStream {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void appendMessage(int type);
};

extern MessageStream *TheMessageStream;

struct Coord3D {
    float x;
    float y;
    float z;
};

struct ICoord2D {
    int x;
    int y;
};

struct IRegion2D {
    ICoord2D lo;
    ICoord2D hi;
};

enum GameMessageArgumentDataType {
    ARGUMENTDATATYPE_INTEGER,
    ARGUMENTDATATYPE_REAL,
    ARGUMENTDATATYPE_BOOLEAN,
    ARGUMENTDATATYPE_OBJECTID,
    ARGUMENTDATATYPE_DRAWABLEID,
    ARGUMENTDATATYPE_TEAMID,
    ARGUMENTDATATYPE_SQUADID,
    ARGUMENTDATATYPE_LOCATION,
    ARGUMENTDATATYPE_PIXEL,
    ARGUMENTDATATYPE_PIXELREGION,
    ARGUMENTDATATYPE_TIMESTAMP,
    ARGUMENTDATATYPE_WIDECHAR,
    ARGUMENTDATATYPE_UNKNOWN
};

class GameMessage {
public:
    enum Type {
        MSG_CLEAR_GAME_DATA = 0x1d,
        MSG_BEGIN_NETWORK_MESSAGES = 0x3e8
    };

    GameMessage(Type type);
    virtual ~GameMessage();

    void appendIntegerArgument(int arg);
    void appendRealArgument(float arg);
    void appendBooleanArgument(bool arg);
    void appendObjectIDArgument(unsigned int arg);
    void appendDrawableIDArgument(unsigned int arg);
    void appendTeamIDArgument(unsigned int arg);
    void appendLocationArgument(const Coord3D &arg);
    void appendPixelArgument(const ICoord2D &arg);
    void appendPixelRegionArgument(const IRegion2D &arg);
    void appendTimestampArgument(unsigned int arg);
    void appendWideCharArgument(const wchar_t &arg);
    void friend_setPlayerIndex(int i) { m_playerIndex = i; }

private:
    GameMessage *m_next;
    GameMessage *m_prev;
    void *m_list;
    Type m_type;
    int m_playerIndex;
    int m_frame;
    int m_argCount;
    void *m_argList;
};

class CommandList {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void appendMessage(GameMessage *msg);
};

extern CommandList *TheCommandList;

enum SlotState {
    SLOT_OPEN,
    SLOT_CLOSED,
    SLOT_EASY_AI,
    SLOT_MED_AI,
    SLOT_BRUTAL_AI,
    SLOT_PLAYER
};

class GameSlot {
public:
    virtual void reset();
    SlotState getState() const { return m_state; }
    unsigned int getIP() const { return m_IP; }
    unsigned int getPort() const { return m_port; }
    bool isHuman() const { return m_state == SLOT_PLAYER; }

private:
    SlotState m_state;
    bool m_isAccepted;
    bool m_hasMap;
    bool m_isMuted;
    int m_color;
    int m_startPos;
    int m_playerTemplate;
    int m_teamNumber;
    int m_origColor;
    int m_origStartPos;
    int m_origPlayerTemplate;
    int m_origTeamNumber;
    UnicodeString m_name;
    unsigned int m_IP;
    unsigned int m_port;
};

class GameInfo {
public:
    virtual void v0();
    virtual void v1();
    virtual void reset();
    virtual void startGame(int gameID);

    void enterGame();
    void endGame();
    GameSlot *getSlot(int slotNum);
    const GameSlot *getConstSlot(int slotNum) const;

private:
    char m_padding4[0x34 - 0x04];
};

bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options, bool unknown);

class GameMessageParserArgumentType {
public:
    virtual ~GameMessageParserArgumentType();
    GameMessageParserArgumentType *getNext() { return m_next; }
    GameMessageArgumentDataType getType() { return m_type; }
    int getArgCount() { return m_argCount; }

private:
    GameMessageParserArgumentType *m_next;
    GameMessageArgumentDataType m_type;
    int m_argCount;
};

class GameMessageParser {
public:
    GameMessageParser();
    virtual ~GameMessageParser();

    GameMessageParserArgumentType *getFirstArgumentType() { return m_first; }
    void addArgType(GameMessageArgumentDataType type, int argCount);

private:
    GameMessageParserArgumentType *m_first;
    GameMessageParserArgumentType *m_last;
    int m_argTypeCount;
};

class RecorderClass {
public:
    struct ReplayHeader {
        int startTime;
        int endTime;
        unsigned int frameDuration;
        unsigned int field0c;
        unsigned int field10;
        bool desyncGame;
        bool playerDiscons[8];
        char padding1d[3];
        AsciiString gameOptions;
        int localPlayerIndex;
        AsciiString filename;
        bool forPlayback;
        char padding2d[3];
        UnicodeString replayName;
        SystemTime timeVal;
        UnicodeString versionString;
        UnicodeString versionTimeString;
        unsigned int versionNumber;
        unsigned int exeCRC;
        unsigned int iniCRC;
        bool quitEarly;
        char padding59[3];
        unsigned int field5c;
    };

    static AsciiString getReplayDir();
    bool readReplayHeader(ReplayHeader &header);

protected:
    AsciiString readAsciiString();
    UnicodeString readUnicodeString();
    void readNextFrame();
    void appendNextCommand();
    void readArgument(GameMessageArgumentDataType type, GameMessage *msg);

private:
    int m_padding0;
    int m_padding4;
    int m_padding8;
    FILE *m_file;
    AsciiString m_fileName;
    char m_padding14[0x20 - 0x14];
    GameInfo m_gameInfo;
    unsigned int m_gameInfoLocalIP;
    unsigned int m_gameInfoLocalPort;
    char m_gameInfoPadding5c[0x298 - 0x5c];
    unsigned int m_replayHeaderField0c;
    unsigned int m_replayHeaderField10;
    int m_humanPlayerCount;
    int m_localPlayerIndex;
    bool m_doingAnalysis;
    char m_padding2a9[0x2b0 - 0x2a9];
    int m_nextFrame;
};

AsciiString RecorderClass::readAsciiString()
{
    char str[1024] = "";
    int index = 0;

    int c = fgetc(m_file);
    if (c == EOF) {
        str[index] = 0;
    }
    str[index] = c;

    while (index < 1024 && str[index] != 0) {
        ++index;
        int c = fgetc(m_file);
        if (c == EOF) {
            str[index] = 0;
            break;
        }
        str[index] = c;
    }
    str[1023] = '\0';

    AsciiString retval(str);
    return retval;
}

UnicodeString RecorderClass::readUnicodeString()
{
    return ::readUnicodeString(m_file);
}

void RecorderClass::readNextFrame()
{
    int retcode = fread(&m_nextFrame, sizeof(m_nextFrame), 1, m_file);
    if (retcode != 1) {
        m_nextFrame = -1;
        if (m_file != 0) {
            fclose(m_file);
            m_file = 0;
        }
        m_fileName.clear();
        if (!m_doingAnalysis) {
            TheMessageStream->appendMessage(0x1d);
        }
    }
}

void RecorderClass::readArgument(GameMessageArgumentDataType type, GameMessage *msg)
{
    if (type == ARGUMENTDATATYPE_INTEGER) {
        int theint;
        fread(&theint, sizeof(theint), 1, m_file);
        msg->appendIntegerArgument(theint);
    } else if (type == ARGUMENTDATATYPE_REAL) {
        float thereal;
        fread(&thereal, sizeof(thereal), 1, m_file);
        msg->appendRealArgument(thereal);
    } else if (type == ARGUMENTDATATYPE_BOOLEAN) {
        bool thebool;
        fread(&thebool, sizeof(thebool), 1, m_file);
        msg->appendBooleanArgument(thebool);
    } else if (type == ARGUMENTDATATYPE_OBJECTID) {
        unsigned int theid;
        fread(&theid, sizeof(theid), 1, m_file);
        msg->appendObjectIDArgument(theid);
    } else if (type == ARGUMENTDATATYPE_DRAWABLEID) {
        unsigned int theid;
        fread(&theid, sizeof(theid), 1, m_file);
        msg->appendDrawableIDArgument(theid);
    } else if (type == ARGUMENTDATATYPE_TEAMID) {
        unsigned int theid;
        fread(&theid, sizeof(theid), 1, m_file);
        msg->appendTeamIDArgument(theid);
    } else if (type == ARGUMENTDATATYPE_LOCATION) {
        Coord3D loc;
        fread(&loc, sizeof(loc), 1, m_file);
        msg->appendLocationArgument(loc);
    } else if (type == ARGUMENTDATATYPE_PIXEL) {
        ICoord2D pixel;
        fread(&pixel, sizeof(pixel), 1, m_file);
        msg->appendPixelArgument(pixel);
    } else if (type == ARGUMENTDATATYPE_PIXELREGION) {
        IRegion2D reg;
        fread(&reg, sizeof(reg), 1, m_file);
        msg->appendPixelRegionArgument(reg);
    } else if (type == ARGUMENTDATATYPE_TIMESTAMP) {
        unsigned int stamp;
        fread(&stamp, sizeof(stamp), 1, m_file);
        msg->appendTimestampArgument(stamp);
    } else if (type == ARGUMENTDATATYPE_WIDECHAR) {
        wchar_t theid;
        fread(&theid, sizeof(theid), 1, m_file);
        msg->appendWideCharArgument(theid);
    }
}

void RecorderClass::appendNextCommand()
{
    GameMessage::Type type;
    int retcode = fread(&type, sizeof(type), 1, m_file);
    if (retcode != 1) {
        return;
    }

    GameMessage *msg = new GameMessage(type);
    if (type != GameMessage::MSG_BEGIN_NETWORK_MESSAGES && type != GameMessage::MSG_CLEAR_GAME_DATA) {
        if (!m_doingAnalysis) {
            TheCommandList->appendMessage(msg);
        }
    }

    int playerIndex = -1;
    fread(&playerIndex, sizeof(playerIndex), 1, m_file);
    msg->friend_setPlayerIndex(playerIndex);

    unsigned char numTypes = 0;
    int totalArgs = 0;
    fread(&numTypes, sizeof(numTypes), 1, m_file);

    GameMessageParser *parser = new GameMessageParser;
    for (unsigned char i = 0; i < numTypes; ++i) {
        unsigned char type = ARGUMENTDATATYPE_UNKNOWN;
        fread(&type, sizeof(type), 1, m_file);
        unsigned char numArgs = 0;
        fread(&numArgs, sizeof(numArgs), 1, m_file);
        parser->addArgType((GameMessageArgumentDataType)type, numArgs);
        totalArgs += numArgs;
    }

    GameMessageParserArgumentType *parserArgType = parser->getFirstArgumentType();
    GameMessageArgumentDataType lasttype = ARGUMENTDATATYPE_UNKNOWN;
    int argsLeftForType = 0;
    if (parserArgType != 0) {
        lasttype = parserArgType->getType();
        argsLeftForType = parserArgType->getArgCount();
    }

    for (int j = 0; j < totalArgs; ++j) {
        readArgument(lasttype, msg);

        --argsLeftForType;
        if (argsLeftForType == 0) {
            if (parserArgType == 0) {
                return;
            }

            parserArgType = parserArgType->getNext();
            if (parserArgType != 0) {
                argsLeftForType = parserArgType->getArgCount();
                lasttype = parserArgType->getType();
            }
        }
    }

    if (type == GameMessage::MSG_CLEAR_GAME_DATA || type == GameMessage::MSG_BEGIN_NETWORK_MESSAGES) {
        delete msg;
        msg = 0;
    }

    if (m_doingAnalysis) {
        delete msg;
        msg = 0;
    }

    delete parser;
}

bool RecorderClass::readReplayHeader(ReplayHeader &header)
{
    AsciiString filepath = getReplayDir();
    filepath.concat(header.filename.str());
    m_file = fopen(filepath.str(), "rb");
    if (m_file == 0) {
        return false;
    }

    char magic[9];
    fread(&magic, sizeof(char), 8, m_file);
    magic[8] = 0;
    if (strncmp(magic, "BFMEREPL", 8)) {
        fclose(m_file);
        m_file = 0;
        return false;
    }

    fread(&header.startTime, sizeof(header.startTime), 1, m_file);
    fread(&header.endTime, sizeof(header.endTime), 1, m_file);
    fread(&header.frameDuration, sizeof(header.frameDuration), 1, m_file);
    fread(&header.field0c, sizeof(header.field0c), 1, m_file);
    m_replayHeaderField0c = header.field0c;
    fread(&header.field10, sizeof(header.field10), 1, m_file);
    m_replayHeaderField10 = header.field10;
    fread(&header.desyncGame, sizeof(header.desyncGame), 1, m_file);
    for (int i = 0; i < 8; ++i) {
        fread(&header.playerDiscons[i], sizeof(header.playerDiscons[i]), 1, m_file);
    }

    header.replayName = readUnicodeString();
    fread(&header.timeVal, sizeof(header.timeVal), 1, m_file);
    header.versionString = readUnicodeString();
    header.versionTimeString = readUnicodeString();
    fread(&header.versionNumber, sizeof(header.versionNumber), 1, m_file);
    fread(&header.exeCRC, sizeof(header.exeCRC), 1, m_file);
    fread(&header.iniCRC, sizeof(header.iniCRC), 1, m_file);
    fread(&header.quitEarly, sizeof(header.quitEarly), 1, m_file);
    fread(&header.field5c, sizeof(header.field5c), 1, m_file);

    int commandStart;
    fgetpos(m_file, &commandStart);

    header.gameOptions = readAsciiString();
    m_gameInfo.reset();
    m_gameInfo.enterGame();
    if (!ParseAsciiStringToGameInfo(&m_gameInfo, header.gameOptions, true)) {
        fclose(m_file);
        m_file = 0;
        return false;
    }
    m_gameInfo.startGame(0);

    AsciiString playerIndex = readAsciiString();
    header.localPlayerIndex = atoi(playerIndex.str());
    if (header.localPlayerIndex < -1 || header.localPlayerIndex >= 8) {
        m_gameInfo.endGame();
        m_gameInfo.reset();
        fclose(m_file);
        m_file = 0;
        return false;
    }
    if (header.localPlayerIndex >= 0) {
        GameSlot *slot = m_gameInfo.getSlot(header.localPlayerIndex);
        m_gameInfoLocalIP = slot->getIP();
        m_gameInfoLocalPort = slot->getPort();
    }

    if (!header.forPlayback) {
        m_gameInfo.endGame();
        m_gameInfo.reset();
        fclose(m_file);
        m_file = 0;
    }

    m_humanPlayerCount = 0;
    for (int j = 0; j < 8; ++j) {
        const GameSlot *slot = m_gameInfo.getConstSlot(j);
        if (slot->isHuman()) {
            ++m_humanPlayerCount;
        }
    }
    m_localPlayerIndex = header.localPlayerIndex;
    return true;
}
