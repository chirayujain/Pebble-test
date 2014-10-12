{\rtf1\ansi\ansicpg1252\cocoartf1265\cocoasubrtf210
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
\margl1440\margr1440\vieww10800\viewh8400\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural

\f0\fs24 \cf0 #include <pebble.h>\
 \
Window *window;\
TextLayer *text_layer;\
TextLayer *date_layer;\
TextLayer *seconds_layer;\
InverterLayer *inverter_layer;\
InverterLayer *horizontal_layer;\
 \
void handle_timechanges(struct tm *tick_time, TimeUnits units_changed) \{\
	static char time_buffer[10];\
	static char date_buffer[10];\
  static char seconds_buffer[10];\
	\
	strftime(time_buffer, sizeof(time_buffer), "%H %M", tick_time);\
	text_layer_set_text(text_layer, time_buffer);\
	\
	strftime(date_buffer, sizeof(date_buffer), "%b %e", tick_time);\
	text_layer_set_text(date_layer, date_buffer);\
  \
  strftime(seconds_buffer, sizeof(seconds_buffer), "%S", tick_time);\
  text_layer_set_text(seconds_layer, seconds_buffer);\
\}\
 \
void handle_init(void) \{\
	\
	window = window_create();\
	text_layer = text_layer_create(GRect(0, 0, 71, 84));\
  seconds_layer = text_layer_create(GRect(0, 95, 144, 68));\
  \
\
	text_layer_set_text(text_layer, "time");\
	text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));\
	text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);\
\
  text_layer_set_text(seconds_layer, "seconss");\
	text_layer_set_font(seconds_layer, fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));\
	text_layer_set_text_alignment(seconds_layer, GTextAlignmentCenter);\
\
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(text_layer));\
  \
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(seconds_layer));\
  \
	date_layer = text_layer_create(GRect(74, 0, 70, 83));\
	text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);\
	text_layer_set_font(date_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));\
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(date_layer));\
	\
	inverter_layer = inverter_layer_create(GRect(72, 0, 2, 84));\
	layer_add_child(window_get_root_layer(window), inverter_layer_get_layer(inverter_layer));\
  \
  horizontal_layer = inverter_layer_create(GRect(0, 84, 144, 2));\
	layer_add_child(window_get_root_layer(window), inverter_layer_get_layer(horizontal_layer));\
	\
	time_t now = time(NULL);\
	handle_timechanges(localtime(&now), SECOND_UNIT);\
	\
	tick_timer_service_subscribe(SECOND_UNIT, handle_timechanges);\
	\
	window_stack_push(window, true);\
\
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Hello World from the applogs!");\
\}\
 \
void handle_deinit(void) \{\
	\
	text_layer_destroy(text_layer);\
	text_layer_destroy(date_layer);\
  text_layer_destroy(seconds_layer);\
	inverter_layer_destroy(inverter_layer);\
\
	window_destroy(window);\
\}\
 \
int main(void) \{\
	handle_init();\
	app_event_loop();\
	handle_deinit();\
\}}