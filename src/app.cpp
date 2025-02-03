#include <uwebsockets/App.h>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <random>

struct PerSocketData {};

uint16_t generate_random_value() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution distrib(1, 65534);
    return static_cast<uint16_t>(distrib(gen));
}

class WebSocketServer {
public:
    explicit WebSocketServer(const uint16_t &port) : port_(port) {
        websockets_ = std::make_unique<std::unordered_map<std::string, std::unordered_set<uWS::WebSocket<false, true, PerSocketData> *>>>();
    }

    bool& get_is_ready_() {
        return this->is_ready_;
    }

    uWS::Loop* get_loop_() {
        return this->loop_;
    }

    void add_endpoint(const std::string& endpoint) const {
        this->app_->ws<PerSocketData>(endpoint, {
            .compression = uWS::SHARED_COMPRESSOR,
            .maxPayloadLength = 1 * 1024 * 1024,
            .idleTimeout = 16,
            .maxBackpressure = 1 * 1024 * 1024,
            .closeOnBackpressureLimit = false,
            .resetIdleTimeoutOnSend = false,
            .sendPingsAutomatically = true,
            .upgrade = nullptr,
            .open = [this, endpoint](auto* ws) {
                (*this->websockets_)[endpoint].insert(ws);

                std::cout << "Connected to " << endpoint << std::endl;
            },
            .close = [this, endpoint]([[maybe_unused]] auto* ws, int code, std::string_view message) {
                websockets_->erase(endpoint);

                std::cout << "Disconnected from " << endpoint << " (" << message << ", err code: " << code << ") \n";
            }
        });
    }

    void init() {
        this->app_ = std::make_shared<uWS::App>();

        this->add_endpoint("/endpoint1");
        this->add_endpoint("/endpoint2");
        this->add_endpoint("/endpoint3");
        this->add_endpoint("/endpoint4");
        this->add_endpoint("/endpoint5");
        this->add_endpoint("/endpoint6");
        this->add_endpoint("/endpoint7");
        this->add_endpoint("/endpoint8");
        this->add_endpoint("/endpoint9");
        this->add_endpoint("/endpoint10");
        this->add_endpoint("/endpoint11");
        this->add_endpoint("/endpoint12");
        this->add_endpoint("/endpoint13");
        this->add_endpoint("/endpoint14");
        this->add_endpoint("/endpoint15");
        this->add_endpoint("/endpoint16");
        this->add_endpoint("/endpoint17");
        this->add_endpoint("/endpoint18");
        this->add_endpoint("/endpoint19");
        this->add_endpoint("/endpoint20");
        this->add_endpoint("/endpoint21");
        this->add_endpoint("/endpoint22");
        this->add_endpoint("/endpoint23");
        this->add_endpoint("/endpoint24");
        this->add_endpoint("/endpoint25");
        this->add_endpoint("/endpoint26");
        this->add_endpoint("/endpoint27");
        this->add_endpoint("/endpoint28");
        this->add_endpoint("/endpoint29");
        this->add_endpoint("/endpoint30");
        this->add_endpoint("/endpoint31");
        this->add_endpoint("/endpoint32");
        this->add_endpoint("/endpoint33");
        this->add_endpoint("/endpoint34");
        this->add_endpoint("/endpoint35");
        this->add_endpoint("/endpoint36");
        this->add_endpoint("/endpoint37");
        this->add_endpoint("/endpoint38");
        this->add_endpoint("/endpoint39");
        this->add_endpoint("/endpoint40");
        this->add_endpoint("/endpoint41");
        this->add_endpoint("/endpoint42");
        this->add_endpoint("/endpoint43");
        this->add_endpoint("/endpoint44");
        this->add_endpoint("/endpoint45");
        this->add_endpoint("/endpoint46");
        this->add_endpoint("/endpoint47");
        this->add_endpoint("/endpoint48");
        this->add_endpoint("/endpoint49");
        this->add_endpoint("/endpoint50");
        this->add_endpoint("/endpoint51");
        this->add_endpoint("/endpoint52");
        this->add_endpoint("/endpoint53");
        this->add_endpoint("/endpoint54");
        this->add_endpoint("/endpoint55");
        this->add_endpoint("/endpoint56");
        this->add_endpoint("/endpoint57");
        this->add_endpoint("/endpoint58");
        this->add_endpoint("/endpoint59");
        this->add_endpoint("/endpoint60");
        this->add_endpoint("/endpoint61");
        this->add_endpoint("/endpoint62");
        this->add_endpoint("/endpoint63");
        this->add_endpoint("/endpoint64");
        this->add_endpoint("/endpoint65");
        this->add_endpoint("/endpoint66");
        this->add_endpoint("/endpoint67");
        this->add_endpoint("/endpoint68");
        this->add_endpoint("/endpoint69");
        this->add_endpoint("/endpoint70");    
        this->add_endpoint("/endpoint71");
        this->add_endpoint("/endpoint72");
        this->add_endpoint("/endpoint73");
        this->add_endpoint("/endpoint74");
        this->add_endpoint("/endpoint75");
        this->add_endpoint("/endpoint76");
        this->add_endpoint("/endpoint77");
        this->add_endpoint("/endpoint78");
        this->add_endpoint("/endpoint79");
        this->add_endpoint("/endpoint80");  
        this->add_endpoint("/endpoint81");
        this->add_endpoint("/endpoint82");
        this->add_endpoint("/endpoint83");
        this->add_endpoint("/endpoint84");
        this->add_endpoint("/endpoint85");
        this->add_endpoint("/endpoint86");
        this->add_endpoint("/endpoint87");
        this->add_endpoint("/endpoint88");
        this->add_endpoint("/endpoint89");
        this->add_endpoint("/endpoint90");  
        this->add_endpoint("/endpoint91");
        this->add_endpoint("/endpoint92");
        this->add_endpoint("/endpoint93");
        this->add_endpoint("/endpoint94");
        this->add_endpoint("/endpoint95");
        this->add_endpoint("/endpoint96");
        this->add_endpoint("/endpoint97");
        this->add_endpoint("/endpoint98");
        this->add_endpoint("/endpoint99");
        this->add_endpoint("/endpoint100");

        this->app_->listen(this->port_, [this](auto* listen_socket) {
            if (listen_socket) {
                std::cout << "WebSocket Server Listening on port " + std::to_string(this->port_) << std::endl;
                this->is_ready_ = true;
            }
        });

        this->loop_ = uWS::Loop::get();
    }

    void start() const {
        this->app_->run();
    }

    void stop() const {
        this->app_->close();
    }

    void broadcast_message(const std::string &endpoint, const std::string& data) const {
        for (auto* ws : (*this->websockets_)[endpoint]) {
            ws->send(data, uWS::OpCode::TEXT);
        }
    }
private:
    bool is_ready_ = false;

    uint16_t port_;
    uWS::Loop *loop_;
    std::shared_ptr<uWS::App> app_;
    
    std::unique_ptr<std::unordered_map<std::string, std::unordered_set<uWS::WebSocket<false, true, PerSocketData> *>>> websockets_;
};

[[noreturn]] void periodically_broadcast(WebSocketServer& ws, const std::string_view& endpoint) {
    while (true) {
        if (ws.get_is_ready_()) {
            ws.get_loop_()->defer([&ws, endpoint] () {
                ws.broadcast_message(std::string(endpoint), "message from endpoint " + std::string(endpoint) + " (" + std::to_string(generate_random_value()) + ")");
            });
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

int main() {
    WebSocketServer ws(9000);

    std::thread ws_thread([&ws]() {
        ws.init();
        ws.start();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    std::thread transmitter_1([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint1"); });
    std::thread transmitter_2([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint2"); });
    std::thread transmitter_3([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint3"); });
    std::thread transmitter_4([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint4"); });
    std::thread transmitter_5([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint5"); });
    std::thread transmitter_6([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint6"); });
    std::thread transmitter_7([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint7"); });
    std::thread transmitter_8([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint8"); });
    std::thread transmitter_9([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint9"); });
    std::thread transmitter_10([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint10"); });
    std::thread transmitter_11([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint11"); });
    std::thread transmitter_12([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint12"); });
    std::thread transmitter_13([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint13"); });
    std::thread transmitter_14([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint14"); });
    std::thread transmitter_15([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint15"); });
    std::thread transmitter_16([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint16"); });
    std::thread transmitter_17([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint17"); });
    std::thread transmitter_18([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint18"); });
    std::thread transmitter_19([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint19"); });
    std::thread transmitter_20([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint20"); });
    std::thread transmitter_21([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint21"); });
    std::thread transmitter_22([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint22"); });
    std::thread transmitter_23([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint23"); });
    std::thread transmitter_24([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint24"); });
    std::thread transmitter_25([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint25"); });
    std::thread transmitter_26([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint26"); });
    std::thread transmitter_27([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint27"); });
    std::thread transmitter_28([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint28"); });
    std::thread transmitter_29([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint29"); });
    std::thread transmitter_30([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint30"); });
    std::thread transmitter_31([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint31"); });
    std::thread transmitter_32([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint32"); });
    std::thread transmitter_33([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint33"); });
    std::thread transmitter_34([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint34"); });
    std::thread transmitter_35([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint35"); });
    std::thread transmitter_36([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint36"); });
    std::thread transmitter_37([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint37"); });
    std::thread transmitter_38([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint38"); });
    std::thread transmitter_39([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint39"); });
    std::thread transmitter_40([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint40"); });
    std::thread transmitter_41([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint41"); });
    std::thread transmitter_42([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint42"); });
    std::thread transmitter_43([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint43"); });
    std::thread transmitter_44([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint44"); });
    std::thread transmitter_45([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint45"); });
    std::thread transmitter_46([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint46"); });
    std::thread transmitter_47([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint47"); });
    std::thread transmitter_48([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint48"); });
    std::thread transmitter_49([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint49"); });
    std::thread transmitter_50([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint50"); });
    std::thread transmitter_51([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint51"); });
    std::thread transmitter_52([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint52"); });
    std::thread transmitter_53([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint53"); });
    std::thread transmitter_54([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint54"); });
    std::thread transmitter_55([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint55"); });
    std::thread transmitter_56([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint56"); });
    std::thread transmitter_57([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint57"); });
    std::thread transmitter_58([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint58"); });
    std::thread transmitter_59([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint59"); });
    std::thread transmitter_60([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint60"); });
    std::thread transmitter_61([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint61"); });
    std::thread transmitter_62([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint62"); });
    std::thread transmitter_63([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint63"); });
    std::thread transmitter_64([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint64"); });
    std::thread transmitter_65([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint65"); });
    std::thread transmitter_66([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint66"); });
    std::thread transmitter_67([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint67"); });
    std::thread transmitter_68([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint68"); });
    std::thread transmitter_69([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint69"); });
    std::thread transmitter_70([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint70"); });
    std::thread transmitter_71([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint71"); });
    std::thread transmitter_72([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint72"); });
    std::thread transmitter_73([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint73"); });
    std::thread transmitter_74([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint74"); });
    std::thread transmitter_75([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint75"); });
    std::thread transmitter_76([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint76"); });
    std::thread transmitter_77([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint77"); });
    std::thread transmitter_78([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint78"); });
    std::thread transmitter_79([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint79"); });
    std::thread transmitter_80([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint80"); });
    std::thread transmitter_81([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint81"); });
    std::thread transmitter_82([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint82"); });
    std::thread transmitter_83([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint83"); });
    std::thread transmitter_84([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint84"); });
    std::thread transmitter_85([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint85"); });
    std::thread transmitter_86([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint86"); });
    std::thread transmitter_87([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint87"); });
    std::thread transmitter_88([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint88"); });
    std::thread transmitter_89([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint89"); });
    std::thread transmitter_90([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint90"); });
    std::thread transmitter_91([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint91"); });
    std::thread transmitter_92([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint92"); });
    std::thread transmitter_93([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint93"); });
    std::thread transmitter_94([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint94"); });
    std::thread transmitter_95([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint95"); });
    std::thread transmitter_96([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint96"); });
    std::thread transmitter_97([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint97"); });
    std::thread transmitter_98([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint98"); });
    std::thread transmitter_99([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint99"); });
    std::thread transmitter_100([&ws]() { periodically_broadcast(std::ref(ws), "/endpoint100"); });

    ws_thread.join();

    transmitter_1.join();
    transmitter_2.join();
    transmitter_3.join();   
    transmitter_4.join();
    transmitter_5.join();
    transmitter_6.join();
    transmitter_7.join();
    transmitter_8.join();
    transmitter_9.join();
    transmitter_10.join();
    transmitter_11.join();
    transmitter_12.join();
    transmitter_13.join();
    transmitter_14.join();
    transmitter_15.join();
    transmitter_16.join();
    transmitter_17.join();
    transmitter_18.join();
    transmitter_19.join();
    transmitter_20.join();
    transmitter_21.join();
    transmitter_22.join();
    transmitter_23.join();
    transmitter_24.join();
    transmitter_25.join();
    transmitter_26.join();
    transmitter_27.join();
    transmitter_28.join();
    transmitter_29.join();
    transmitter_30.join();
    transmitter_31.join();
    transmitter_32.join();
    transmitter_33.join();
    transmitter_34.join();
    transmitter_35.join();
    transmitter_36.join();
    transmitter_37.join();
    transmitter_38.join();
    transmitter_39.join();
    transmitter_40.join();
    transmitter_41.join();
    transmitter_42.join();
    transmitter_43.join();
    transmitter_44.join();
    transmitter_45.join();
    transmitter_46.join();
    transmitter_47.join();
    transmitter_48.join();
    transmitter_49.join();
    transmitter_50.join();
    transmitter_51.join();
    transmitter_52.join();
    transmitter_53.join();
    transmitter_54.join();
    transmitter_55.join();
    transmitter_56.join();
    transmitter_57.join();
    transmitter_58.join();
    transmitter_59.join();
    transmitter_60.join();
    transmitter_61.join();
    transmitter_62.join();
    transmitter_63.join();
    transmitter_64.join();
    transmitter_65.join();
    transmitter_66.join();
    transmitter_67.join();
    transmitter_68.join();
    transmitter_69.join();
    transmitter_70.join();
    transmitter_71.join();
    transmitter_72.join();
    transmitter_73.join();
    transmitter_74.join();
    transmitter_75.join();
    transmitter_76.join();
    transmitter_77.join();
    transmitter_78.join();
    transmitter_79.join();
    transmitter_80.join();
    transmitter_81.join();
    transmitter_82.join();
    transmitter_83.join();
    transmitter_84.join();
    transmitter_85.join();
    transmitter_86.join();
    transmitter_87.join();
    transmitter_88.join();
    transmitter_89.join();
    transmitter_90.join();
    transmitter_91.join();
    transmitter_92.join();
    transmitter_93.join();
    transmitter_94.join();
    transmitter_95.join();
    transmitter_96.join();
    transmitter_97.join();
    transmitter_98.join();
    transmitter_99.join();
    transmitter_100.join();

    return 0;
}
