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


	def __init__ (self):
		# Load LoLClientAPI into LoL process
		self.hAPI = cdll.LoadLibrary ('./LoLClientAPI.dll');
		
