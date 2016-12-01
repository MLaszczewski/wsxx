//
// Created by Michał Łaszczewski on 11/09/16.
//

#ifndef WSXX_WEBSOCKET_H
#define WSXX_WEBSOCKET_H

#include <string>
#include <functional>

namespace wsxx {

  class WebSocket {
  public:

    enum class PacketType {
      Continuation = 0x0,
      Text = 0x1,
      Binary = 0x2,
      Ping = 0x9,
      Pong = 0xA
    };

    enum class ErrorType {
      Timeout,
      Closed
    };

    enum class State {
      Connecting = 0,
      Open = 1,
      Closing	= 2,
      Closed = 3
    };

    using messageCallback = std::function<void(std::string data, PacketType type)>;
    using errorCallback = std::function<void()>;
    using closeCallback = std::function<void(int code, std::string reason, bool wasClean)>;
    using openCallback = std::function<void()>;

    WebSocket(std::string url);
    WebSocket(std::string url, openCallback onOpenp, messageCallback onMessagep, closeCallback onClosep);
    ~WebSocket();

    void close(unsigned short code, std::string reason);
    void close();
    void send(std::string data, PacketType type);
    State getState();
    unsigned int bufferedAmount();

    void setOnOpen(openCallback callback);
    void setOnClose(closeCallback callback);
    void setOnMessage(messageCallback callback);
    void setOnError(errorCallback callback);

    messageCallback onMessage;
    errorCallback onError;
    openCallback onOpen;
    closeCallback onClose;


  protected:
    #ifdef EMSCRIPTEN
    unsigned int socketId;
    static unsigned int lastSocketId;
    #endif

  };

}

#endif //WSXX_WEBSOCKET_H
