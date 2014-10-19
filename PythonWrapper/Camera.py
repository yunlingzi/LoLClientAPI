import LoLClientAPI
import time

# Inject LoLClientAPI in LoLProcess
api = LoLClientAPI.LoLClientAPI ();

# Configurations
threshold   = 200.0
cameraSpeed = 2

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
	
	# Compute the target position : Between the cursor and the champion
	targetX = (cursorX + champX) / 2.0;
	targetY = (cursorY + champY) / 2.0;
	
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