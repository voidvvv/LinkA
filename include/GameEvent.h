#ifndef __GAMEEVENT_H__
#define __GAMEEVENT_H__
#include <map>
#include <vector>
#include <memory>

#include "GameObject.h"

#define _CARD_SELECTED 1
#define _CARD_SUCCESS_MATCH 2


enum _ReturnReceiptStatus
{
    RETURN_RECEIPT_UNNEEDED,
    RETURN_RECEIPT_NEEDED,
    RETURN_RECEIPT_SENT,
};
class _LinkAMessage;
class _Recipient
{
public:
    virtual bool handleMessage(_LinkAMessage &msg) = 0;
};

class _LinkAMessage
{
public:
    _Recipient *sender;
    _Recipient *receiver;
    int messageType;
    float timestamp;
    _ReturnReceiptStatus returnReceiptStatus;
    GameObject* extraInfo;
};

class _LinkAGameEvents : public _Recipient
{
private:
    std::map<int, std::vector<_Recipient *>> listeners;

public:
    virtual bool handleMessage(_LinkAMessage &msg) override;
    void sendMessaage(int messageType, _Recipient *sender = nullptr,
                      _Recipient *receiver = nullptr,
                      GameObject *extraInfo = nullptr,
                      float timestamp = 0.f,
                      _ReturnReceiptStatus returnReceiptStatus = _ReturnReceiptStatus::RETURN_RECEIPT_UNNEEDED);
    void sendMessaage(_LinkAMessage &message);
    void dispose();
    void registListerner(int messageType, _Recipient *);
};

extern _LinkAGameEvents* events;

#endif // __GAMEEVENT_H__