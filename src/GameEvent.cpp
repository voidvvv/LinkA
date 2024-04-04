#include "GameEvent.h"

bool _LinkAGameEvents::handleMessage(_LinkAMessage &msg)
{
    return false;
}

void _LinkAGameEvents::sendMessaage(int messageType, _Recipient *sender, _Recipient *receiver, GameObject *extraInfo, float timestamp,_ReturnReceiptStatus returnReceiptStatus)
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
    if (message.receiver != NULL){
        message.receiver->handleMessage(message);
    }else {
        std::vector<_Recipient *> ls = listeners[message.messageType];
        for (_Recipient * rPtr : ls){
            rPtr->handleMessage(message);
        }
    }
    if (message.sender != NULL &&  message.returnReceiptStatus == _ReturnReceiptStatus::RETURN_RECEIPT_NEEDED){
        message.receiver = message.sender;
        message.sender = this;
        message.returnReceiptStatus = _ReturnReceiptStatus::RETURN_RECEIPT_SENT;

        message.receiver->handleMessage(message);
    }
}

void _LinkAGameEvents::dispose()
{
    
    for (auto it = listeners.begin(); it != listeners.end(); it++){
        std::vector<_Recipient *> ls =  it->second;
        for (_Recipient * rPtr: ls){
            delete rPtr;
        }
    }
    listeners.clear();
}
