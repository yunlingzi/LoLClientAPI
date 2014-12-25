import LoLClientAPI
from datetime import datetime
import math
import time

class CameraController:

	def __init__ (self, api):
		self.api = api;

	# Translate the camera to a given position and angle, during a given time
	# cameraDestX : The camera destination X
	# cameraDestY : The camera destination Y
	# angleX      : The camera angle X
	# angleY      : The camera angle Y
	# speed       : Time to travel to destination in milliseconds
	def translate (self, cameraDestX, cameraDestY, angleDestX, angleDestY, speed) :
		# Get the current camera position
		cameraX, cameraY = self.api.get_camera_position ();
		angleX, angleY   = self.api.get_camera_angle ();
		
		# Don't do anything if nothing is requested
		if (cameraX == cameraDestX 
		and cameraY == cameraDestY
		and angleX  == angleDestX
		and angleY  == angleDestY):
			return;
		
		offsetCamX = (cameraDestX - cameraX) / speed;
		offsetCamY = (cameraDestY - cameraY) / speed;
		offsetAngleX = (angleDestX - angleX) / speed;
		offsetAngleY = (angleDestY - angleY) / speed;
		
		curCamSignX = initialCamSignX = math.copysign (1, offsetCamX);
		curCamSignY = initialCamSignY = math.copysign (1, offsetCamY);
		curAngleSignX = initialAngleSignX = math.copysign (1, offsetAngleX);
		curAngleSignY = initialAngleSignY = math.copysign (1, offsetAngleY);
		
		timeNow = datetime.now ();
		
		while (curCamSignX == initialCamSignX 
		  and   curCamSignY == initialCamSignY 
		  and   curAngleSignX == initialAngleSignX 
		  and   curAngleSignY == initialAngleSignY):
			# Update the camera position and angle
			self.api.set_camera_position (cameraX, cameraY);
			self.api.set_camera_angle (angleX, angleY);
			
			cameraX += offsetCamX;
			cameraY += offsetCamY;
			angleX  += offsetAngleX;
			angleY  += offsetAngleY;
			
			# Check if we've reached the target
			curCamSignX   = math.copysign (1, cameraDestX - cameraX);
			curCamSignY   = math.copysign (1, cameraDestY - cameraY);
			curAngleSignX = math.copysign (1, angleDestX - angleX);
			curAngleSignY = math.copysign (1, angleDestY - angleY);
			
			time.sleep (0.001);


