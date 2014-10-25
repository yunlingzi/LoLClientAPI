#include "Position.h"
#include <stdlib.h>

Position *
Position_new (float x, float y, float z)
{
	Position *this;

	if ((this = Position_alloc()) == NULL)
		return NULL;

	Position_init(this, x, y, z);

	return this;
}

Position *
Position_alloc (void)
{
	return calloc(1, sizeof(Position));
}

void
Position_init (Position *this, float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void
Position_free (Position *Position)
{
	if (Position != NULL)
	{
		free (Position);
	}
}

bool
Position_in_map (Position *this)
{
	return (
		(this->x >= 0 && this->x <= 14000.0)
	&&  (this->y >= 0 && this->y <= 14200.0)
	);
}
