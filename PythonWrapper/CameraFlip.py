import LoLClientAPI

api = LoLClientAPI.LoLClientAPI ();

# Originally, the camera angle is  {x = 180.0, y = 56.0}
x, y = api.get_camera_angle ();

if x == 180:
	# Flip camera
	api.set_camera_angle (0, 56);
else:
	# Flip back to the original angle
	api.set_camera_angle (180, 56);