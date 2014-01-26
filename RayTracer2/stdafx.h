// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstdlib>

#include "vect.h"
#include "Camera.h"
#include "Command.h"
#include "SettingsFile.h"
#include "Color.h"
#include "Sphere.h"
#include "Plane.h"
#include "Source.h"
#include "Light.h"


#include "glut.h"

struct RGBColor {
	double r;
	double g;
	double b;
};

// TODO: reference additional headers your program requires here
