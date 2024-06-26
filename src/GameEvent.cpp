#include "GameEvent.h"

bool _LinkAGameEvents::handleMessage(_LinkAMessage &msg)
{
    return false;
}

void _LinkAGameEvents::sendMessaage(int messageType, _Recipient *sender, _Recipient *receiver, GameObject *extraInfo, float timestamp, _ReturnReceiptStatus returnReceiptStatus)
{
    _LinkAMessage msg;
    msg.messageType = messageType;
    msg.sender = sender;
    msg.receiver = receiver;
    msg.extraInfo = extraInfo;
    msg.timestamp = timestamp;
    msg.returnReceiptStatus = returnReceiptStatus;
    sendMessaage(msg);
}

void _LinkAGameEvents::sendMessaage(_LinkAMessage &message)
{
    if (message.receiver != NULL)
    {
        std::cout << "message send to target receiver" << std::endl;
        message.receiver->handleMessage(message);
    }
    else
    {
        std::vector<_Recipient *> ls = listeners[message.messageType];
        for (_Recipient *rPtr : ls)
        {
            rPtr->handleMessage(message);
        }
    }
    if (message.sender != NULL && message.returnReceiptStatus == _ReturnReceiptStatus::RETURN_RECEIPT_NEEDED)
    {
        message.receiver = message.sender;
        message.sender = this;
        message.returnReceiptStatus = _ReturnReceiptStatus::RETURN_RECEIPT_SENT;

        message.receiver->handleMessage(message);
    }
}

void _LinkAGameEvents::dispose()
{

    for (auto it = listeners.begin(); it != listeners.end(); it++)
    {
        std::vector<_Recipient *> ls = it->second;
        for (_Recipient *rPtr : ls)
        {
            delete rPtr;
        }
    }
    listeners.clear();
}

void _LinkAGameEvents::registListerner(int messageType, _Recipient *lsn)
{
    listeners[messageType].push_back(lsn);
}

void _LinkAGameEvents::removeListerner(_Recipient *lsn)
{
    for (auto it = listeners.begin(); it != listeners.end(); it++)
    {
        std::vector<_Recipient *> &list = it->second;
        for (auto itInner = list.begin(); itInner != list.end();)
        {
            if ((*itInner) == lsn)
            {
                itInner = list.erase(itInner);
            }
            else
            {
                itInner++;
            }
        }
    }
}