
//#include "dataStructure.h"
#include "net.h"
//#include "../../ChromeDownload/vcpkg-master/vcpkg-master/installed/x86-windows/tools/protobuf/MyQQ3/proto.pb.h"
//extern websocket_endpoint endpoint;
//typedef websocketpp::client<websocketpp::config::asio_client> client;
std::string dec2hex(int i) //将int转成16进制字符串
{
    std::stringstream ioss; //定义字符串流
    std::string s_temp; //存放转化后字符
    ioss << std::resetiosflags(std::ios::uppercase) << std::setw(8) << std::setfill('0') << std::hex << i; //以十六制(小写)形式输出//取消大写的设置
    ioss >> s_temp;
    return s_temp;
}
/*
websocket_endpoint::websocket_endpoint(int id, websocketpp::connection_hdl hdl, std::string uri)
    : m_id(id)
    , m_hdl(hdl)
    , m_status("Connecting")
    , m_uri(uri)
    , m_server("N/A"){}

void websocket_endpoint::on_open(client* c, websocketpp::connection_hdl hdl) {
    m_status = "Open";

    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
    m_hdl = hdl;
}

void websocket_endpoint::on_fail(client* c, websocketpp::connection_hdl hdl) {
    m_status = "Failed";

    client::connection_ptr con = c->get_con_from_hdl(hdl);
    m_server = con->get_response_header("Server");
    m_error_reason = con->get_ec().message();
}

void websocket_endpoint::on_close(client* c, websocketpp::connection_hdl hdl) {
    m_status = "Closed";
    client::connection_ptr con = c->get_con_from_hdl(hdl);
    std::stringstream s;
    s << "close code: " << con->get_remote_close_code() << " ("
        << websocketpp::close::status::get_string(con->get_remote_close_code())
        << "), close reason: " << con->get_remote_close_reason();
    m_error_reason = s.str();
}

void websocket_endpoint::on_message(websocketpp::connection_hdl, client::message_ptr msg) {


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


}

websocketpp::connection_hdl websocket_endpoint::get_hdl() const {
    return m_hdl;
}

int websocket_endpoint::get_id() const {
    return m_id;
}

std::string websocket_endpoint::get_status() const {
    return m_status;
}

void websocket_endpoint::record_sent_message(std::string message) {
    m_messages.push_back(">> " + message);
}


std::ostream& operator<< (std::ostream& out, websocket_endpoint const& data) {
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



websocket_endpoint::websocket_endpoint() 
{
    m_endpoint.set_access_channels(websocketpp::log::alevel::all);
    m_endpoint.set_error_channels(websocketpp::log::elevel::all);

    m_endpoint.init_asio();
    m_endpoint.start_perpetual();

    m_thread = websocketpp::lib::make_shared<websocketpp::lib::thread>(&client::run, &m_endpoint);
}

websocket_endpoint::~websocket_endpoint() {
    m_endpoint.stop_perpetual();
    if (this != nullptr)
    {
        if(this->get_status()!="Open"){}
        else
        {
            std::cout << "> Closing connection " << this->get_id() << std::endl;

            websocketpp::lib::error_code ec;
            m_endpoint.close(this->get_hdl(), websocketpp::close::status::going_away, "", ec);
            if (ec) {
                std::cout << "> Error closing connection " << this->get_id() << ": "
                    << ec.message() << std::endl;
            }
        }
    }

    m_thread->join();
}

int websocket_endpoint::connect(std::string const& uri) {
    websocketpp::lib::error_code ec;
    std::cout<<"connecting..."<<std::endl;
    client::connection_ptr con = m_endpoint.get_connection(uri, ec);

    if (ec) {
        std::cout << "> Connect initialization error: " << ec.message() << std::endl;
        return -1;
    }
    id = 1;

    //con_m = websocketpp::lib::make_shared<websocket_endpoint>(id, con->get_handle(), uri);
    con->set_open_handler(websocketpp::lib::bind(&websocket_endpoint::on_open, this, &m_endpoint, websocketpp::lib::placeholders::_1));
    con->set_fail_handler(websocketpp::lib::bind(&websocket_endpoint::on_fail, this, &m_endpoint, websocketpp::lib::placeholders::_1));
    con->set_close_handler(websocketpp::lib::bind(&websocket_endpoint::on_close, this, &m_endpoint, websocketpp::lib::placeholders::_1));
    con->set_message_handler(websocketpp::lib::bind(&websocket_endpoint::on_message, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));

    m_endpoint.connect(con);

    return id;
}

void websocket_endpoint::close(websocketpp::close::status::value code, std::string reason) {
    websocketpp::lib::error_code ec;

    m_endpoint.close(this->get_hdl(), code, reason, ec);
    if (ec) {
        std::cout << "> Error initiating close: " << ec.message() << std::endl;
    }
}

void websocket_endpoint::send(std::string messageContent, message_type mst) {
    websocketpp::lib::error_code ec;

    std::string str = dec2hex((unsigned int)mst) + dec2hex(messageContent.length()) + dec2hex(50);
    std::string message = str + messageContent;
    m_endpoint.send(this->get_hdl(),
        message, websocketpp::frame::opcode::BINARY, ec);
    if (ec) {
        std::cout << "> Error sending message: " << ec.message() << std::endl;
        return;
    }

    this->record_sent_message(message);
}
*/
/*
websocket_endpoint::ptr websocket_endpoint::get_metadata() const {
    return con_m;
}
websocket_endpoint::ptr websocket_endpoint::get_con_m() const
{
    return con_m;
}
*/
//websocket_endpoint endpoint;

