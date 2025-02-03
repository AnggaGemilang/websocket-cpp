#include <uwebsockets/App.h>
#include <iostream>
#include <thread>
#include <random>

struct PerSocketData {};

uint16_t generate_random_value() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 65534);
    return static_cast<uint16_t>(distrib(gen));
}

class WebSocketServer {
public:
    explicit WebSocketServer(const uint16_t &port, const std::string_view &url) : port_(port), url_(url) {}

    bool& get_is_ready_() {
        return this->is_ready_;
    }

    uWS::Loop* get_loop_() {
        return this->loop_;
    }

    void init() {
        this->app_ = std::make_shared<uWS::App>();

        this->app_->ws<PerSocketData>(this->url_, {
            .compression = uWS::SHARED_COMPRESSOR,
            .maxPayloadLength = 21 * 1024 * 1024,
            .idleTimeout = 16,
            .maxBackpressure = 21 * 1024 * 1024,
            .closeOnBackpressureLimit = false,
            .resetIdleTimeoutOnSend = false,
            .sendPingsAutomatically = true,
            .upgrade = nullptr,
            .open = [this](auto* ws) {
                ws->subscribe("broadcast-data");

                std::cout << "Connected to " << this->url_ << "\n";
            },
            .close = [this](auto* ws, int code, std::string_view message) {
                ws->unsubscribe("broadcast-data");

                std::cout << "Disconnected from " << this->url_ << " (" << message << ", err code: " << code << ") \n";
            }
        });

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

    void broadcast_message
    (
        std::string_view broadcast,
        std::string_view data
    ) const
    {
        this->app_->publish(broadcast, data, uWS::OpCode::TEXT, false);
    }

private:
    bool is_ready_ = false;

    uint16_t port_;
    std::string url_;
    std::shared_ptr<uWS::App> app_;
    uWS::Loop* loop_;
};

[[noreturn]] void periodically_broadcast(WebSocketServer &ws, const std::string_view& port) {
    while (true) {
        if (ws.get_is_ready_()) {
            ws.get_loop_()->defer([&ws, port] () {
                ws.broadcast_message("broadcast-data", "message from port " + std::string(port) + " (" + std::to_string(generate_random_value()) + ")");
            });
            std::this_thread::sleep_for(std::chrono::milliseconds(200));            
        }
    }
}

int main() {
    // Websocket 1
    WebSocketServer ws(7000, "/endpoint1");

    std::thread ws_thread_1([&ws]() {
        ws.init();
        ws.start();
    });

    // Websocket 2
    WebSocketServer ws2(7001, "/endpoint2");

    std::thread ws_thread_2([&ws2]() {
        ws2.init();
        ws2.start();
    });

    // Websocket 3
    WebSocketServer ws3(7002, "/endpoint3");

    std::thread ws_thread_3([&ws3]() {
        ws3.init();
        ws3.start();
    });

    // Websocket 4
    WebSocketServer ws4(7003, "/endpoint4");

    std::thread ws_thread_4([&ws4]() {
        ws4.init();
        ws4.start();
    });

    // Websocket 5
    WebSocketServer ws5(7004, "/endpoint5");

    std::thread ws_thread_5([&ws5]() {
        ws5.init();
        ws5.start();
    });

    // Websocket 6
    WebSocketServer ws6(7005, "/endpoint6");

    std::thread ws_thread_6([&ws6]() {
        ws6.init();
        ws6.start();
    });

    // Websocket 7
    WebSocketServer ws7(7006, "/endpoint7");

    std::thread ws_thread_7([&ws7]() {
        ws7.init();
        ws7.start();
    });

    // Websocket 8
    WebSocketServer ws8(7007, "/endpoint8");

    std::thread ws_thread_8([&ws8]() {
        ws8.init();
        ws8.start();
    });

    // Websocket 9
    WebSocketServer ws9(7008, "/endpoint9");

    std::thread ws_thread_9([&ws9]() {
        ws9.init();
        ws9.start();
    });

    // Websocket 10
    WebSocketServer ws10(7009, "/endpoint10");

    std::thread ws_thread_10([&ws10]() {
        ws10.init();
        ws10.start();
    });

    // Websocket 11
    WebSocketServer ws11(7010, "/endpoint11");

    std::thread ws_thread_11([&ws11]() {
        ws11.init();
        ws11.start();
    });

    // Websocket 12
    WebSocketServer ws12(7011, "/endpoint12");

    std::thread ws_thread_12([&ws12]() {
        ws12.init();
        ws12.start();
    });

    // Websocket 13
    WebSocketServer ws13(7012, "/endpoint13");

    std::thread ws_thread_13([&ws13]() {
        ws13.init();
        ws13.start();
    });

    // Websocket 14
    WebSocketServer ws14(7013, "/endpoint14");

    std::thread ws_thread_14([&ws14]() {
        ws14.init();
        ws14.start();
    });

    // Websocket 15
    WebSocketServer ws15(7014, "/endpoint15");

    std::thread ws_thread_15([&ws15]() {
        ws15.init();
        ws15.start();
    });    

    // Websocket 16
    WebSocketServer ws16(7015, "/endpoint16");

    std::thread ws_thread_16([&ws16]() {
        ws16.init();
        ws16.start();
    });

    // Websocket 17
    WebSocketServer ws17(7016, "/endpoint17");

    std::thread ws_thread_17([&ws17]() {
        ws17.init();
        ws17.start();
    });    

    // Websocket 18
    WebSocketServer ws18(7017, "/endpoint18");

    std::thread ws_thread_18([&ws18]() {
        ws18.init();
        ws18.start();
    });    

    // Websocket 19
    WebSocketServer ws19(7018, "/endpoint19");

    std::thread ws_thread_19([&ws19]() {
        ws19.init();
        ws19.start();
    });    

    // Websocket 20
    WebSocketServer ws20(7019, "/endpoint20");

    std::thread ws_thread_20([&ws20]() {
        ws20.init();
        ws20.start();
    });

    // Websocket 21
    WebSocketServer ws21(7020, "/endpoint21");

    std::thread ws_thread_21([&ws21]() {
        ws21.init();
        ws21.start();
    });

    // Websocket 22
    WebSocketServer ws22(7021, "/endpoint22");

    std::thread ws_thread_22([&ws22]() {
        ws22.init();
        ws22.start();
    });

    // Websocket 23
    WebSocketServer ws23(7022, "/endpoint23");

    std::thread ws_thread_23([&ws23]() {
        ws23.init();
        ws23.start();
    });

    // Websocket 24
    WebSocketServer ws24(7023, "/endpoint24");

    std::thread ws_thread_24([&ws24]() {
        ws24.init();
        ws24.start();
    });

    // Websocket 25
    WebSocketServer ws25(7024, "/endpoint25");

    std::thread ws_thread_25([&ws25]() {
        ws25.init();
        ws25.start();
    });

    // Websocket 26
    WebSocketServer ws26(7025, "/endpoint26");

    std::thread ws_thread_26([&ws26]() {
        ws26.init();
        ws26.start();
    });

    // Websocket 27
    WebSocketServer ws27(7026, "/endpoint27");

    std::thread ws_thread_27([&ws27]() {
        ws27.init();
        ws27.start();
    });

    // Websocket 28
    WebSocketServer ws28(7027, "/endpoint28");

    std::thread ws_thread_28([&ws28]() {
        ws28.init();
        ws28.start();
    });

    // Websocket 29
    WebSocketServer ws29(7028, "/endpoint29");

    std::thread ws_thread_29([&ws29]() {
        ws29.init();
        ws29.start();
    });

    // Websocket 30
    WebSocketServer ws30(7029, "/endpoint30");

    std::thread ws_thread_30([&ws30]() {
        ws30.init();
        ws30.start();
    });

    // Websocket 31
    WebSocketServer ws31(7030, "/endpoint31");

    std::thread ws_thread_31([&ws31]() {
        ws31.init();
        ws31.start();
    });

    // Websocket 32
    WebSocketServer ws32(7031, "/endpoint32");

    std::thread ws_thread_32([&ws32]() {
        ws32.init();
        ws32.start();
    });    

    // Websocket 33
    WebSocketServer ws33(7032, "/endpoint33");

    std::thread ws_thread_33([&ws33]() {
        ws33.init();
        ws33.start();
    });

    // Websocket 34
    WebSocketServer ws34(7033, "/endpoint34");

    std::thread ws_thread_34([&ws34]() {
        ws34.init();
        ws34.start();
    });

    // Websocket 35
    WebSocketServer ws35(7034, "/endpoint35");

    std::thread ws_thread_35([&ws35]() {
        ws35.init();
        ws35.start();
    });

    // Websocket 36
    WebSocketServer ws36(7035, "/endpoint36");

    std::thread ws_thread_36([&ws36]() {
        ws36.init();
        ws36.start();
    });    

    // Websocket 37
    WebSocketServer ws37(7036, "/endpoint37");

    std::thread ws_thread_37([&ws37]() {
        ws37.init();
        ws37.start();
    });

    // Websocket 38
    WebSocketServer ws38(7037, "/endpoint38");

    std::thread ws_thread_38([&ws38]() {
        ws38.init();
        ws38.start();
    });

    // Websocket 39
    WebSocketServer ws39(7038, "/endpoint39");

    std::thread ws_thread_39([&ws39]() {
        ws39.init();
        ws39.start();
    });

    // Websocket 40
    WebSocketServer ws40(7039, "/endpoint40");

    std::thread ws_thread_40([&ws40]() {
        ws40.init();
        ws40.start();
    });

    // Websocket 41
    WebSocketServer ws41(7040, "/endpoint41");

    std::thread ws_thread_41([&ws41]() {
        ws41.init();
        ws41.start();
    });

    // Websocket 42
    WebSocketServer ws42(7041, "/endpoint42");

    std::thread ws_thread_42([&ws42]() {
        ws42.init();
        ws42.start();
    });

    // Websocket 43
    WebSocketServer ws43(7042, "/endpoint43");

    std::thread ws_thread_43([&ws43]() {
        ws43.init();
        ws43.start();
    });

    // Websocket 44
    WebSocketServer ws44(7043, "/endpoint44");

    std::thread ws_thread_44([&ws44]() {
        ws44.init();
        ws44.start();
    });

    // Websocket 45
    WebSocketServer ws45(7044, "/endpoint45");

    std::thread ws_thread_45([&ws45]() {
        ws45.init();
        ws45.start();
    });

    // Websocket 46
    WebSocketServer ws46(7045, "/endpoint46");

    std::thread ws_thread_46([&ws46]() {
        ws46.init();
        ws46.start();
    });

    // Websocket 47
    WebSocketServer ws47(7046, "/endpoint47");

    std::thread ws_thread_47([&ws47]() {
        ws47.init();
        ws47.start();
    });

    // Websocket 48
    WebSocketServer ws48(7047, "/endpoint48");

    std::thread ws_thread_48([&ws48]() {
        ws48.init();
        ws48.start();
    });

    // Websocket 49
    WebSocketServer ws49(7048, "/endpoint49");

    std::thread ws_thread_49([&ws49]() {
        ws49.init();
        ws49.start();
    });

    // Websocket 50
    WebSocketServer ws50(7049, "/endpoint50");

    std::thread ws_thread_50([&ws50]() {
        ws50.init();
        ws50.start();
    });

    // Websocket 51
    WebSocketServer ws51(7050, "/endpoint51");

    std::thread ws_thread_51([&ws51]() {
        ws51.init();
        ws51.start();
    });

    // Websocket 52
    WebSocketServer ws52(7051, "/endpoint52");

    std::thread ws_thread_52([&ws52]() {
        ws52.init();
        ws52.start();
    });

    // Websocket 53
    WebSocketServer ws53(7052, "/endpoint53");

    std::thread ws_thread_53([&ws53]() {
        ws53.init();
        ws53.start();
    });

    // Websocket 54
    WebSocketServer ws54(7053, "/endpoint54");

    std::thread ws_thread_54([&ws54]() {
        ws54.init();
        ws54.start();
    });

    // Websocket 55
    WebSocketServer ws55(7054, "/endpoint55");

    std::thread ws_thread_55([&ws55]() {
        ws55.init();
        ws55.start();
    });

    // Websocket 56
    WebSocketServer ws56(7055, "/endpoint56");

    std::thread ws_thread_56([&ws56]() {
        ws56.init();
        ws56.start();
    });

    // Websocket 57
    WebSocketServer ws57(7056, "/endpoint57");

    std::thread ws_thread_57([&ws57]() {
        ws57.init();
        ws57.start();
    });    

    // Websocket 58
    WebSocketServer ws58(7057, "/endpoint58");

    std::thread ws_thread_58([&ws58]() {
        ws58.init();
        ws58.start();
    });    

    // Websocket 59
    WebSocketServer ws59(7058, "/endpoint59");

    std::thread ws_thread_59([&ws59]() {
        ws59.init();
        ws59.start();
    });    

    // Websocket 60
    WebSocketServer ws60(7059, "/endpoint60");

    std::thread ws_thread_60([&ws60]() {
        ws60.init();
        ws60.start();
    });    

    // Websocket 61
    WebSocketServer ws61(7060, "/endpoint61");

    std::thread ws_thread_61([&ws61]() {
        ws61.init();
        ws61.start();
    });    

    // Websocket 62
    WebSocketServer ws62(7061, "/endpoint62");

    std::thread ws_thread_62([&ws62]() {
        ws62.init();
        ws62.start();
    });

    // Websocket 63
    WebSocketServer ws63(7062, "/endpoint63");

    std::thread ws_thread_63([&ws63]() {
        ws63.init();
        ws63.start();
    });

    // Websocket 64
    WebSocketServer ws64(7063, "/endpoint64");

    std::thread ws_thread_64([&ws64]() {
        ws64.init();
        ws64.start();
    });

    // Websocket 65
    WebSocketServer ws65(7064, "/endpoint65");

    std::thread ws_thread_65([&ws65]() {
        ws65.init();
        ws65.start();
    });

    // Websocket 66
    WebSocketServer ws66(7065, "/endpoint66");

    std::thread ws_thread_66([&ws66]() {
        ws66.init();
        ws66.start();
    });

    // Websocket 67
    WebSocketServer ws67(7066, "/endpoint67");

    std::thread ws_thread_67([&ws67]() {
        ws67.init();
        ws67.start();
    });

    // Websocket 68
    WebSocketServer ws68(7067, "/endpoint68");

    std::thread ws_thread_68([&ws68]() {
        ws68.init();
        ws68.start();
    });

    // Websocket 69
    WebSocketServer ws69(7068, "/endpoint69");

    std::thread ws_thread_69([&ws69]() {
        ws69.init();
        ws69.start();
    });

    // Websocket 70
    WebSocketServer ws70(7069, "/endpoint70");

    std::thread ws_thread_70([&ws70]() {
        ws70.init();
        ws70.start();
    });

    // Websocket 71
    WebSocketServer ws71(7070, "/endpoint71");

    std::thread ws_thread_71([&ws71]() {
        ws71.init();
        ws71.start();
    });

    // Websocket 72
    WebSocketServer ws72(7071, "/endpoint72");

    std::thread ws_thread_72([&ws72]() {
        ws72.init();
        ws72.start();
    });

    // Websocket 73
    WebSocketServer ws73(7072, "/endpoint73");

    std::thread ws_thread_73([&ws73]() {
        ws73.init();
        ws73.start();
    });

    // Websocket 74
    WebSocketServer ws74(7073, "/endpoint74");

    std::thread ws_thread_74([&ws74]() {
        ws74.init();
        ws74.start();
    });

    // Websocket 75
    WebSocketServer ws75(7074, "/endpoint75");

    std::thread ws_thread_75([&ws75]() {
        ws75.init();
        ws75.start();
    });

    // Websocket 76
    WebSocketServer ws76(7075, "/endpoint76");

    std::thread ws_thread_76([&ws76]() {
        ws76.init();
        ws76.start();
    });

    // Websocket 77
    WebSocketServer ws77(7076, "/endpoint77");

    std::thread ws_thread_77([&ws77]() {
        ws77.init();
        ws77.start();
    });

    // Websocket 78
    WebSocketServer ws78(7077, "/endpoint78");

    std::thread ws_thread_78([&ws78]() {
        ws78.init();
        ws78.start();
    });

    // Websocket 79
    WebSocketServer ws79(7078, "/endpoint79");

    std::thread ws_thread_79([&ws79]() {
        ws79.init();
        ws79.start();
    });

    // Websocket 80
    WebSocketServer ws80(7079, "/endpoint80");

    std::thread ws_thread_80([&ws80]() {
        ws80.init();
        ws80.start();
    });

    // Websocket 81
    WebSocketServer ws81(7080, "/endpoint81");

    std::thread ws_thread_81([&ws81]() {
        ws81.init();
        ws81.start();
    });

    // Websocket 82
    WebSocketServer ws82(7081, "/endpoint82");

    std::thread ws_thread_82([&ws82]() {
        ws82.init();
        ws82.start();
    });

    // Websocket 83
    WebSocketServer ws83(7082, "/endpoint83");

    std::thread ws_thread_83([&ws83]() {
        ws83.init();
        ws83.start();
    });

    // Websocket 84
    WebSocketServer ws84(7083, "/endpoint84");

    std::thread ws_thread_84([&ws84]() {
        ws84.init();
        ws84.start();
    });

    // Websocket 85
    WebSocketServer ws85(7084, "/endpoint85");

    std::thread ws_thread_85([&ws85]() {
        ws85.init();
        ws85.start();
    });

    // Websocket 86
    WebSocketServer ws86(7085, "/endpoint86");

    std::thread ws_thread_86([&ws86]() {
        ws86.init();
        ws86.start();
    });

    // Websocket 87
    WebSocketServer ws87(7086, "/endpoint87");

    std::thread ws_thread_87([&ws87]() {
        ws87.init();
        ws87.start();
    });

    // Websocket 88
    WebSocketServer ws88(7087, "/endpoint88");

    std::thread ws_thread_88([&ws88]() {
        ws88.init();
        ws88.start();
    });

    // Websocket 89
    WebSocketServer ws89(7088, "/endpoint89");

    std::thread ws_thread_89([&ws89]() {
        ws89.init();
        ws89.start();
    });

    // Websocket 90
    WebSocketServer ws90(7089, "/endpoint90");

    std::thread ws_thread_90([&ws90]() {
        ws90.init();
        ws90.start();
    });

    // Websocket 91
    WebSocketServer ws91(7090, "/endpoint91");

    std::thread ws_thread_91([&ws91]() {
        ws91.init();
        ws91.start();
    });

    // Websocket 92
    WebSocketServer ws92(7091, "/endpoint92");

    std::thread ws_thread_92([&ws92]() {
        ws92.init();
        ws92.start();
    });

    // Websocket 93
    WebSocketServer ws93(7092, "/endpoint93");

    std::thread ws_thread_93([&ws93]() {
        ws93.init();
        ws93.start();
    });

    // Websocket 94
    WebSocketServer ws94(7093, "/endpoint94");

    std::thread ws_thread_94([&ws94]() {
        ws94.init();
        ws94.start();
    });

    // Websocket 95
    WebSocketServer ws95(7094, "/endpoint95");

    std::thread ws_thread_95([&ws95]() {
        ws95.init();
        ws95.start();
    });    

    // Websocket 96
    WebSocketServer ws96(7095, "/endpoint96");

    std::thread ws_thread_96([&ws96]() {
        ws96.init();
        ws96.start();
    });

    // Websocket 97
    WebSocketServer ws97(7096, "/endpoint97");

    std::thread ws_thread_97([&ws97]() {
        ws97.init();
        ws97.start();
    });

    // Websocket 98
    WebSocketServer ws98(7097, "/endpoint98");

    std::thread ws_thread_98([&ws98]() {
        ws98.init();
        ws98.start();
    });

    // Websocket 99
    WebSocketServer ws99(7098, "/endpoint99");

    std::thread ws_thread_99([&ws99]() {
        ws99.init();
        ws99.start();
    });

    // Websocket 100
    WebSocketServer ws100(7099, "/endpoint100");

    std::thread ws_thread_100([&ws100]() {
        ws100.init();
        ws100.start();
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    std::thread transmitter_1([&ws]() {periodically_broadcast(std::ref(ws), "7000");});
    std::thread transmitter_2([&ws2]() {periodically_broadcast(std::ref(ws2), "7001");});
    std::thread transmitter_3([&ws3]() {periodically_broadcast(std::ref(ws3), "7002");});
    std::thread transmitter_4([&ws4]() {periodically_broadcast(std::ref(ws4), "7003");});
    std::thread transmitter_5([&ws5]() {periodically_broadcast(std::ref(ws5), "7004");});
    std::thread transmitter_6([&ws6]() {periodically_broadcast(std::ref(ws6), "7005");});
    std::thread transmitter_7([&ws7]() {periodically_broadcast(std::ref(ws7), "7006");});
    std::thread transmitter_8([&ws8]() {periodically_broadcast(std::ref(ws8), "7007");});
    std::thread transmitter_9([&ws9]() {periodically_broadcast(std::ref(ws9), "7008");});
    std::thread transmitter_10([&ws10]() {periodically_broadcast(std::ref(ws10), "7009");});
    std::thread transmitter_11([&ws11]() {periodically_broadcast(std::ref(ws11), "7010");});
    std::thread transmitter_12([&ws12]() {periodically_broadcast(std::ref(ws12), "7011");});
    std::thread transmitter_13([&ws13]() {periodically_broadcast(std::ref(ws13), "7012");});
    std::thread transmitter_14([&ws14]() {periodically_broadcast(std::ref(ws14), "7013");});
    std::thread transmitter_15([&ws15]() {periodically_broadcast(std::ref(ws15), "7014");});
    std::thread transmitter_16([&ws16]() {periodically_broadcast(std::ref(ws16), "7015");});
    std::thread transmitter_17([&ws17]() {periodically_broadcast(std::ref(ws17), "7016");});
    std::thread transmitter_18([&ws18]() {periodically_broadcast(std::ref(ws18), "7017");});
    std::thread transmitter_19([&ws19]() {periodically_broadcast(std::ref(ws19), "7018");});
    std::thread transmitter_20([&ws20]() {periodically_broadcast(std::ref(ws20), "7019");});
    std::thread transmitter_21([&ws21]() {periodically_broadcast(std::ref(ws21), "7020");});
    std::thread transmitter_22([&ws22]() {periodically_broadcast(std::ref(ws22), "7021");});
    std::thread transmitter_23([&ws23]() {periodically_broadcast(std::ref(ws23), "7022");});
    std::thread transmitter_24([&ws24]() {periodically_broadcast(std::ref(ws24), "7023");});
    std::thread transmitter_25([&ws25]() {periodically_broadcast(std::ref(ws25), "7024");});
    std::thread transmitter_26([&ws26]() {periodically_broadcast(std::ref(ws26), "7025");});
    std::thread transmitter_27([&ws27]() {periodically_broadcast(std::ref(ws27), "7026");});
    std::thread transmitter_28([&ws28]() {periodically_broadcast(std::ref(ws28), "7027");});
    std::thread transmitter_29([&ws29]() {periodically_broadcast(std::ref(ws29), "7028");});
    std::thread transmitter_30([&ws30]() {periodically_broadcast(std::ref(ws30), "7029");});
    std::thread transmitter_31([&ws31]() {periodically_broadcast(std::ref(ws31), "7030");});
    std::thread transmitter_32([&ws32]() {periodically_broadcast(std::ref(ws32), "7031");});
    std::thread transmitter_33([&ws33]() {periodically_broadcast(std::ref(ws33), "7032");});
    std::thread transmitter_34([&ws34]() {periodically_broadcast(std::ref(ws34), "7033");});
    std::thread transmitter_35([&ws35]() {periodically_broadcast(std::ref(ws35), "7034");});
    std::thread transmitter_36([&ws36]() {periodically_broadcast(std::ref(ws36), "7035");});
    std::thread transmitter_37([&ws37]() {periodically_broadcast(std::ref(ws37), "7036");});
    std::thread transmitter_38([&ws38]() {periodically_broadcast(std::ref(ws38), "7037");});
    std::thread transmitter_39([&ws39]() {periodically_broadcast(std::ref(ws39), "7038");});
    std::thread transmitter_40([&ws40]() {periodically_broadcast(std::ref(ws40), "7039");});
    std::thread transmitter_41([&ws41]() {periodically_broadcast(std::ref(ws41), "7040");});
    std::thread transmitter_42([&ws42]() {periodically_broadcast(std::ref(ws42), "7041");});
    std::thread transmitter_43([&ws43]() {periodically_broadcast(std::ref(ws43), "7042");});
    std::thread transmitter_44([&ws44]() {periodically_broadcast(std::ref(ws44), "7043");});
    std::thread transmitter_45([&ws45]() {periodically_broadcast(std::ref(ws45), "7044");});
    std::thread transmitter_46([&ws46]() {periodically_broadcast(std::ref(ws46), "7045");});
    std::thread transmitter_47([&ws47]() {periodically_broadcast(std::ref(ws47), "7046");});
    std::thread transmitter_48([&ws48]() {periodically_broadcast(std::ref(ws48), "7047");});
    std::thread transmitter_49([&ws49]() {periodically_broadcast(std::ref(ws49), "7048");});
    std::thread transmitter_50([&ws50]() {periodically_broadcast(std::ref(ws50), "7049");});
    std::thread transmitter_51([&ws51]() {periodically_broadcast(std::ref(ws51), "7050");});
    std::thread transmitter_52([&ws52]() {periodically_broadcast(std::ref(ws52), "7051");});
    std::thread transmitter_53([&ws53]() {periodically_broadcast(std::ref(ws53), "7052");});
    std::thread transmitter_54([&ws54]() {periodically_broadcast(std::ref(ws54), "7053");});
    std::thread transmitter_55([&ws55]() {periodically_broadcast(std::ref(ws55), "7054");});
    std::thread transmitter_56([&ws56]() {periodically_broadcast(std::ref(ws56), "7055");});
    std::thread transmitter_57([&ws57]() {periodically_broadcast(std::ref(ws57), "7056");});
    std::thread transmitter_58([&ws58]() {periodically_broadcast(std::ref(ws58), "7057");});
    std::thread transmitter_59([&ws59]() {periodically_broadcast(std::ref(ws59), "7058");});
    std::thread transmitter_60([&ws60]() {periodically_broadcast(std::ref(ws60), "7059");});
    std::thread transmitter_61([&ws61]() {periodically_broadcast(std::ref(ws61), "7060");});
    std::thread transmitter_62([&ws62]() {periodically_broadcast(std::ref(ws62), "7061");});
    std::thread transmitter_63([&ws63]() {periodically_broadcast(std::ref(ws63), "7062");});
    std::thread transmitter_64([&ws64]() {periodically_broadcast(std::ref(ws64), "7063");});
    std::thread transmitter_65([&ws65]() {periodically_broadcast(std::ref(ws65), "7064");});
    std::thread transmitter_66([&ws66]() {periodically_broadcast(std::ref(ws66), "7065");});
    std::thread transmitter_67([&ws67]() {periodically_broadcast(std::ref(ws67), "7066");});
    std::thread transmitter_68([&ws68]() {periodically_broadcast(std::ref(ws68), "7067");});
    std::thread transmitter_69([&ws69]() {periodically_broadcast(std::ref(ws69), "7068");});
    std::thread transmitter_70([&ws70]() {periodically_broadcast(std::ref(ws70), "7069");});
    std::thread transmitter_71([&ws71]() {periodically_broadcast(std::ref(ws71), "7070");});
    std::thread transmitter_72([&ws72]() {periodically_broadcast(std::ref(ws72), "7071");});
    std::thread transmitter_73([&ws73]() {periodically_broadcast(std::ref(ws73), "7072");});
    std::thread transmitter_74([&ws74]() {periodically_broadcast(std::ref(ws74), "7073");});
    std::thread transmitter_75([&ws75]() {periodically_broadcast(std::ref(ws75), "7074");});
    std::thread transmitter_76([&ws76]() {periodically_broadcast(std::ref(ws76), "7075");});
    std::thread transmitter_77([&ws77]() {periodically_broadcast(std::ref(ws77), "7076");});
    std::thread transmitter_78([&ws78]() {periodically_broadcast(std::ref(ws78), "7077");});
    std::thread transmitter_79([&ws79]() {periodically_broadcast(std::ref(ws79), "7078");});
    std::thread transmitter_80([&ws80]() {periodically_broadcast(std::ref(ws80), "7079");});
    std::thread transmitter_81([&ws81]() {periodically_broadcast(std::ref(ws81), "7080");});
    std::thread transmitter_82([&ws82]() {periodically_broadcast(std::ref(ws82), "7081");});
    std::thread transmitter_83([&ws83]() {periodically_broadcast(std::ref(ws83), "7082");});
    std::thread transmitter_84([&ws84]() {periodically_broadcast(std::ref(ws84), "7083");});
    std::thread transmitter_85([&ws85]() {periodically_broadcast(std::ref(ws85), "7084");});
    std::thread transmitter_86([&ws86]() {periodically_broadcast(std::ref(ws86), "7085");});
    std::thread transmitter_87([&ws87]() {periodically_broadcast(std::ref(ws87), "7086");});
    std::thread transmitter_88([&ws88]() {periodically_broadcast(std::ref(ws88), "7087");});
    std::thread transmitter_89([&ws89]() {periodically_broadcast(std::ref(ws89), "7088");});
    std::thread transmitter_90([&ws90]() {periodically_broadcast(std::ref(ws90), "7089");});
    std::thread transmitter_91([&ws91]() {periodically_broadcast(std::ref(ws91), "7090");});
    std::thread transmitter_92([&ws92]() {periodically_broadcast(std::ref(ws92), "7091");});
    std::thread transmitter_93([&ws93]() {periodically_broadcast(std::ref(ws93), "7092");});
    std::thread transmitter_94([&ws94]() {periodically_broadcast(std::ref(ws94), "7093");});
    std::thread transmitter_95([&ws95]() {periodically_broadcast(std::ref(ws95), "7094");});
    std::thread transmitter_96([&ws96]() {periodically_broadcast(std::ref(ws96), "7095");});
    std::thread transmitter_97([&ws97]() {periodically_broadcast(std::ref(ws97), "7096");});
    std::thread transmitter_98([&ws98]() {periodically_broadcast(std::ref(ws98), "7097");});
    std::thread transmitter_99([&ws99]() {periodically_broadcast(std::ref(ws99), "7098");});
    std::thread transmitter_100([&ws100]() {periodically_broadcast(std::ref(ws100), "7099");});

    ws_thread_1.join();        
    ws_thread_2.join();        
    ws_thread_3.join();        
    ws_thread_4.join();        
    ws_thread_5.join();        
    ws_thread_6.join();        
    ws_thread_7.join();        
    ws_thread_8.join();        
    ws_thread_9.join();        
    ws_thread_10.join();        
    ws_thread_11.join();        
    ws_thread_12.join();        
    ws_thread_13.join();        
    ws_thread_14.join();
    ws_thread_15.join();
    ws_thread_16.join();
    ws_thread_17.join();
    ws_thread_18.join();
    ws_thread_19.join();
    ws_thread_20.join();
    ws_thread_21.join();
    ws_thread_22.join();
    ws_thread_23.join();
    ws_thread_24.join();
    ws_thread_25.join();
    ws_thread_26.join();
    ws_thread_27.join();
    ws_thread_28.join();
    ws_thread_29.join();
    ws_thread_30.join();
    ws_thread_31.join();
    ws_thread_32.join();
    ws_thread_33.join();
    ws_thread_34.join();
    ws_thread_35.join();
    ws_thread_36.join();
    ws_thread_37.join();
    ws_thread_38.join();
    ws_thread_39.join();
    ws_thread_40.join();
    ws_thread_41.join();
    ws_thread_42.join();
    ws_thread_43.join();
    ws_thread_44.join();
    ws_thread_45.join();
    ws_thread_46.join();
    ws_thread_47.join();
    ws_thread_48.join();
    ws_thread_49.join();
    ws_thread_50.join();
    ws_thread_51.join();
    ws_thread_52.join();
    ws_thread_53.join();
    ws_thread_54.join();
    ws_thread_55.join();
    ws_thread_56.join();
    ws_thread_57.join();
    ws_thread_58.join();
    ws_thread_59.join();
    ws_thread_60.join();
    ws_thread_61.join();
    ws_thread_62.join();
    ws_thread_63.join();
    ws_thread_64.join();
    ws_thread_65.join();
    ws_thread_66.join();
    ws_thread_67.join();
    ws_thread_68.join();
    ws_thread_69.join();
    ws_thread_70.join();
    ws_thread_71.join();
    ws_thread_72.join();
    ws_thread_73.join();
    ws_thread_74.join();
    ws_thread_75.join();
    ws_thread_76.join();
    ws_thread_77.join();
    ws_thread_78.join();
    ws_thread_79.join();
    ws_thread_80.join();
    ws_thread_81.join();
    ws_thread_82.join();
    ws_thread_83.join();
    ws_thread_84.join();
    ws_thread_85.join();
    ws_thread_86.join();
    ws_thread_87.join();
    ws_thread_88.join();
    ws_thread_89.join();
    ws_thread_90.join();
    ws_thread_91.join();
    ws_thread_92.join();
    ws_thread_93.join();
    ws_thread_94.join();
    ws_thread_95.join();
    ws_thread_96.join();
    ws_thread_97.join();
    ws_thread_98.join();
    ws_thread_99.join();
    ws_thread_100.join();

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
