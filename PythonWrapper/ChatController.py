import LoLClientAPI
import time

api = LoLClientAPI.LoLClientAPI ();

while True:
	print "Sending ..."
	api.send_chat_message ("Hello");
	
	lastMsg = api.get_chat_message ();
	if lastMsg is not None:
		print "> %s" % lastMsg;
	
	
	time.sleep (1);