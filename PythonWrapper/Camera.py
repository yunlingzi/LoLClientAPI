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

	# Get cursor position
	cursorX, cursorY = api.get_cursor_position ();
	# Get camera position
	cameraX, cameraY = api.get_camera_position ();
	# Get champion position
	champX, champY   = api.get_champion_position ();
	
	# Fix perspective (http://i.imgur.com/cwpZk3Z.png)
	distance_mouse_cam_y = cameraY - cursorY;
	if (distance_mouse_cam_y > threshold):
		# If the cursor is in the bottom part of the screen and superior to threshold value
		# Decrease slightly the cursorY position
		cursorY -= (distance_mouse_cam_y * camera_scroll_speed_bottom);
	
	# Sum all the weights
	sumWeights = championWeight + cursorWeight;
	
	# Compute the weighted target position : Between the cursor and the champion
	targetX = (ChampionX * championWeight + CursorX * cursorWeight) / sumWeights;
	targetY = (ChampionY * championWeight + CursorY * cursorWeight) / sumWeights;
	
	# Smoothing : We don't want the camera to jump to the target position too quickly
	# Increase the camera position value slowly if it's greater than "threshold" value
	if (abs(targetX - cameraX) > threshold):
		cameraX += ((targetX - cameraX) * 0.001) * cameraSpeed;

	if (abs(targetY - cameraY) > threshold):
		cameraY += ((targetY - cameraY) * 0.001) * cameraSpeed;

	# Update the new camera position
	api.set_camera_position (cameraX, cameraY);

	# Sleep during 1 millisecond so the script doesn't take 100% CPU
	time.sleep(0.001);