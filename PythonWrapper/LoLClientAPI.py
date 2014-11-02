from ctypes import *
import win32api

class LoLClientAPI:

	# LoLClientAPI DLL handle
	hAPI = None;
	
	# =================================================================================
	# ================================== CAMERA APIs ==================================
	# =================================================================================

	# Get the current camera position
	# Returns : {x, y} the camera position
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

	# Toggle built-in client camera movements
	# For instance, camera movements when the cursor is on the border of the screen
	# enabled : boolean, If true, the camera client movements are enabled. False otherwise.
	def set_camera_client_enabled (self, enabled):
	
		# C API declaration :
		# void set_camera_client_enabled (
		# 	__in__ bool enabled
		# )
		
		self.hAPI.set_camera_client_enabled (c_bool(enabled));


	# =================================================================================
	# ================================== Cursor APIs ==================================
	# =================================================================================

	
	# Get the cursor in-game position
	# Returns : {x, y} the cursor in game position
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
		
		
	# Get the cursor screen absolute position
	# Returns : {x, y} the cursor screen position
	def get_cursor_screen_position (self):
		return win32api.GetCursorPos ()
		

	# Get the destination in-game position (right click)
	# Returns : {x, y} the destination in game position
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
	# Returns : {x, y} The champion in game position
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
	# Returns : {currentHP, maximumHP}
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
	# Returns : 0 if BLUE team, 1 if PURPLE team 
	def get_champion_team (self):
	
		# C API declaration :
		# int get_champion_team (
		#	void
		# )

		return self.hAPI.get_champion_team ();

	# Retrieve the number of allies
	# Returns : The number of allies in your team
	def get_teammates_count (self):
	
		# C API declaration :
		# int get_teammates_count (
		#	void
		# )

		return self.hAPI.get_teammates_count ();

	# Check if the target teammate ID is valid
	# teammateId : The target teammate ID
	# Returns : true on success, false otherwise
	def check_teammate_id (self, teammateId):
	
		# C API declaration :
		# bool check_teammate_id (
		#	__in__  int teammateId
		# )

		return self.hAPI.check_teammate_id (c_int(teammateId));

	# Retrieve the teammate champion position
	# teammateId : The target teammate ID
	# Returns : {x, y} The teammate in game position
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
	# Returns : {currentHP, maximumHP} The current and the maximum HP of the teammate
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
	# Returns : summonerName A string containing the teammate summoner name (16 bytes maximum)
	def get_teammate_summoner_name (self, teammateId):
	
		# C API declaration :
		# void get_teammate_summoner_name (
		# 	__in__  int teammateId,
		# 	__out__ char * summonerName
		# ) 
		self.hAPI.get_teammate_summoner_name.restype = c_char_p;
		self.hAPI.get_teammate_summoner_name (c_int(teammateId), byref(currentHP), byref(maximumHP));
		return (currentHP.value, maximumHP.value);

		
	# =================================================================================
	# ================================= Summoner APIs =================================
	# =================================================================================

		
	# Retrieve the position of the minimap on the screen
	# Returns : {x, y} The minimap position on the screen
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
	# Returns : {x, y} The minimap position on the screen
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
	# Returns : The name of the current summoner as an ASCII string
	def get_current_summoner_name (self):
	
		# C API declaration :
		# char * get_current_summoner_name (
		#	void
		# )
		self.hAPI.get_current_summoner_name.restype = c_char_p;
		return self.hAPI.get_current_summoner_name ();

	def __init__ (self):
		# Load LoLClientAPI into LoL process
		try:
			self.hAPI = cdll.LoadLibrary ('./LoLClientAPI.dll');
		except:
			print("Cannot find LoLClientAPI.dll.");
			exit(0);
		
