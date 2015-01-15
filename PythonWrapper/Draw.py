from LoLClientAPI import LoLClientAPI
import time

api = LoLClientAPI ();

# Just in case, clean the objects
api.delete_all_objects ();

# Create 3 objects
rect1 = api.create_rectangle (30, 270, 300, 300, 0xFF, 0x00, 0x00);
text = api.create_text ("I <3 LoLClientAPI", 50, 50, 0xFF, 0x00, 0x00, 1.0, 20, "Verdana");
img = api.create_sprite ("C:/sprite.png", 30, 120, 0.5);

# Detect the hovered object, change its attribute
while True:
	hovered = api.get_hovered_object ();
	if (hovered == rect1):
		api.rect_object_set (rect1, 0, 255, 0, 300, 300);
	else:
		api.rect_object_set (rect1, 255, 0, 0, 300, 300);
		
	if (hovered == img):
		api.sprite_object_set (img, 1.0);
	else:
		api.sprite_object_set (img, 0.5);
		
	time.sleep (0.01);