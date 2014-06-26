#ifndef _TK_CVLIB_H_
#define _TK_CVLIB_H_
 
#pragma once
 
#include <opencv2/core/version.hpp>

 
#define CV_VERSION_ID CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)
 
#ifdef _DEBUG
#define cvLIB(name) "opencv_" name CV_VERSION_ID "d"
#else
#define cvLIB(name) "opencv_" name CV_VERSION_ID
#endif
 
 /*
  * Example: 
  * 	#pragma comment( lib, cvLIB("core") )
 */

#endif