#include "Site.h"

Site::Site() {
	id = 0;
	quality = 0;
	agentsAssigned = 0;
	position = { 0, 0 };
}

Site::Site(int i, double qual , Position pos) {
	id = i;
	quality = qual;
	agentsAssigned = 0;
	position = pos;

}