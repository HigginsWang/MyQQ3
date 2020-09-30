#pragma once
//#include "MyQQ3Client.h"
//#include "logindialog.h"
#include <QtWidgets/QApplication>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>

#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <QObject>

#include <QDialog>
#include <QDebug>
#include <QMetaType>
#include "dataStructure.h"
#include "proto.pb.h"
typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef std::function<void()> Fun;
std::string dec2hex(int i); //将int转成16进制字符串
class connection_metadata {
public:
    typedef websocketpp::lib::shared_ptr<connection_metadata> ptr;

    connection_metadata( websocketpp::connection_hdl hdl, std::string uri)
        :// m_id(id)
         m_hdl(hdl)
        , m_status("Connecting")
        , m_uri(uri)
        , m_server("N/A")
    {}
    /*
    void on_open(client* c, websocketpp::connection_hdl hdl) {
        m_status = "Open";

        client::connection_ptr con = c->get_con_from_hdl(hdl);
        m_server = con->get_response_header("Server");
    }

    void on_fail(client* c, websocketpp::connection_hdl hdl) {
        m_status = "Failed";

        client::connection_ptr con = c->get_con_from_hdl(hdl);
        m_server = con->get_response_header("Server");
        m_error_reason = con->get_ec().message();
    }

    void on_close(client* c, websocketpp::connection_hdl hdl) {
        m_status = "Closed";
        client::connection_ptr con = c->get_con_from_hdl(hdl);
        std::stringstream s;
        s << "close code: " << con->get_remote_close_code() << " ("
            << websocketpp::close::status::get_string(con->get_remote_close_code())
            << "), close reason: " << con->get_remote_close_reason();
        m_error_reason = s.str();
    }

    void on_message(websocketpp::connection_hdl, client::message_ptr msg) {


        if (msg->get_opcode() == websocketpp::frame::opcode::text) {
            std::cout << "msg->payload():" << msg->get_payload() << std::endl;
            std::cout << "msg->get_header():" << msg->get_header() << std::endl;
            m_messages.push_back("<< " + msg->get_payload());
        }
        else {
            //m_messages.push_back("<< " + websocketpp::utility::to_hex(msg->get_payload()));

            //std::cout << "header:" << msg->get_payload().substr(0, 16) << std::endl;
            //消息类型
            message_type a_messageType = (message_type)std::stoi(msg->get_payload().substr(0, 8), nullptr, 16);
            //std::cout << "a_messageType:" << (int)a_messageType << std::endl;

            //消息内容长度
            size_t a_messageConentLength = std::stoi(msg->get_payload().substr(8, 8), nullptr, 16);
            //std::cout << "a_messageConentLength:" << (int)a_messageConentLength << std::endl;

            //保留
            unsigned int a_save = std::stoi(msg->get_payload().substr(16, 8), nullptr, 16);
            //std::cout << "a_save:" << (int)a_save << std::endl;

            //消息内容
            std::string a_messageContent = msg->get_payload().substr(24);
            //std::cout << "a_save:" << a_messageContent << std::endl;
            switch (a_messageType)
            {
            case message_type::BOTH_TEXT:
                std::cout << "text:" + a_messageContent << std::endl;
                break;
            case message_type::S2C_LOGINRET:
                MyQQ3Proto::S2C_LOGINRET s2c_loginret;
                if (s2c_loginret.ParseFromString(a_messageContent)) {
                    if (s2c_loginret.iflogin() == 1) {
                        //emit on_getLoginSuccessfully();
                        //emit QDialog::Accepted;
                        ;
                        std::cout << "login successful" << std::endl;
                    }
                }
                break;
            }
        }
        std::cout << "...................................................................." << std::endl;
    }
    */
    websocketpp::connection_hdl get_hdl() const {
        return m_hdl;
    }

    std::string get_status() const {
        return m_status;
    }

    void record_sent_message(std::string message) {
        m_messages.push_back(">> " + message);
    }

    friend std::ostream& operator<< (std::ostream& out, connection_metadata const& data) {
        out << "> URI: " << data.m_uri << "\n"
            << "> Status: " << data.m_status << "\n"
            << "> Remote Server: " << (data.m_server.empty() ? "None Specified" : data.m_server) << "\n"
            << "> Error/close reason: " << (data.m_error_reason.empty() ? "N/A" : data.m_error_reason) << "\n";
        out << "> Messages Processed: (" << data.m_messages.size() << ") \n";

        std::vector<std::string>::const_iterator it;
        for (it = data.m_messages.begin(); it != data.m_messages.end(); ++it) {
            out << *it << "\n";
        }

        return out;
    }
private:
    //int m_id;
    websocketpp::connection_hdl m_hdl;
    std::string m_status;
    std::string m_uri;
    std::string m_server;
    std::string m_error_reason;
    std::vector<std::string> m_messages;
};

class websocket_endpoint : public QObject {
    Q_OBJECT
signals:
    void loginDone1(QString, QString);
    void loginDone2();

    void receive_S2C_GETALLFRIENDSRET(MyQQ3Proto::S2C_GETALLFRIENDSRET);
public:

    static websocket_endpoint& instance() {
        static websocket_endpoint we;
        return we;
    }

    ~websocket_endpoint() {
        m_endpoint.stop_perpetual();

        if (m_connection_list != nullptr) {
            if (m_connection_list->get_status() != "Open") {
                // Only close open connections
                //continue;
                return;
            }

            //std::cout << "> Closing connection " << m_connection_list->get_id() << std::endl;

            websocketpp::lib::error_code ec;
            m_endpoint.close(m_connection_list->get_hdl(), websocketpp::close::status::going_away, "", ec);
            if (ec) {
                std::cout << "> Error closing connection " //<< m_connection_list->get_id() << ": "
                    << ec.message() << std::endl;
            }
        }

        m_thread->join();
    }
    void on_open(client* c, websocketpp::connection_hdl hdl) {
        m_status = "Open";

        client::connection_ptr con = c->get_con_from_hdl(hdl);
        m_server = con->get_response_header("Server");
    }

    void on_fail(client* c, websocketpp::connection_hdl hdl) {
        m_status = "Failed";

        client::connection_ptr con = c->get_con_from_hdl(hdl);
        m_server = con->get_response_header("Server");
        m_error_reason = con->get_ec().message();
    }

    void on_close(client* c, websocketpp::connection_hdl hdl) {
        m_status = "Closed";
        client::connection_ptr con = c->get_con_from_hdl(hdl);
        std::stringstream s;
        s << "close code: " << con->get_remote_close_code() << " ("
            << websocketpp::close::status::get_string(con->get_remote_close_code())
            << "), close reason: " << con->get_remote_close_reason();
        m_error_reason = s.str();
    }

    void on_message(websocketpp::connection_hdl, client::message_ptr msg) {


        if (msg->get_opcode() == websocketpp::frame::opcode::text) {
            std::cout << "msg->payload():" << msg->get_payload() << std::endl;
            std::cout << "msg->get_header():" << msg->get_header() << std::endl;
            m_messages.push_back("<< " + msg->get_payload());
        }
        else {
            //m_messages.push_back("<< " + websocketpp::utility::to_hex(msg->get_payload()));

            //std::cout << "header:" << msg->get_payload().substr(0, 16) << std::endl;
            //消息类型
            message_type a_messageType = (message_type)std::stoi(msg->get_payload().substr(0, 8), nullptr, 16);
            //std::cout << "a_messageType:" << (int)a_messageType << std::endl;

            //消息内容长度
            size_t a_messageConentLength = std::stoi(msg->get_payload().substr(8, 8), nullptr, 16);
            //std::cout << "a_messageConentLength:" << (int)a_messageConentLength << std::endl;

            //保留
            unsigned int a_save = std::stoi(msg->get_payload().substr(16, 8), nullptr, 16);
            //std::cout << "a_save:" << (int)a_save << std::endl;

            //消息内容
            std::string a_messageContent = msg->get_payload().substr(24);
            //std::cout << "a_save:" << a_messageContent << std::endl;
            switch (a_messageType)
            {
                case message_type::BOTH_TEXT:
                    std::cout << "text:" + a_messageContent << std::endl;
                    break;
                case message_type::S2C_LOGINRET:
                {
                    MyQQ3Proto::S2C_LOGINRET s2c_loginret;
                    if (s2c_loginret.ParseFromString(a_messageContent)) {
                        if (s2c_loginret.iflogin() == 1) {
                            std::cout << s2c_loginret.userid() << std::endl;
                            std::cout << s2c_loginret.username() << std::endl;
                            //emit on_getLoginSuccessfully();
                            //emit QDialog::Accepted;
                            ;
                            std::cout << "login successful" << std::endl;
                            emit loginDone1(QString::fromStdString(s2c_loginret.userid()), QString::fromStdString( s2c_loginret.username()));
                            emit loginDone2();
                        }
                    }
                    break;
                }
                
                case message_type::S2C_GETALLFRIENDSRET:
                {
                    MyQQ3Proto::S2C_GETALLFRIENDSRET s2c_getallfriendsret;
                    if (s2c_getallfriendsret.ParseFromString(a_messageContent)) {
                        /*auto t = s2c_getallfriendsret.mutable_friends();
                        for (auto it = t->begin(); it != t->end(); ++it)
                        {
                            std::cout << it->userid() << std::endl;
                            std::cout << it->username() << std::endl;
                        }*/
                        emit receive_S2C_GETALLFRIENDSRET(s2c_getallfriendsret);
                    
                    }
                    break;
                }
            }
        }
        std::cout << "...................................................................." << std::endl;
    }
    int connect(std::string const& uri) {
        websocketpp::lib::error_code ec;

        client::connection_ptr con = m_endpoint.get_connection(uri, ec);

        if (ec) {
            std::cout << "> Connect initialization error: " << ec.message() << std::endl;
            return -1;
        }

        //int new_id = m_next_id++;
        connection_metadata::ptr metadata_ptr = websocketpp::lib::make_shared<connection_metadata>(con->get_handle(), uri);
        m_connection_list = metadata_ptr;

        con->set_open_handler(websocketpp::lib::bind(
            &websocket_endpoint::on_open,
            this,
            &m_endpoint,
            websocketpp::lib::placeholders::_1
        ));
        con->set_fail_handler(websocketpp::lib::bind(
            &websocket_endpoint::on_fail,
            this,
            &m_endpoint,
            websocketpp::lib::placeholders::_1
        ));
        con->set_close_handler(websocketpp::lib::bind(
            &websocket_endpoint::on_close,
            this,
            &m_endpoint,
            websocketpp::lib::placeholders::_1
        ));
        con->set_message_handler(websocketpp::lib::bind(
            &websocket_endpoint::on_message,
            this,
            websocketpp::lib::placeholders::_1,
            websocketpp::lib::placeholders::_2
        ));

        m_endpoint.connect(con);

        return 0;
    }

    void close(websocketpp::close::status::value code, std::string reason) {
        websocketpp::lib::error_code ec;

        //con_list::iterator metadata_it = m_connection_list.find(id);
        if (m_connection_list == nullptr) {
            std::cout << "> No connection found with id "  << std::endl;
            return;
        }

        m_endpoint.close(m_connection_list->get_hdl(), code, reason, ec);
        if (ec) {
            std::cout << "> Error initiating close: " << ec.message() << std::endl;
        }
    }

    void send(std::string messageContent, message_type mst) {
        websocketpp::lib::error_code ec;
        std::string str = dec2hex((unsigned int)mst) + dec2hex(messageContent.length()) + dec2hex(50);
        std::string message = str + messageContent;
        //con_list::iterator metadata_it = m_connection_list.find();
        if (m_connection_list == nullptr) {
            std::cout << "> No connection found with id "  << std::endl;
            return;
        }

        m_endpoint.send(m_connection_list->get_hdl(), message, websocketpp::frame::opcode::BINARY, ec);
        if (ec) {
            std::cout << "> Error sending message: " << ec.message() << std::endl;
            return;
        }

        m_connection_list->record_sent_message(message);
    }

    connection_metadata::ptr get_metadata() const {
        //con_list::const_iterator metadata_it = m_connection_list.find(id);
        if ( m_connection_list == nullptr) {
            return connection_metadata::ptr();
        }
        else {
            return m_connection_list;//metadata_it->second;
        }
    }
private:
    std::string m_status;
    std::string m_uri;
    std::string m_server;
    std::string m_error_reason;
    std::vector<std::string> m_messages;

    websocket_endpoint() {
        qRegisterMetaType<MyQQ3Proto::S2C_GETALLFRIENDSRET>("MyQQ3Proto::S2C_GETALLFRIENDSRET");
        m_endpoint.set_access_channels(websocketpp::log::alevel::all);
        m_endpoint.set_error_channels(websocketpp::log::elevel::all);

        m_endpoint.init_asio();
        m_endpoint.start_perpetual();

        m_thread = websocketpp::lib::make_shared<websocketpp::lib::thread>(&client::run, &m_endpoint);
    }
    //typedef std::map<int, connection_metadata::ptr> con_list;
    connection_metadata::ptr m_connection_list;
    client m_endpoint;
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;

    //con_list m_connection_list;
    //int m_next_id;
};

