#include <Arduino.h>
#include "Page.h"
//using namespace std;

String Page_home(){
  String page_home = "<!DOCTYPE html>\
<html>\
  <head>\
    <meta charset=\"utf-8\">\
    <title></title>\
    <style type=\"text/css\">\
      .btn{\
        border: 2px solid #7586AC;\
        border-radius: 5px;\
        background: #00AF64;\
        width: 200px;\
        height: 50px;\
        font\-size\: 20px;\
        font-family:monospace;\
        margin-top: 15px;\
        margin-left: 8px;\
      }\
      .form{\
        margin-left: 10px;\
        width: 216px;\
        margin-top: 15px;\
        border: 2px solid #7586AC;\
        padding-bottom: 5px;\
      }\
    </style>\
  </head>\
  <body>\
  <\div \class=\"form\">\
    <input type=\"button\" value=\"Открыть окно\" class=\"btn\" onclick=\"location.href=\'/open_window\'\"><br>\
    <input type=\"button\" value=\"Закрыть окно\" class=\"btn\" onclick=\"location.href=\'/close_window\'\"><br>\
    </\div>\
    <form \class=\"form\" action=\"/open_to\" method=\"GET\" id=\"open_to\">\
      <label \for=\"range_open\">Открыть окно на указанный процент</label>\
      <input type=\"range\" step=\"5\" value=\"50\" style=\"width: 212px\" id=\"range_open\" name=\"open_procent\" form=\"open_to\">\
      <input type=\"submit\" value=\"Открыть на чуть\" form=\"open_to\" class=\"btn\" style=\"margin-left: 8px\">\
    </form>\
    <form \class=\"form\" action=\"/timer\" method=\"GET\" id=\"run_timer\">\
      <label \for=\"timer\">Выполнить действие через указанное время</label><br>\
      <input type=\"number\" step=\"1\" max=\"60\" style=\"width:30px; height:20px; margin-left:10px\" min=\"1\" id=\"timer\" name=\"time\" form=\"run_timer\"><br><br>\
      <input type=\"radio\" name=\"timer_open\" form=\"run_timer\">Открыть окно<br>\
      <input type=\"radio\" name=\"timer_close\" form=\"run_timer\">Закрыть окно\
      <input type=\"submit\" value=\"Запустить таймер\" form=\"run_timer\" class=\"btn\" style=\"margin-left: 8px\">\
    </form>\
    <form \class=\"form\" action=\"/plan\" method=\"GET\" id=\"run_plan\">\
      Выполнить действие в указанное время<br>\
      <label \for=\"hour\"> Часы   Минуты</label><br>\
      <input type=\"number\" step=\"0\" max=\"24\" style=\"width:30px; height:20px; margin-left:10px\" min=\"1\" id=\"hour\" name=\"hour\" form=\"run_plan\">\
      <input type=\"number\" step=\"0\" max=\"60\" style=\"width:30px; height:20px; margin-left:10px\" min=\"1\"  id=\"minut\" name=\"minut\" form=\"run_plan\"><br><br>\
      <input type=\"radio\" name=\"plan_open\" form=\"run_plan\">Открыть окно<br>\
      <input type=\"radio\" name=\"plan_close\" form=\"run_plan\">Закрыть окно\
      <input type=\"submit\" value=\"Запланировать\" form=\"run_plan\" class=\"btn\" style=\"margin-left: 8px\">\
    </form>\
  </body>\
</html>";

return(page_home);
  }
