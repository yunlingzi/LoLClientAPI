import LoLClientAPI
import time

api = LoLClientAPI.LoLClientAPI ();

api.log_chat_message ('<font family="Courier New" color="#BE00EE">Hi there, </font><font color="#006EBF" size="37">stranger !</font>');
time.sleep(1);
api.log_chat_message ('<font color="#DDAA33">LoLClientAPI</font> <font color="#ffffff">lets you modify <font color="#00ff00">a lot of things :-)</font>');
time.sleep(1);
api.log_chat_message ('<font color="#ffffff">Let\'s have</font> <font color="#ff0000">some fun programming things :D</font>');

while True:
	message = api.get_chat_message ();
	if message != None:
		print "Message received > %s" % message;
		
	time.sleep (1);