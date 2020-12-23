#include "webform.h"
#include "config.h"
#include "effects.h"

extern std::vector<Effect*> effects;

const char* loginIndexx =
        "<form name='loginForm'>"
        "<table width='20%' bgcolor='A09F9F' align='center'>"
        "<tr>"
        "<td colspan=2>"
        "<center><font size=4><b>ESP32 Login Page</b></font></center>"
        "<br>"
        "</td>"
        "<br>"
        "<br>"
        "</tr>"
        "<td>Username:</td>"
        "<td><input type='text' size=25 name='userid'><br></td>"
        "</tr>"
        "<br>"
        "<br>"
        "<tr>"
        "<td>Password:</td>"
        "<td><input type='Password' size=25 name='pwd'><br></td>"
        "<br>"
        "<br>"
        "</tr>"
        "<tr>"
        "<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
        "</tr>"
        "</table>"
        "</form>"
        "<script>"
        "function check(form)"
        "{"
        "if(form.userid.value=='admin' && form.pwd.value=='admin')"
        "{"
        "window.open('/serverIndex')"
        "}"
        "else"
        "{"
        " alert('Error Password or Username')/*displays error message*/"
        "}"
        "}"
        "</script>";


const char* config =
        "<form id='form0' class='appnitro' method='get' action='.'>"
        "<div class='form_description'>"
        "<h2>Christmas tree configuration</h2>"
        "</div>"
        "<li id='li_1' class=''>"
        "<label class='description' for='brightness'>Brightness (0-255)</label>"
        "<div>"
        "<input id='brightness' name='brightness' class='element text small' type='text' maxlength='3' value='{{BRIGHTNESS}}'>"
        "</li>"
        //"<input type='hidden' name='form_id' value='1'>"
        "<input id='saveForm' type='submit' name='action' value='Set'>"
        "<br><br>"
        "<input id='restartForm' type='submit' name='action' value='Restart'>"
        "<br><br><br><br>"
        "Effects:<br>{{EFFECTS}}"
        "</form>";

WebServer WebForm::server;

String WebForm::mainCheck(PageArgument& args)
{
    if(args.hasArg("action"))
    {
        if(args.arg("action") == String("Restart"))
        {
            ESP.restart();
        }
        // Redirect http request to connection result page.
        //server.sendHeader("Location", String("http://") + WiFi.localIP().toString(), true);
        server.sendHeader("Location", String("/"), true);
        server.send(303, "text/plain", "");
    }
    return "";
}

WebForm::WebForm()
{
}

PageElement header_elem("<html><body>");
PageElement footer_elem("</body></html>");
PageElement body_elem(config, {
        { "MAIN",       WebForm::mainCheck },
        { "BRIGHTNESS", [](PageArgument& args) {
            WebForm::mainCheck(args);

            if(args.hasArg("brightness"))
            {
                String val = args.arg("brightness");
                Config::setBrigthness(val.toInt());
            }
            return String(Config::getBrigthness());
        }},
        { "EFFECTS",    [](PageArgument& args) {
            String s = "";
            for(Effect* e : effects)
            {
                s += String(e->getName()) + "-> delay: " + e->getDelay() + "ms, elapsed: " + e->getElapsed() + "ms [" + (e->isActive() ? "1" : "0") + "]<br>";
            }
            return s;
        }}
});

PageBuilder page("/", {
        header_elem,
        body_elem,
        footer_elem
});

void WebForm::init()
{
#if 0
    server.on("/", HTTP_GET, [this]() {
        /*if(server.hasArg("sec")){
            String tw = server.arg("sec");
            Serial.println(tw.toInt());
        }*/
        String headers = server.arg(0);

        server.sendHeader("Connection", "close");
        server.send(200, "text/html", config);
    });
#endif
#if 0
    server.on("/serverIndex", HTTP_GET, [this]() {
        server.sendHeader("Connection", "close");
        server.send(200, "text/html", serverIndex);
    });
#endif

    page.insert(server);

    server.begin(80);
}

void WebForm::loop()
{
    server.handleClient();
}

