from LoLClientAPI import LoLClientAPI
import time


api = LoLClientAPI ();


x, y = api.get_minimap_screen_position ();

print "%d / %d" % (x, y);