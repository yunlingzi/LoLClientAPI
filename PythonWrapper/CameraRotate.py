import LoLClientAPI
import CameraController

class CameraRotate:

	def __init__ (self):
		# ===== Start of the program ======
		# Inject LoLClientAPI in LoLProcess
		self.api = LoLClientAPI.LoLClientAPI ();

		# Start the main loop
		self.run ();

	def run (self):
	
		cameraController = CameraController.CameraController (self.api);
		
		# Center the camera on the champion
		champX, champY = self.api.get_champion_position ();
		self.api.set_camera_position (champX, champY);
		
		# Rotate around the champion
		while True:
			champX, champY = self.api.get_champion_position ();
			angleX, angleY = self.api.get_camera_angle ();
			cameraController.translate (champX, champY, angleX + 1, angleY, 10);

	
if __name__ == '__main__':
	CameraRotate ();

	