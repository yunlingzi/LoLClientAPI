import LoLClientAPI

api = LoLClientAPI.LoLClientAPI ();

x, y = api.get_camera_position ();
print "Camera position = %f / %f" % (x, y);
api.set_camera_position(x, y);

x, y = api.get_camera_angle ();
print "Camera angle = %f / %f" % (x, y);
api.set_camera_angle(x, y);

zoom = api.get_camera_zoom ();
print "Camera zoom = %f" % (zoom);
api.set_camera_zoom (zoom);

x, y = api.get_cursor_position ();
print "Cursor position = %f / %f" % (x, y);


x, y = api.get_destination_position ();
print "Destination position = %f / %f" % (x, y);


x, y = api.get_champion_position ();
print "Champion position = %f / %f" % (x, y);


curHP, maxHP = api.get_champion_hp ();
print "Champion HP = %f / %f" % (curHP, maxHP);


team = api.get_champion_team ();
print "Champion team = %d" % (team);


nbTeammates = api.get_teammates_count ();
print "Teammates count = %d" % (nbTeammates);

for id in range(0, nbTeammates):
	x, y = api.get_teammate_position (id);
	print "Teammate %d position = %f / %f" % (id, x, y);
	
	curHP, maxHP = api.get_teammate_hp (id);
	print "Teammate %d HP = %f / %f" % (id, curHP, maxHP);

	summonerName = api.get_teammate_summoner_name (id);
	print "Teammate %d summonerName = %s" % (id, summonerName);

x, y = api.get_cursor_screen_position ();
print "cursorScreen position = %d / %d" % (x, y);

x, y = api.get_minimap_screen_position ();
print "Minimap position = %d / %d" % (x, y);


summonerName = api.get_current_summoner_name ();
print "Current summonerName = %s" % (summonerName);


time = api.get_game_time ();
print "Current time = %s" % (time);

