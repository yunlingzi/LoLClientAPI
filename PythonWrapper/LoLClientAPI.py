from ctypes import *
import win32api

class LoLClientAPI:

	# LoLClientAPI DLL handle
	hAPI = None;
	
	# Constants
	INVALID_OBJECT_HANDLE = -1;
	
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
	# ================================ Keyboard APIs =================================
	# =================================================================================

	
	# Check if the given key is pressed
	# key : ASCII code of the character pressed.
	#       For special characters, please refer to http://www.kbdedit.com/manual/low_level_vk_list.html
	# Return : true if pressed, false otherwise
	def is_key_pressed (self, key):
	
		# C API declaration :
		# bool is_key_pressed (
		#	unsigned char key
		# )
		
		return self.hAPI.is_key_pressed (c_ubyte(key));
	
	# Check if the given key is pressed
	# key : ASCII code of the character pressed.
	#       For special characters, please refer to http://www.kbdedit.com/manual/low_level_vk_list.html
	# Return : true if pressed, false otherwise
	def is_key_typed (self, key):
	
		# C API declaration :
		# bool is_key_typed (
		#	unsigned char key
		# )
		
		return self.hAPI.is_key_typed (c_ubyte(key));
	
	
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
	# Return : A string containing the teammate summoner name (16 bytes maximum)
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
		# 	__out__ int * x,
		# 	__out__ int * y
		# ) 
		
		x = c_int()
		y = c_int()
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
	# =================================== Chat APIs ===================================
	# =================================================================================

	# Get the next line of the chat received since the last time called.
	# Return : A line of chat, or NULL if no message has been posted since the last time called.
	def get_chat_message (self):
		
		# C API declaration :
		# char * get_chat_message (
		#	void
		# )
		
		self.hAPI.get_chat_message.restype = c_char_p;
		return self.hAPI.get_chat_message ();

	# Log a message to the HudChat
	# message : a string containing the message to send.
	def log_chat_message (self, message):
		
		# C API declaration :
		# void log_chat_message (
		#	char * message
		# )
		
		return self.hAPI.log_chat_message (c_char_p (message));

	
	# =================================================================================
	# ================================= Drawing APIs ==================================
	# =================================================================================

	# Create a new colored rectangle object displayed on the screen
	# {x, y} : position of the rectangle
	# {w, h} : width and height of the rectangle
	# {r, g, b} : color of the rectangle
	# Return : A unique handle of your rectangle object, or INVALID_OBJECT_HANDLE if an error occurred
	def create_rectangle (self, x, y, w, h, r, g, b):

		# C API declaration :
		# int create_rectangle (
		# 	int x, int y,
		# 	int w, int h,
		# 	byte r, byte g, byte b
		# )
		return self.hAPI.create_rectangle (
			c_int (x), c_int (y), 
			c_int (w), c_int (h), 
			c_ubyte (r), c_ubyte (g), c_ubyte (b)
		);
		
	# Create a new sprite object displayed on the screen
	# filePath : The path of the sprite you want to create. Supported formats are the following : 
	#            .bmp, .dds, .dib, .hdr, .jpg, .pfm, .png, .ppm, and .tga
	# {x, y} : position of the image
	# opacity : opacity of the image, value between 0.0 and 1.0 (optional, 1.0 by default)
	# Return : A unique handle of your sprite object, or INVALID_OBJECT_HANDLE if an error occurred
	def create_sprite (self, filePath, x, y, opacity=1.0):	

		# C API declaration :
		# int create_sprite (
		#   char *filePath,
		# 	int x, int y,
		#   float opacity
		# )
		return self.hAPI.create_sprite (
			c_char_p (filePath), c_int (x), c_int (y), c_float (opacity)
		);

	# Create a new colored text object displayed on the screen
	# {x, y} : position of the text
	# {r, g, b} : color of the text
	# opacity : opacity of the text, value between 0.0 and 1.0
	# string : String of the text
	# fontSize : the size of the font
	# fontFamily : The name of the family font. If NULL, "Arial" is used.
	# Return : A unique handle of your text object, or INVALID_OBJECT_HANDLE if an error occurred
	def create_text (self, string, x, y, r, g, b, opacity, fontSize, fontFamily):	

		# C API declaration :
		# int create_text (
		# 	char * string,
		# 	int x, int y,
		# 	byte r, byte g, byte b,
		#   float opacity,
		# 	int fontSize,
		# 	char * fontFamily
		# )
		return self.hAPI.create_text (
			c_char_p (string), 
			c_int (x), c_int (y), 
			c_ubyte (r), c_ubyte (g), c_ubyte (b),
			c_float (opacity),
			c_int (fontSize), 
			c_char_p (fontFamily), 
		);

	# Change the position of the object on the screen.
	# handleObject : The unique handle of the object to move
	# {x, y} : The new position on the screen of the object
	def move_object (self, handleObject, x, y):
	
		# C API declaration :
		# void move_object (
		#	int id,
		#   int x, int y
		# )
		return self.hAPI.move_object (c_int (handleObject), c_int (x), c_int (y));

	# Change the attributes of the rectangle object.
	# handleObject : The unique handle of the object to modify
	# {r, g, b} : The new color of the rectangle
	# {w, h} : Width and height of the rectangle
	def rect_object_set (self, handleObject, r, g, b, w, h):
	
		# C API declaration :
		# void rect_object_set (
		#	int id,
		#   byte r, byte g, byte b,
		#	int w, int h
		# )
		return self.hAPI.rect_object_set (
			c_int (handleObject), 
			c_ubyte (r), c_ubyte (g), c_ubyte (b), 
			c_int (w), c_int (h)
		);

	# Change the attributes of the text object.
	# handleObject : The unique handle of the object to modify
	# string : The new string of the text object
	# {r, g, b} : The new color of the text
	# opacity : opacity of the text, value between 0.0 and 1.0
	def text_object_set (self, handleObject, string, r, g, b, opacity):
	
		# C API declaration :
		# void text_object_set (
		#	int id,
		#   char * string,
		#   byte r, byte g, byte b,
		#   float opacity
		# )
		return self.hAPI.text_object_set (
			c_int (handleObject), 
			c_char_p (string), 
			c_ubyte (r), c_ubyte (g), c_ubyte (b), 
			c_float (opacity)
		);

	# Change the attributes of the sprite object.
	# handleObject : The unique handle of the object to modify
	# opacity : opacity of the text, value between 0.0 and 1.0
	def sprite_object_set (self, handleObject, opacity):
	
		# C API declaration :
		# void sprite_object_set (
		#	int id,
		#   float opacity
		# )
		return self.hAPI.sprite_object_set (
			c_int (handleObject),
			c_float (opacity)
		);

	# Show a hidden object. If it wasn't hidden, put it to the foreground.
	# handleObject : The unique handle of the object to delete
	def show_object (self, handleObject):
	
		# C API declaration :
		# void show_object (
		#	int id
		# )
		return self.hAPI.show_object (c_int (handleObject));
	
	# Show all hidden objects. Don't do anything with those already shown.
	def show_all_objects (self):
	
		# C API declaration :
		# void show_all_objects (
		#	void
		# )
		return self.hAPI.show_all_objects ();
	
	# Hide a visible object.
	# It isn't deleted, so you can use show_object if you want to make it appear again.
	# handleObject : The unique handle of the object to delete
	def hide_object (self, handleObject):
	
		# C API declaration :
		# void hide_object (
		#	int id
		# )
		return self.hAPI.hide_object (c_int (handleObject));
	
	# Hide all objects. Don't do anything with those already hidden.
	def hide_all_objects (self):
	
		# C API declaration :
		# void hide_all_objects (
		#	void
		# )
		return self.hAPI.hide_all_objects ();

	# Delete a specific object on the screen
	# handleObject : The unique handle of the object to delete
	def delete_object (self, handleObject):
	
		# C API declaration :
		# void delete_object (
		#	int id
		# )
		return self.hAPI.delete_object (c_int (handleObject));
	
	# Delete all the previously created objects on the screen
	def delete_all_objects (self):

		# C API declaration :
		# void delete_all_objects (
		#	void
		# )
		return self.hAPI.delete_all_objects ();
	
	# Return the object hovered by the mouse, or INVALID_OBJECT_HANDLE if no object is hovered
	def get_hovered_object (self):

		# C API declaration :
		# int get_hovered_object (
		#	void
		# )
		return self.hAPI.get_hovered_object ();
		
	
	
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
		
