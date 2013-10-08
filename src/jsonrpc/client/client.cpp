/*************************************************************************
 * libjson-rpc-cpp
 *************************************************************************
 * @file    client.cpp
 * @date    03.01.2013
 * @author  Peter Spiess-Knafl <peter.knafl@gmail.com>
 * @license See attached LICENSE.txt
 ************************************************************************/

#include "client.h"

using namespace jsonrpc;

Client::Client(AbstractClientConnector &connector)
    : connector(connector)
{
}

void Client::CallMethod(const std::string &name, const Json::Value &paramter, Json::Value& result) throw(JsonRpcException)
{
    std::string request, response;
    protocol.BuildRequest(name, paramter, request, false);
    connector.SendRPCResponse(request, response);
    protocol.HandleResponse(response, result);
}

Json::Value Client::CallMethod(const std::string& name,
                               const Json::Value& parameter) throw(JsonRpcException)
{
    Json::Value result;
    this->CallMethod(name, parameter, result);
    return result;
}

void Client::CallNotification(const std::string& name, const Json::Value& parameter) throw(JsonRpcException)
{
    std::string request, response;
    protocol.BuildRequest(name, parameter, request, true);
    connector.SendRPCResponse(request, response);
}
