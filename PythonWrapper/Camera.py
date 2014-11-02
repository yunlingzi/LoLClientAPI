import LoLClientAPI
import time

# ======= Configurations =======
threshold   = 200.0
cameraSpeed = 2
camera_scroll_speed_bottom = 1.5

# Weights
championWeight = 1.0
cursorWeight   = 2.0

# ===== Start of the program ======
# Inject LoLClientAPI in LoLProcess
api = LoLClientAPI.LoLClientAPI ();

# Disable client camera behavior
api.set_camera_client_enabled (False);


# Program infinite loop
while (1):

	# Sleep during 1 millisecond so the script doesn't take 100% CPU
	time.sleep(0.001);
	
	# Don't do anything if the cursor is hovering the minimap
	if (api.is_cursor_hovering_minimap ()):
		continue;
	
	# Get cursor position
	cursorX, cursorY = api.get_cursor_position ();
	# Get camera position
	cameraX, cameraY = api.get_camera_position ();
	# Get champion position
	championX, championY = api.get_champion_position ();
	
	# Fix perspective : Move the camera farther to the bottom of the screen
	# than to the top of the screen http://i.imgur.com/cwpZk3Z.png
	distance_mouse_cam_y = cameraY - cursorY;
	if (distance_mouse_cam_y > threshold):
		# If the cursor is in the bottom part of the screen (positive value) and superior to threshold value
		# Decrease slightly the cursorY position so it simulates a farther bottom scrolling
		cursorY -= (distance_mouse_cam_y * camera_scroll_speed_bottom);

	# Sum all the weights
	sumWeights = championWeight + cursorWeight;
	
	# Compute the weighted target position : Between the cursor and the champion
	# http://puu.sh/cAWUw/c703c6233c.png
	targetX = (championX * championWeight + cursorX * cursorWeight) / sumWeights;
	targetY = (championY * championWeight + cursorY * cursorWeight) / sumWeights;
	
	# Smoothing : We don't want the camera to jump to the target position too quickly
	# Increase the camera position value slowly if it's greater than "threshold" value
	if (abs(targetX - cameraX) > threshold):
		cameraX += ((targetX - cameraX) * 0.001) * cameraSpeed;

	if (abs(targetY - cameraY) > threshold):
		cameraY += ((targetY - cameraY) * 0.001) * cameraSpeed;

	# Update the new camera position
	api.set_camera_position (cameraX, cameraY);
