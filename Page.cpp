#include <Arduino.h>
#include "Page.h"
//using namespace std;

String Page_home(){
  String page_home = "<!DOCTYPE html>\
    <html>\
      <head>\
        <meta charset=\"utf-8\">\
        <title></title>\
      </head>\
      <body>\
      <input type=\"button\" value=\"Добавить сериал\" class=\"btn_href\" onclick=\"location.href=\'/add_page\'\"><br>\
    <form action=\"/get_time\" method=\"GET\" id=\"form_time\">\
      <input type=\"text\" name=\"time\" form=\"form_time\" >\
      <input type=\"text\" name=\"tme\" form=\"form_time\" >\
      <input type=\"text\" name=\"tim\" form=\"form_time\" >\
      <input type=\"text\" name=\"ime\" form=\"form_time\" >\
      <input type=\"submit\" value=\"Отправить\" form=\"form_time\">\
    </form>\
      </body>\
    </html>";

return(page_home);
  }
