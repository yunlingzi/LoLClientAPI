from ctypes import *


class LoLClientAPI:

	# LoLClientAPI DLL handle
	hAPI = None;
	
	# =================================================================================
	# ================================== CAMERA APIs ==================================
	# =================================================================================

	# Get the current camera position
	# Returns : {x, y}
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


	# =================================================================================
	# ================================== Cursor APIs ==================================
	# =================================================================================

	
	# Get the cursor camera position
	# Returns : {x, y}
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

	# Get the destination position (right click)
	# Returns : {x, y}
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
	# Returns : {x, y}
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

		return self.hAPI.get_current_summoner_name ();

	def __init__ (self):
		# Load LoLClientAPI into LoL process
		try:
			self.hAPI = cdll.LoadLibrary ('./LoLClientAPI.dll');
		except:
			print("Cannot find LoLClientAPI.dll.");
			exit(0);
		
