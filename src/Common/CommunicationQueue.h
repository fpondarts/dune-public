#ifndef __COMMUNICATION_QUEUE_H__
#define __COMMUNICATION_QUEUE_H__

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <nlohmann/json.hpp>

class CommunicationQueue {
public:
    CommunicationQueue();
    void enqueue(nlohmann::json send_json);

    nlohmann::json dequeue();

    void putReceived(nlohmann::json send_json);
    nlohmann::json getSend();

    bool sendEmpty();
    bool recvEmpty();
    
    void clear();

    bool isWorking();

private:
    bool working;
    std::queue<nlohmann::json> send_queue;
    std::queue<nlohmann::json> recv_queue;
    std::mutex send_m;
    std::mutex recv_m;
    std::condition_variable condNewSendData;
    std::condition_variable condNewRecvData;
};

#endif // __COMMUNICATION_QUEUE_H__
