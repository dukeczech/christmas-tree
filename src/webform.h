#include <WebServer.h>
#include <PageBuilder.h>

class WebForm
{
public:
    WebForm();
    void init();

    static String mainCheck(PageArgument& args);

    void loop();

    static WebServer server;
};