
class Network
{
public:
    Network();

    bool init(String ssid, String pass);

    String getLocalIP() const;
};