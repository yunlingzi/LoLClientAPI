import LoLClientAPI
import time

api = LoLClientAPI.LoLClientAPI ();

api.log_chat_message ('<font color="#00ff00">LoLClientAPI initialization ...</font>');

api.log_chat_message ('<font color="#ff0000">LoLClientAPI : Red message</font>');
api.log_chat_message ('<font color="#00ff00">LoLClientAPI : Green message</font>');
api.log_chat_message ('<font color="#0000ff">LoLClientAPI : Blue message</font>');
api.log_chat_message ('<font color="#000000">LoLClientAPI : Black message</font>');
api.log_chat_message ('<font color="#ffffff">LoLClientAPI : White message</font>');

while True:
	message = api.get_chat_message ();
	if message not None:
		print "Message received > %s" % message;
		
	time.sleep (1);