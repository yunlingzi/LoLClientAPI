from ctypes import *
import win32api

class LoLClientAPI:

	# LoLClientAPI DLL handle
	hAPI = None;
	
	# =================================================================================
	# ================================== Camera APIs ==================================
	# =================================================================================

	# Get the current camera position
	# Return : {x, y} the camera position
	def get_camera_position (self):
	
		# C API declaration :
		# void get_camera_position (
		#	__out__ float * x,
		#	__out__ float * y
		# )
		
		x = c_float()
		y = c_float()
		self.hAPI.get_camera_position (byref(x), byref(y));
		return (x.value, y.value)


	# Set the camera position to x, y
	# x : New position X
	# y : New position Y
	def set_camera_position (self, x, y):
	
		# C API declaration :
		# void set_camera_position (
		# 	__in__ float x,
		# 	__in__ float y
		# )
		
		self.hAPI.set_camera_position (c_float(x), c_float(y));

	# Toggle the built-in client camera movements
	# For instance, camera movements when the cursor is on the border of the screen
	# enabled : boolean, If true, the camera client movements are enabled. False otherwise.
	def set_default_camera_enabled (self, enabled):
	
		# C API declaration :
		# void set_default_camera_enabled (
		# 	__in__ bool enabled
		# )
		self.hAPI.set_default_camera_enabled (c_bool(enabled));

	# Get the current camera angle in degrees
	# Return : {angleX, angleY} the camera angle
	def get_camera_angle (self):
	
		# C API declaration :
		# void get_camera_angle (
		#	__out__ float * angleX,
		#	__out__ float * angleY
		# )
		
		angleX = c_float()
		angleY = c_float()
		self.hAPI.get_camera_angle (byref(angleX), byref(angleY));
		return (angleX.value, angleY.value)


	# Set the camera position to angleX, angleY
	# angleX : New angle X
	# angleY : New angle Y
	def set_camera_angle (self, angleX, angleY):
	
		# C API declaration :
		# void set_camera_angle (
		# 	__in__ float angleX,
		# 	__in__ float angleY
		# )
		
		self.hAPI.set_camera_angle (c_float(angleX), c_float(angleY));

	# Get the current zoom value (1000.0 min, 2250.0 max)
	# Return : The zoom value
	def get_camera_zoom (self):
	
		# C API declaration :
		# float get_camera_zoom (
		#	void
		# )
		
		self.hAPI.get_camera_zoom.restype = c_float;
		return self.hAPI.get_camera_zoom ();

	# Set the current camera zoom (1000.0 min, 2250.0 max)
	# zoomValue : New zoom value
	def set_camera_zoom (self, zoomValue):

		# C API declaration :
		# void set_camera_zoom (
		# 	__in__ float zoomValue
		# )

		self.hAPI.set_camera_zoom (c_float(zoomValue));


	# =================================================================================
	# ================================== Cursor APIs ==================================
	# =================================================================================

	
	# Get the cursor in-game position
	# Return : {x, y} the cursor in game position
	def get_cursor_position (self):
	
		# C API declaration :
		# void get_cursor_position (
		#	__out__ float * x,
		#	__out__ float * y
		# )

		x = c_float()
		y = c_float()
		self.hAPI.get_cursor_position (byref(x), byref(y));
		return (x.value, y.value)
	
	
	# Check if the left mouse button is pressed
	# Return : true if pressed, false otherwise
	def is_left_mouse_button_pressed (self):
	
		# C API declaration :
		# bool is_left_mouse_button_pressed (
		#	void
		# )
		
		return self.hAPI.is_left_mouse_button_pressed ();
	
	
	# Check if the left mouse button has been clicked
	# Return : true if clicked, false otherwise
	def is_left_mouse_button_click (self):
	
		# C API declaration :
		# bool is_left_mouse_button_click (
		#	void
		# )
		
		return self.hAPI.is_left_mouse_button_click ();
	
	# Check if the right mouse button is pressed
	# Return : true if pressed, false otherwise
	def is_right_mouse_button_pressed (self):
	
		# C API declaration :
		# bool is_right_mouse_button_pressed (
		#	void
		# )
		
		return self.hAPI.is_right_mouse_button_pressed ();
	
	
	# Check if the right mouse button has been clicked
	# Return : true if clicked, false otherwise
	def is_right_mouse_button_click (self):
	
		# C API declaration :
		# bool is_right_mouse_button_click (
		#	void
		# )
		
		return self.hAPI.is_right_mouse_button_click ();
	
	
	# Check if the given key is pressed
	# key : ASCII code of the character pressed.
	#           For special characters, please refer to http://www.kbdedit.com/manual/low_level_vk_list.html
	# Return : true if pressed, false otherwise
	def is_key_pressed (self, key):
	
		# C API declaration :
		# bool is_key_pressed (
		#	int key
		# )
		
		return self.hAPI.is_key_pressed (c_int(key));
	
	
	# Get the cursor screen absolute position
	# Return : {x, y} the cursor screen position
	def get_cursor_screen_position (self):
	
		return win32api.GetCursorPos ()


	# Get the destination in-game position (right click)
	# Return : {x, y} the destination in game position
	def get_destination_position (self):
	
		# C API declaration :
		# void get_destination_position (
		#	__out__ float * x,
		#	__out__ float * y
		# )

		x = c_float()
		y = c_float()
		self.hAPI.get_destination_position (byref(x), byref(y));
		return (x.value, y.value)

		
	# =================================================================================
	# ================================ Champions APIs =================================
	# =================================================================================

	
	# Get the position of the current champion
	# Return : {x, y} The champion in game position
	def get_champion_position (self):
	
		# C API declaration :
		# void get_champion_position (
		#	__out__ float * x,
		#	__out__ float * y
		# )

		x = c_float()
		y = c_float()
		self.hAPI.get_champion_position (byref(x), byref(y));
		return (x.value, y.value)

	# Get the position of the current champion
	# Return : {currentHP, maximumHP}
	def get_champion_hp (self):
	
		# C API declaration :
		# void get_champion_hp (
		#	__out__ float * currentHP,
		#	__out__ float * maximumHP
		# )

		currentHP = c_float()
		maximumHP = c_float()
		self.hAPI.get_champion_hp (byref(currentHP), byref(maximumHP));
		return (currentHP.value, maximumHP.value)

	# Get the position of the current champion
	# Return : 0 if BLUE team, 1 if PURPLE team 
	def get_champion_team (self):
	
		# C API declaration :
		# int get_champion_team (
		#	void
		# )

		return self.hAPI.get_champion_team ();

	# ===== Teammates APIs =====
	
	# Retrieve the number of allies
	# Return : The number of allies in your team
	def get_teammates_count (self):
	
		# C API declaration :
		# int get_teammates_count (
		#	void
		# )

		return self.hAPI.get_teammates_count ();

	# Check if the target teammate ID is valid
	# teammateId : The target teammate ID
	# Return : true on success, false otherwise
	def check_teammate_id (self, teammateId):
	
		# C API declaration :
		# bool check_teammate_id (
		#	__in__  int teammateId
		# )

		return self.hAPI.check_teammate_id (c_int(teammateId));

	# Retrieve the teammate champion position
	# teammateId : The target teammate ID
	# Return : {x, y} The teammate in game position
	def get_teammate_position (self, teammateId):
	
		# C API declaration :
		# void get_teammate_position (
		# 	__in__  int teammateId,
		# 	__out__ float * x,
		# 	__out__ float * y
		# ) 
		
		x = c_float()
		y = c_float()
		self.hAPI.get_teammate_position (c_int(teammateId), byref(x), byref(y));
		return (x.value, y.value);

	# Retrieve teammate champion health points information
	# teammateId : The target teammate ID
	# Return : {currentHP, maximumHP} The current and the maximum HP of the teammate
	def get_teammate_hp (self, teammateId):
	
		# C API declaration :
		# void get_teammate_hp (
		# 	__in__  int teammateId,
		# 	__out__ float * currentHP,
		# 	__out__ float * maximumHP
		# ) 
		
		currentHP = c_float()
		maximumHP = c_float()
		self.hAPI.get_teammate_hp (c_int(teammateId), byref(currentHP), byref(maximumHP));
		return (currentHP.value, maximumHP.value);

	# Retrieve teammate champion health points information
	# teammateId : The target teammate ID
	# Return : summonerName A string containing the teammate summoner name (16 bytes maximum)
	def get_teammate_summoner_name (self, teammateId):
	
		# C API declaration :
		# char * get_teammate_summoner_name (
		# 	__in__  int teammateId
		# )
		
		self.hAPI.get_teammate_summoner_name.restype = c_char_p;
		return self.hAPI.get_teammate_summoner_name (c_int(teammateId));

		
	# =================================================================================
	# =================================== GUI APIs ====================================
	# =================================================================================

		
	# Retrieve the position of the minimap on the screen
	# Return : {x, y} The minimap position on the screen
	def get_minimap_screen_position (self):
	
		# C API declaration :
		# void get_minimap_screen_position (
		# 	__out__ float * x,
		# 	__out__ float * y
		# ) 
		
		x = c_float()
		y = c_float()
		self.hAPI.get_minimap_screen_position (byref(x), byref(y));
		return (x.value, y.value);
		
	# Retrieve the position of the minimap on the screen
	# Return : {x, y} The minimap position on the screen
	def is_cursor_hovering_minimap (self):
	
		# C API declaration :
		# void is_cursor_hovering_minimap (
		# 	void
		# )
		
		return self.hAPI.is_cursor_hovering_minimap ();
		
		
	# =================================================================================
	# ================================= Summoner APIs =================================
	# =================================================================================

	# Get the name of the current summoner playing
	# Return : The name of the current summoner as an ASCII string
	def get_current_summoner_name (self):
	
		# C API declaration :
		# char * get_current_summoner_name (
		#	void
		# )
		
		self.hAPI.get_current_summoner_name.restype = c_char_p;
		return self.hAPI.get_current_summoner_name ();

		
	# =================================================================================
	# ================================= Summoner APIs =================================
	# =================================================================================

	# Get the current game time (as seconds)
	# Return : float the current time as seconds
	def get_game_time (self):
		
		# C API declaration :
		# float get_game_time (
		#	void
		# )
		
		self.hAPI.get_game_time.restype = c_float;
		return self.hAPI.get_game_time ();
	
	
		
	# =================================================================================
	# ================================= Internal APIs =================================
	# =================================================================================
	
	# Eject the API from the LoL Process. You have to call this function before ejecting the DLL.
	def eject_api (self):
		
		# C API declaration :
		# void eject_api (
		#	void
		# )
		
		return self.hAPI.eject_api ();
	
	# Wait for the API to be in a ready state. (blocking)
	def wait_api (self):
		
		# C API declaration :
		# void wait_api (
		#	void
		# )
		
		self.hAPI.wait_api ();
	
	# Check if the API is in a ready state. (nonblocking)
	# Return : true if ready, false otherwise
	def check_api (self):
		
		# C API declaration :
		# bool check_api (
		#	void
		# )
		
		return self.hAPI.check_api ();
		
	# =================================================================================
	# ================================== Entry Point ==================================
	# =================================================================================

	def __init__ (self):
		# Load LoLClientAPI into LoL process
		try:
			self.hAPI = cdll.LoadLibrary ('./bin/LoLClientAPI.dll');
		except:
			print("Cannot find LoLClientAPI.dll.");
			exit(0);
		
