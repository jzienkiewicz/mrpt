/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2015, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

/** \page changelog Change Log
 *

<p> <b>Note:</b> <i>If you are displaying a local version of this page and you have not built the whole HTML documentation, the links above will be broken. Either build the documentation invoking <code>make documentation_html</code> or [browse it on-line](http://www.mrpt.org/).</i></p>

<a name="1.3.2">
  <h2>Version 1.3.2: (Under development) </h2></a>
	- Changes in libraries:
		- \ref mrpt_base_grp
			- mrpt::math::KDTreeCapable::TKDTreeSearchParams: Removed parameter nChecks, which was ignored by nanoflann anyway.
 

<hr>
<a name="1.3.1">
  <h2>Version 1.3.1: Released 18-JUL-2015 </h2></a>
	- Changes in apps:
		- [navlog-viewer](http://www.mrpt.org/list-of-mrpt-apps/application-navlog-viewer/): Now shows more information on navigation logs.
		- New app [icp-slam-live](http://www.mrpt.org/list-of-mrpt-apps/application-icp-slam-live/): Real-time ICP-SLAM with a LIDAR sensor.
	- Changes in libraries:
		- \ref mrpt_base_grp
			- New helper templates: mrpt::utils::int_select_by_bytecount<>, mrpt::utils::uint_select_by_bytecount<>
			- New methods to evaluate SO(2), SO(3), SE(2) and SE(3) averages and weighted averages. See: 
				- Header <mrpt/poses/SO_SE_average.h>
				- mrpt::poses::SO_average<2>, mrpt::poses::SO_average<3>
				- mrpt::poses::SE_average<2>, mrpt::poses::SE_average<3>
		- \ref mrpt_hwdrivers_grp
			- New sensors supported:
				- mrpt::hwdrivers::CIMUIntersense
				- mrpt::hwdrivers::CSkeletonTracker
			- New parameter mrpt::hwdrivers::CHokuyoURG::m_disable_firmware_timestamp to override faulty Hokuyo timestamps with PC time.
			- mrpt::hwdrivers::CRoboPeakLidar::turnOn() and turnOff() now really implement turning on/off the RPLidar motor.
		- \ref mrpt_maps_grp
			- New method mrpt::maps::COccupancyGridMap2D::getAsPointCloud() 
		- \ref mrpt_nav_grp
			- Removed old base class CPathPlanningMethod
			- CPathPlanningCircularRobot => mrpt::nav::PlannerSimple2D: Class renamed (and better described) for consistency with other planners
			- mrpt::nav::CReactiveNavigationSystem:
				- Documentation has been added about all existing parameters, and template config files provided as starting points.
				- The loadConfigFile() method with 2 config files has been deprecated favoring the newer, simpler single config file. 
				- The "ROBOT_NAME" parameter is no longer employed. A minor side effect (probably affecting no one) is that PTG cache files are no longer named differently for different robots.
			- mrpt::nav::CParameterizedTrajectoryGenerator: New methods to save and load trajectories to binary streams. Used to debug in navlog-viewer.
		- \ref mrpt_obs_grp
			- mrpt::obs::CObservation3DRangeScan now supports pixel labels (semantic mapping, etc.)
			- New class mrpt::obs::CObservationSkeleton to hold body tracking information (by Francisco Angel Moreno)
			- mrpt::obs::CObservationIMU has new data fields and fields are better documented to reflect whether they refer to local/global coordinate frames
		- \ref mrpt_vision_grp
			- mrpt::vision::CImageGrabber_dc1394: Changed default Bayer filter from NEAREST to HQLINEAR
	- BUG FIXES:
			- Fix ocasional (false) failure of RANSAC unit tests due to their non-deterministic nature.
			- Fix build error with MSVC 2010 in mrpt-hmtslam (Closes #127).
			- Fixed potential wrong bounding box results in mrpt::maps::CPointsMap::boundingBox() when SSE2 optimization is enabled.
			- mrpt::obs::CObservation6DFeatures: Fixed random crashes related to non-aligned memory in 32bit builds (Fixes #141)
			- Fix Debian bug [#786349](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=786349) on Eigen2 support.
			- mrpt::hwdrivers::CIMUXSens_MT4: Fix crash in destructor of objects not attached to a physical device.
			- Fix wrong quaternion cross product when target variable is one of the operands. Also affected the += operator of mrpt::poses::CPose3DQuat (Fixes #148)
			- mrpt::hwdrivers::CKinect with libfreenect driver: Fix potential memory corruption.
			- Fix a bug in mrpt::tfest::se3_l2_robust() that led to it returning without trying to find a good consensus solution. It affected the demo app kinect-3d-slam (Fixes #156)
			- Fix wrong feature points in CFeatureExtraction::extractFeaturesKLT()  (Fixes #138)

<hr>
<a name="1.3.0">
  <h2>Version 1.3.0: Released 12-JAN-2015 </h2></a>
	- <b>Most important changes:</b>
		- Classes in libraries \ref mrpt_obs_grp and \ref mrpt_maps_grp now belong to new namespaces (mrpt::obs, mrpt::maps) instead of the old mrpt::slam
		- No more `using namespace`s polute MRPT headers. <b>Errors in user projects</b> missing `using namespace XXX` that might be formerly masked will now reveal. <b>This is a good thing</b>, though admitedly annoying...
		- New library \ref mrpt_nav_grp, subsumming the old \ref mrpt_reactivenav_grp.
		- New library \ref mrpt_tfest_grp, a refactor of the old \ref mrpt_scanmatching_grp.
		- <b>Backwards compatible headers</b> have been provided to ease the transition of user code for all those library changes. Warning messages will be shown recommending deprecated replacements.
	- <b>Detailed list of changes:</b>
		- Lib changes:
			- Clean up of the bad practice of `using namespace` in public scopes of headers. May lead to user code failing for missing `using namespace`s which were previously masked.
			- Namespace "slam" deprecated in libraries mrpt-obs and mrpt-maps (used for historical reasons):
				- New namespaces  \ref mrpt_obs_grp and \ref mrpt_maps_grp.
				- #include files moved from old paths <mrpt/slam/...> => <mrpt/{obs,maps}/...>
				- Backward compatible headers added in <mrpt/slam/...> until mrpt 2.0.0
			- New library \ref mrpt_nav_grp, subsumming the old mrpt-reactivenav (\ref mrpt_reactivenav_grp).
			- \ref mrpt_reactivenav_grp is now a meta-library, depending on \ref mrpt_nav_grp.
			- \ref mrpt_tfest_grp : Old library mrpt-scanmatching (\ref mrpt_scanmatching_grp) has been refactored, its API clean-up, and renamed \ref mrpt_tfest_grp
			- \ref mrpt_scanmatching_grp is now a meta-library, depending on \ref mrpt_tfest_grp. 
			- These classes have been moved between libs for a more sensible organization:
				- mrpt::slam::CDetectorDoorCrossing ==> mrpt::detectors::CDetectorDoorCrossing
				- mrpt::slam::CPathPlanningMethod & CPathPlanningCircularRobot: \ref mrpt_slam_grp ==> \ref mrpt_nav_grp
		- Build System / General changes:
			- Many optimizations in function arguments (value vs ref). Forces ABI incompatibility with previous versions, hence the change to a new minor version number.
			- Updated embedded version of Eigen to 3.2.3
			- Kinect: Dropped support for the CL NUI API, which seems discontinued. Alternatives in use are libfreenect and OpenNI2.
			- libfreenect is now detected in the system and used instead of compiling the embedded copy of it.
			- Embedded copy of libfreenect has been updated to (23/oct/2014). It now supports "Kinect for Windows".
			- More selective linking of .so files to avoid useless dependencies (Fixes #52).
			- (Windows only) MRPT can now be safely built with libusb support (Freenect, Kinect,...) and it will run on systems without libusb installed, by means of /DELAYLOAD linking flags.
			- More unit tests.
		- Changes in classes:
			- [mrpt-base]
				- New function mrpt::math::angDistance()
			- [mrpt-hwdrivers]
				- mrpt::hwdrivers::CIMUXSens_MT4: (by Joe Burmeister for Suave Aerial Software)
					- Upgrade to latest XSens SDK 4.2.1. Requires libudev-dev in Linux
					- Add GPS observations to CIMUXSens_MT4 for Xsens devices like GTi-G-700 which have GPS
				- mrpt::hwdrivers::CImageGrabber_dc1394: Length of ring buffer is now configurable via TCaptureOptions_dc1394::ring_buffer_size
			- [mrpt-maps]
				- Important refactor of internal code related to mrpt::maps::CMultiMetricMap: 
					- All maps (derived from mrpt::maps::CMetricMap) now have a more uniform interface. 
					- Each map now has a `MapDefinition` structure with all its parameters. See docs for mrpt::maps::TMetricMapInitializer
					- Introduced mrpt::maps::TMapGenericParams to hold parameters shared in all maps.
			- [mrpt-obs]
				- CObservation::getDescriptionAsText(): New virtual method to obstain a textual description of observations. Refactoring of messy code previously in the RawLogViewer app.
			- [mrpt-vision]
				- mrpt::vision::CFeatureExtraction: Removed (unused) optional ROI parameter in detectors.
		- BUG FIXES:
			- mrpt::poses::CRobot2DPoseEstimator could estimate wrong angular velocities for orientations near +-180deg.
			- mrpt::system::CDirectoryExplorer::sortByName() didn't sort in descending order
			- Fixed crashes from MATLAB .mex files: mrpt::system::registerFatalExceptionHandlers() has no longer effect, and will be removed in future releases. (Thanks to Jesús Briales García for all the testing!)
			- Fixed potential crash for Eigen unaligned memory access in 32bit builds in mrpt::slam::CGridMapAligner and other places ([Closes #94](https://github.com/MRPT/mrpt/issues/94))

<hr>
<a name="1.2.2">
  <h2>Version 1.2.2: Released 12-SEP-2014  </h2></a>
	- Changes in apps:
		- <a href="http://www.mrpt.org/list-of-mrpt-apps/application-sceneviewer3d/" >SceneViewer3D</a>:
			- New menu "File" -> "Import" -> "3D model" which supports many standard formats (via mrpt::opengl::CAssimpModel)
	- New classes:
		- [mrpt-hwdrivers]
			- mrpt::hwdrivers::CRoboPeakLidar to interface Robo Peak LIDAR scanners.
		- [mrpt-opengl]
			- mrpt::opengl::CAssimpModel for rendering complex 3D models (many supported formats) in OpenGL scenes.
	- Changes in classes:
		- Consistency in all "laser scan" classes: angular increments between rays are now FOV/(N-1) instead of FOV/N.
		- [mrpt-base]
			- New method mrpt::utils::CImage::loadTGA()
			- *IMPORTANT*: Changed behavior of CSerializable/CObject macros (see bugfix below), introducing the new macros DEFINE_SERIALIZABLE_POST_*. 
			   May require changes in user code if serializable classes are defined:
				- Previous version:
					\code
						DEFINE_SERIALIZABLE_PRE_*(...)
						class XXX {
							DEFINE_SERIALIZABLE(XXX)
						};
					\endcode
				- Must be changed in this version to:
					\code
						DEFINE_SERIALIZABLE_PRE_*(...)
						class XXX {
							DEFINE_SERIALIZABLE(XXX)
						};
						DEFINE_SERIALIZABLE_POST_*(...)
					\endcode
		- [mrpt-hwdrivers]
			- Bumblebee2 Linux support in mrpt::hwdrivers::CImageGrabber_FlyCapture2 via Triclops (by Jesus Briales)
		- [mrpt-maps]
			- New method mrpt::maps::COccupancyGridMap2D::getRawMap()
			- New method mrpt::maps::CColouredPointsMap::getPCLPointCloudXYZRGB()
		- [mrpt-opengl]
			- mrpt::opengl::CMyGLCanvasBase (affects all 3D rendering classes): better handling of internal timers for smoother updates while rendering in multithreading apps.
		- [mrpt-srba]
			- New method to recover the global coordinates graph-slam problem for a RBA map: mrpt::srba::RbaEngine::get_global_graphslam_problem() (see example [MRPT]\samples\srba-examples\srba-tutorials\tutorial-srba-how-to-recover-global-map.cpp)
	- BUG FIXES:
		- mrpt::utils::CImage constructor from a matrix crashed.
		- Unit tests: Named semaphores are not tested anymore if it's detected that the kernel version doesn't support them (Fix Debian 758725).
		- mrpt::synch::CSemaphore [Linux]: didn't call sem_unlink().
		- mrpt::gui::CDisplayWindow3D didn't implement get/set FOV.
		- Valgrind: Fixed potential unaligned memory access warning in point clouds.
		- Fix build error with AppleClang 5.1 (Closes #71).
		- mrpt::utils::CClientTCPSocket: Use a connection success check that works on all platforms
		- Important bug fixed regarding a missing dynamic_cast<> in smart pointers casting. See above possible implications in user code.
 properly (Patch by Joe Burmeister).

<hr>
<a name="1.2.1">
  <h2>Version 1.2.1: Released 10-JUL-2014 </h2></a>
	- Changes in classes:
		- [mrpt-base]
			- All points and poses now have a method setToNaN(), e.g. mrpt::poses::CPose3D::setToNaN()
		- [mrpt-hwdrivers]
			- mrpt::hwdrivers::COpenNI2Sensor now has better support for opening several RGBD cameras (by Kenzaburo Miyawaki & Eduardo Fernandez)
	- Build system:
		- Fix compilation of SRBA with DEBUG_GARBAGE_FILL_ALL_NUMS=1
		- Fix de-serialization error in mrpt::reactivenav::CLogFileRecord (and new unit tests added to avoid regressions).
		- Several Debian bugs closed (see packaging/debian/changelog), including build errors in uncommon platforms (MIPS, kFreeBSD, etc.)

<hr>
<a name="1.2.0">
  <h2>Version 1.2.0: Released 25-JUN-2014  </h2></a>
  	- <b>Most important changes:</b>
		- Public header files (.h) have undergone a serious refactoring to minimize unnecesary dependencies and reduce compile time and memory as much as possible.
		  As a side effect, user code might need to add new #include<> lines. This change justifies the new minor version series 1.2.X.
		- MRPT now cleanly builds in clang and OSX.
		- Support for new camera drivers (OpenNI2, DUO3D).
		- Many bug fixes.
	- <b>Detailed list of changes:</b>
		- Changes in apps:
			- [rawlog-edit](http://www.mrpt.org/Application%3Arawlog-edit):
				- New operations: --export-odometry-txt, --recalc-odometry
				- New flag: --rectify-centers-coincide
		- New examples:
			- kitti_dataset2rawlog
		- New classes:
			- [mrpt-base]
				- mrpt::math::ContainerType<CONTAINER>::element_t to allow handling either Eigen or STL containers seamlessly.
				- mrpt::utils::CConfigFilePrefixer
			- [mrpt-hwdrivers]
				- mrpt::hwdrivers::COpenNI2Sensor: Interface to OpenNI2 cameras, capable of reading from an array of OpenNI2 RGBD cameras (By Eduardo Fernandez)
				- mrpt::hwdrivers::CDUO3DCamera: Interface to DUO3D cameras (By Francisco Angel Moreno)
				- mrpt::hwdrivers::CGPS_NTRIP: A combination of GPS receiver + NTRIP receiver capable of submitting GGA frames to enable RTCM 3.0
			- [mrpt-obs]
				- mrpt::obs::CObservation6DFeatures
		- Changes in classes:
			- [mrpt-base]
				- Robust kernel templates moved from mrpt::vision to mrpt::math. See mrpt::math::RobustKernel<>. Added unit tests for robust kernels.
				- mrpt::poses::CPose3D has new SE(3) methods: mrpt::poses::CPose3D::jacob_dexpeD_de(), mrpt::poses::CPose3D::jacob_dAexpeD_de()
				- More efficient mrpt::utils::OctetVectorToObject() (avoid memory copy).
				- Fixed const-correctness of mrpt::utils::CImage::forceLoad() and mrpt::utils::CImage::unload()
			- [mrpt-hwdrivers]
				- mrpt::hwdrivers::CCameraSensor: Added a hook for user code to run before saving external image files: mrpt::hwdrivers::CCameraSensor::addPreSaveHook()
				- mrpt::hwdrivers::CNationalInstrumentsDAQ now supports analog and digital outputs.
				- New method mrpt::hwdrivers::CNTRIPClient::sendBackToServer()
			- [mrpt-srba]
				- Now also implements SE(3) relative graph-slam.
			- [mrpt-vision]
				- mrpt::vision::checkerBoardStereoCalibration: More robust handling of stereo calibration patterns. OpenCV sometimes detects corners in the wrong order between (left/right) images, so we detect the situation and fix it.
				- mrpt::vision::findMultipleChessboardsCorners():
					- Now enforces a consistent counterclockwise XYZ coordinate frame at each detected chessboard.
					- Much more robust in distingishing quads of different sizes.
		- Build system / public API:
			- Fixes to build in OS X - [Patch](https://gist.github.com/randvoorhies/9283072) by Randolph Voorhies.
			- Removed most "using namespace" from public headers, as good practice.
			- Refactoring of MRPT headers.
				- <mrpt/utils/stl_extensions.h> has been split into:
					- <mrpt/utils/stl_serialization.h>
					- <mrpt/utils/circular_buffer.h>
					- <mrpt/utils/list_searchable.h>
					- <mrpt/utils/bimap.h>
					- <mrpt/utils/map_as_vector.h>
					- <mrpt/utils/traits_map.h>
					- <mrpt/utils/stl_serialization.h>
					- <mrpt/utils/printf_vector.h>
					- <mrpt/utils/stl_containers_utils.h>
					- <mrpt/utils/ci_less.h>
			- Deleted methods and functions:
				- mrpt::system::breakpoint()
				- mrpt::vector_float is now mrpt::math::CVectorFloat, mrpt::vector_double is mrpt::math::CVectorDouble, for name consistency. Also, using Eigen::VectorXf is preferred for new code.
				- mrpt::CImage::rectifyImage() with parameters as separate vectors.
				- mrpt::maps::CPointsMap::getPoint() with mrpt::poses::CPoint3D arguments.
				- mrpt::vision::correctDistortion() -> use CImage method instead
				- All previous deprecated functions.
			- Embedded Eigen updated to version 3.2.1 [(commit)](https://github.com/MRPT/mrpt/commit/47913da94a27e98a9115f85b2a530b6c14a10b8f) [(commit)](https://github.com/MRPT/mrpt/commit/33258761d3b75bf133d38aecb257c64e4d76b21e)
  		- BUG FIXES:
			- RawlogViewer app: Fixed abort while converting SF->obs.only datasets when there is no odometry.
			- mrpt::obs::CSensoryFrame: The cached point map is now invalidated with any change to the list of observations so it's rebuild upon next call.
			- New implementation of mrpt::synch::CSemaphore avoids crashes in OS X - by Randolph Voorhies.
			- mrpt::opengl::CArrow was always drawn of normalized length.
			- FlyCapture2 monocular & stereo cameras could return an incorrect timestamp (only in Linux?).
			- mrpt::system::createDirectory() returned false (error) when the directory already existed.
			- mrpt::vision::CStereoRectifyMap::rectify() didn't update the left & right camera poses inside mrpt::obs::CObservationStereoImages objects while rectifying.
			- RawLogViewer: Operation "convert to SF format" didn't take into account odometry observations.
			- Fix build errors with GCC 4.9
			- Fix crash of mrpt::hwdrivers::CIMUXSens_MT4's destructor when it fails to scan and open a device.
			- Fix potential crash in mrpt::slam::data_association_full_covariance with JCBB when no individually compatible matching exists [(commit)](https://github.com/MRPT/mrpt/commit/482472ebd80a3484dce63d294b1ac4e8f001e1eb)

<hr>
 <a name="1.1.0">
  <h2>Version 1.1.0: Released 22-FEB-2014  </h2></a>
	- New apps:
		- [DifOdometry-Camera](http://www.mrpt.org/list-of-mrpt-apps/application-difodometry-camera).  (By Mariano Jaimez Tarifa)
		- [DifOdometry-Datasets](http://www.mrpt.org/list-of-mrpt-apps/application-difodometry-datasets). (By Mariano Jaimez Tarifa)
	- New classes:
		- [mrpt-base]
			- mrpt::synch::CPipe: OS-independent pipe support.
		- [mrpt-hwdrivers]
			- mrpt::hwdrivers::CIMUXSens_MT4 : Support for 4th generation xSens MT IMU devices.
			- mrpt::hwdrivers::CNationalInstrumentsDAQ: Support for acquisition boards compatible with National Instruments DAQmx Base - [(commit)](https://github.com/MRPT/mrpt/commit/a82a7e37997cfb77e7ee9e903bdb2a55e3040b35).
			- mrpt::hwdrivers::CImageGrabber_FlyCapture2: Support for Point Grey Research's cameras via the FlyCapture2 libray - [(commits)](https://github.com/MRPT/mrpt/pull/5/commits).
		- [mrpt-maps]
			- There are now two versions of octomaps (by Mariano Jaimez Tarifa/Jose Luis Blanco) - [(commit)](http://code.google.com/p/mrpt/source/detail?r=3443)
				- mrpt::maps::COctoMap (only occupancy)
				- mrpt::maps::CColouredOctoMap (occupancy + RGB color)
		- [mrpt-obs]
			- mrpt::obs::CObservationRawDAQ, a placeholder for raw and generic measurements from data acquisition devices. - [(commit)](http://code.google.com/p/mrpt/source/detail?r=3459)
		- [mrpt-opengl]
			- mrpt::opengl::CMeshFast, an open gl object that draws a "mesh" as a structured point cloud which is faster to render (by Mariano Jaimez Tarifa). -[(commit)](https://github.com/MRPT/mrpt/commit/9306bb4a585387d4c85b3f6e41dd2cbe5a354e80)
			- mrpt::opengl::CVectorField2D, an opengl object that shows a 2D Vector Field (by Mariano Jaimez Tarifa). - [(commit)](http://code.google.com/p/mrpt/source/detail?r=3461)
		- [mrpt-reactivenav]
			- mrpt::reactivenav::CAbstractPTGBasedReactive, as part of a large code refactoring of these classes: [(commit)](https://github.com/MRPT/mrpt/pull/4)
				- mrpt::reactivenav::CReactiveNavigationSystem
				- mrpt::reactivenav::CReactiveNavigationSystem3D
		- [mrpt-vision]
			- mrpt::vision::CDifodo, a class which implements visual odometry based on depth images and the "range flow constraint equation". (by Mariano Jaimez Tarifa) - [(commit)](https://github.com/MRPT/mrpt/commit/e6ab5595f70cb889d07658c0b540c27e495a1cfb)
	- Changes in classes:
		- Clean up and slight optimization of metric map matching API: - [(commit)](http://code.google.com/p/mrpt/source/detail?r=3446)
			- <b>Methods marked as deprecated: </b>
				- mrpt::maps::CMetricMap::computeMatchingWith2D() --> mrpt::maps::CMetricMap::determineMatching2D()
				- mrpt::maps::CMetricMap::computeMatchingWith3D() --> mrpt::maps::CMetricMap::determineMatching3D()
			- New structures:
				- mrpt::slam::TMatchingParams
				- mrpt::slam::TMatchingExtraResults
		- mrpt::maps::CPointsMap::TInsertionOptions now have methods to save/load from binary streams, making more maintainable the serialization of point maps - [(commit)](https://github.com/MRPT/mrpt/commit/544d439c3462228b07344142de68e5bc10c1a2e3)
		- New options in point maps: mrpt::maps::CPointsMap::TInsertionOptions::insertInvalidPoints - [(commit)](https://github.com/MRPT/mrpt/pull/8)
		- mrpt::obs::CObservationIMU now includes data fields for 3D magnetometers and altimeters. - [(commit)](http://code.google.com/p/mrpt/source/detail?r=3451)
		- Method renamed mrpt::utils::CEnhancedMetaFile::selectVectorTextFont() to avoid shadowing mrpt::utils::CCanvas::selectTextFont()
		- mrpt::reactivenav::CParameterizedTrajectoryGenerator: New methods:
			- mrpt::reactivenav::CParameterizedTrajectoryGenerator::inverseMap_WS2TP() for inverse look-up of WS to TP space - [(commit)](https://github.com/MRPT/mrpt/commit/4d04ef50e3dea581bed6287d4ea6593034c47da3)
			- mrpt::reactivenav::CParameterizedTrajectoryGenerator::renderPathAsSimpleLine() - [(commit)](https://github.com/MRPT/mrpt/commit/a224fc2489ad00b3ab116c84e8d4a48532a005df)
		- Changed the signature of mrpt::reactivenav::build_PTG_collision_grids() to become more generic for 2D & 2.5D PTGs - [(commit)](https://github.com/MRPT/mrpt/commit/7bd68e49a4ba3bf08f194678787816c65de1d685)
	- Deleted classes:
		- mrpt::utils::CEvent, which was actually unimplemented (!)
		- mrpt::hwdrivers::CInterfaceNI845x has been deleted. It didn't offer features enough to justify a class.
	- New examples:
		- [MRPT]/samples/threadsPipe
		- [MRPT]/samples/NIDAQ_test
		- [MRPT]/openNI2_RGBD_demo (by Mariano Jaimez Tarifa)
		- [MRPT]/openNI2_proximity_demo (by Mariano Jaimez Tarifa)
	- Build system:
		- Fixed compilation with clang.
		- Fixed building against OpenCV 3.0.0 (GIT head)
		- Updated to the latest nanoflann 1.1.7.
		- Updated to Eigen 3.2.0 - [(commit)](http://code.google.com/p/mrpt/source/detail?r=3455)
		- Binary packages for Windows now include .pdb files to help debugging with Visual Studio.
	- BUG FIXES:
		- Fixed potential infinity loop in mrpt::math::make_vector<1,T>()
		- Fixed build error with GCC when experimental parallelization is enabled. [(commit)](http://code.google.com/p/mrpt/source/detail?r=3441)
		- mrpt::reactivenav::CReactiveNavigationSystem complained about missing config variables ROBOTMODEL_TAU & ROBOTMODEL_DELAY, which were removed in MRPT 1.0.2 - [(commit)](http://code.google.com/p/mrpt/source/detail?r=3452)
		- Fixed potential mem alignment errors (Eigen's UnalignedArrayAssert) in SRBA for 32bit builds. [(commit)](http://code.google.com/p/mrpt/source/detail?r=3457)
		- mrpt::topography::geodeticToENU_WGS84() and related functions used a local +Z axis aligned to the line towards the Earth center; now the Z axis points normally to the ellipsoid surface. The difference with the previous behavior is small but may be of a few millimeters for each meter from the reference point. [(commit)](http://code.google.com/p/mrpt/source/detail?r=3473)
		- Potential crash when setting mpPolygon::setPoints() with empty vectors - [(commit)](http://code.google.com/p/mrpt/source/detail?r=3478)
		- mrpt::reactivenav::CReactiveNavigationSystem and mrpt::reactivenav::CReactiveNavigationSystem3D didn't obey the "enableConsoleOutput" constructor flag - [(commit)](https://github.com/MRPT/mrpt/commit/db7b0e76506af2c24f119a28443a1e8f1a217861)
		- mrpt::synch::CSemaphore::waitForSignal() : Fixed error when thread got an external signal [(commit)](https://github.com/MRPT/mrpt/commit/511e95f03480537ff18ad2cad178c504b1cfbb53)

 <hr>
 <a name="1.0.2">
  <h2>Version 1.0.2: Released 2-AUG-2013 (SVN 3435)  </h2></a>
	- New apps:
		- [ReactiveNav3D-Demo](http://www.mrpt.org/Application%3AReactiveNav3D-Demo) (By Mariano Jaimez Tarifa)
	- Changes in apps:
		- [rawlog-edit](http://www.mrpt.org/Application%3Arawlog-edit):
			- New operations: --list-timestamps, --remap-timestamps, --export-2d-scans-txt, --export-imu-txt
	- New classes:
		- [mrpt-base]
			- mrpt::poses::CPose3DRotVec is now fully implemented (By Francisco Angel Moreno).
		- [mrpt-opengl]
			- mrpt::opengl::CLight - OpenGL scenes now allow customization of OpenGL lighting. See also new lighting methods in mrpt::opengl::COpenGLViewport - <a href="http://code.google.com/p/mrpt/source/detail?r=3409" >r3409</a>
		- [mrpt-reactivenav]
			- mrpt::reactivenav::CReactiveNavigationSystem3D - By Mariano Jaimez Tarifa - <a href="http://code.google.com/p/mrpt/source/detail?r=3389" >r3389</a>
	- New functions:
		- [mrpt-opengl]
			- mrpt::opengl::stock_objects::RobotRhodon()
	- Changes in classes:
		- [mrpt-base]
			- Generic particle filter classes now allow directly resampling to a dynamic number of particles. Affected methods: - <a href="http://code.google.com/p/mrpt/source/detail?r=3381" >r3381</a>
				- mrpt::bayes::CParticleFilterCapable::performResampling()
				- mrpt::bayes::CParticleFilterCapable::computeResampling()
			- New method: CImage::loadFromXPM() - <a href="http://code.google.com/p/mrpt/source/detail?r=3397" >r3397</a>
		- [mrpt-maps]
			- mrpt::maps::COctoMap now exposes the inner octomap::OcTree object. See example samples/octomap_simple - <a href="http://code.google.com/p/mrpt/source/detail?r=4304" >r4304</a>
		- [mrpt-openg]
			- mrpt::opengl::CBox now be also rendered as a solid box + line borders. See mrpt::opengl::CBox::enableBoxBorder()
			- mrpt::opengl::COctoMapVoxels - <a href="http://code.google.com/p/mrpt/source/detail?r=4329" >r4329</a>
				- Fixed calculation of normals (fix shading)
				- Added new coloring scheme to mrpt::opengl::COctoMapVoxels::visualization_mode_t : "FIXED"
				- By default, light effects are disabled in this object, because shadows aren't computed anyway and the effect isn't pleasant.
				- Voxels cubes are sorted in ascending Z order so the visual effect is correct when rendering with transparency.
		- [mrpt-reactivenav]
			- mrpt::reactivenav::CParameterizedTrajectoryGenerator: The "low pass filter" has been removed since it wasn't practical and was never used; thus, parameters "TAU" and "DELAY" has been removed. - <a href="http://code.google.com/p/mrpt/source/detail?r=3395" >r3395</a>
			- Methods removed since they weren't implemented in any derived class and there are no plans for doing it.
				- mrpt::reactivenav::CReactiveNavigationSystem ::evaluate()
				- mrpt::reactivenav::CReactiveNavigationSystem ::setParams()
	- Build system:
		- Updated to nanoflann 1.1.7: ICP is ~5% faster.
		- More unit tests:
			- [mrpt-base] geometry module.
	- BUG FIXES:
		- CTimeLogger::registerUserMeasure() ignored the enable/disable state of the logger - <a href="http://code.google.com/p/mrpt/source/detail?r=3382" >r3382</a>
		- mrpt-srba: SEGFAULT in 32bit builds due to missing MRPT_MAKE_ALIGNED_OPERATOR_NEW - <a href="http://code.google.com/p/mrpt/source/detail?r=3429" >r3429</a>

 <br/>
 <hr>
 <a name="1.0.1">
  <h2>Version 1.0.1: Released 12-MAY-2013 (SVN 3370)  </h2></a>
	- Changes in apps:
		- <a href="http://www.mrpt.org/Application%3ARawLogViewer" >RawLogViewer</a>:
			- Better description of the "too much memory used" warning while loading large datasets.
		- <a href="http://www.mrpt.org/Application%3Arobotic-arm-kinematics" >robotic-arm-kinematics</a>:
			- Now allows changing the orientation of the first DOF (X,Y,Z).
	- New classes:
		- [mrpt-hwdrivers]
			- mrpt::hwdrivers::CInterfaceNI845x: An interface for this USB SPI/I2C data acquisition board.
			- mrpt::hwdrivers::CCANBusReader: A class to record CAN bus frames with a CAN232 converter.
		- [mrpt-obs]
			- mrpt::obs::CObservationCANBusJ1939
	- New functions:
		- New opengl_stock objects:
			- mrpt::opengl::stock_objects::Hokuyo_URG()
			- mrpt::opengl::stock_objects::Hokuyo_UTM()
			- mrpt::opengl::stock_objects::Househam_Sprayer()
		- mrpt::math::saveEigenSparseTripletsToFile() - <a href="http://code.google.com/p/mrpt/source/detail?r=3351" >r3351</a>
	- New examples:
			- gmrf_map_demo
	- Changes in classes:
		- [mrpt-maps]
			- mrpt::maps::COccupancyGridMap2D now also evalutes likelihoods for sonar-like observations (mrpt::obs::CObservationRange), allowing particle-filter localization with these sensors - <a href="http://code.google.com/p/mrpt/source/detail?r=3330" >r3330</a>
			- New method mrpt::slam::CRandomFieldGridMap2D::insertIndividualReading()
		- [mrpt-kinematics]
			- mrpt::kinematics::CKinematicChain: Now allows changing the orientation of the first DOF (X,Y,Z).
	- Removed stuff:
		- Backwards-compatibility typedef mrpt::vision::TKLTFeatureStatus has been removed. Replace with mrpt::vision::TFeatureTrackStatus
		- KLT-specific values for mrpt::vision::TFeatureTrackStatus has been removed, since they were not used in detected features anyway.
	- Build system:
		- Fixed a potential build error if including FFMPEG's <time.h> instead of the standard header - <a href="http://code.google.com/p/mrpt/source/detail?r=3316" >r3316</a>
		- Fixed determination of GCC version for all GCC builds - <a href="http://code.google.com/p/mrpt/source/detail?r=3324" >r3324</a>
		- Updated to Eigen 3.1.3 - <a href="http://code.google.com/p/mrpt/source/detail?r=3349" >r3349</a>
		- Updated to nanoflann 1.1.5
	- BUG FIXES:
		- Unit tests "SchurTests" for mrpt-srba incorrectly reported errors due to an improperly initialized reference to a local variable - <a href="http://code.google.com/p/mrpt/source/detail?r=3318" >r3318</a>
		- Debian packages: added missing binary deps for libmrpt-dev  - <a href="http://code.google.com/p/mrpt/source/detail?r=3335" >r3335</a>

 <hr>
 <a name="1.0.0">
  <h2>Version 1.0.0: Released 1-MAR-2013 (SVN 3287)  </h2></a>
	- <b>Most important changes:</b>
		- New library with a flexible implementation of Sparser Relative Bundle Adjustment (RBA), as presented in ICRA 2013: <a href="http://www.mrpt.org/srba" >mrpt-srba</a>.
		- New library for Plane-based Maps: <a href="group__mrpt__pbmap__grp.html" >mrpt-pbmap</a> (also presented in ICRA 2013).
		- Some MRPT modules are now header-only libraries.
		- Support for a new Octomap metric map, via the octomap library. See mrpt::maps::COctoMap and detailed changes below.
		- Support for importing/exporting point clouds in the standard LAS format (Look for liblas below).
		- Better support for custom builds of MRPT (selective building of individual apps and libs, etc.)
		- Ready for Visual Studio 2012 and GCC 4.7
		- From now on, MRPT is released under the "New BSD" license.
		- Many bug fixes.
	- <b>Detailed list of changes:</b>
		- New apps:
			- <a href="http://www.mrpt.org/Application:srba-slam" >srba-slam</a>: A command-line frontend for the Relative Bundle Adjustment engine in mrpt-srba.
			- <a href="http://www.mrpt.org/Application:holonomic-navigator-demo" >holonomic-navigator-demo</a>
			- <a href="http://www.mrpt.org/Application:robotic-arm-kinematics" >robotic-arm-kinematics</a>: A GUI for experimenting with Denavit-Hartenberg parameters.
		- Changes in apps:
			- <a href="http://www.mrpt.org/Application%3Anavlog-viewer" >navlog-viewer</a>:
				- Fixed some minor visualization errors.
			- <a href="http://www.mrpt.org/Application%3ARawLogViewer" >RawLogViewer</a>:
				- Import sequence of images as rawlog: Didn't detect "png" file extension as images - <a href="http://code.google.com/p/mrpt/source/detail?r=2940" >r2940</a> - Closes <a href="http://code.google.com/p/mrpt/issues/detail?id=34" >#34</a>
				- The GUI toolbar has been ported from wxWidget's ToolBar to sets of wxCustomButton's to avoid visualization problems in wx 2.9.X - <a href="http://code.google.com/p/mrpt/source/detail?r=2950" >r2950</a>
			- <a href="http://www.mrpt.org/Application:ReactiveNavigationDemo" >ReactiveNavigationDemo</a>:
				- The default holonomic navigation method is now the VFF, since after the last bug fixes and tunes it seems to work quite well.
			- <a href="http://www.mrpt.org/Application%3ASceneViewer" >SceneViewer3D</a>:
				- The GUI toolbar has been ported from wxWidget's ToolBar to sets of wxCustomButton's to avoid visualization problems in wx 2.9.X - <a href="http://code.google.com/p/mrpt/source/detail?r=2952" >r2952</a>
				- Added a new menu: "File -> Import -> From LAS file..." - <a href="http://code.google.com/p/mrpt/source/detail?r=3244" >r3244</a>
			- <a href="http://www.mrpt.org/Application%3Agrid-matching" >grid-matching</a>: new argument "--aligner" to select aligner method - <a href="http://code.google.com/p/mrpt/source/detail?r=3021" >r3021</a>
		- New classes:
			- [mrpt-base]
				- mrpt::math::MatrixBlockSparseCols, a templated column-indexed efficient storage of block-sparse Jacobian or Hessian matrices, together with other arbitrary information - <a href="http://code.google.com/p/mrpt/source/detail?r=2995" >r2995</a>
				- mrpt::utils::ignored_copy_ptr<>
				- mrpt::utils::CTimeLoggerEntry
			- [mrpt-obs]
				- mrpt::obs::CObservationWindSensor - <a href="http://code.google.com/p/mrpt/source/detail?r=3050" >r3050</a>
			- [mrpt-maps]
				- mrpt::maps::COctoMap
			- [mrpt-opengl]
				- mrpt::opengl::COctoMapVoxels
		- Deleted classes:
			- [mrpt-vision]
				- CFeatureTracker_FAST and CFeatureTracker_PatchMatch have been removed since they didn't work robustly. Replace with mrpt::vision::CFeatureTracker_KL
		- New libraries:
			- [mrpt-kinematics] See mrpt::kinematics
			- [mrpt-pbmap] See <a href="group__mrpt__pbmap__grp.html" >mrpt-pbmap</a>.
			- [mrpt-srba] See <a href="http://www.mrpt.org/srba" >mrpt-srba</a>.
		- Changes in libraries:
			- These libs are now header-only: <a href="http://code.google.com/p/mrpt/source/detail?r=3035" >r3035</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3045" >r3045</a>
				- [mrpt-bayes]
				- [mrpt-graphs]
				- [mrpt-graphslam]
			- Integration of the Octomap C++ library (new BSD License) by Kai M. Wurm et al.: <a href="http://code.google.com/p/mrpt/source/detail?r=3081" >r3081</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3083" >r3083</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3084" >r3084</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3086" >r3086</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3087" >r3087</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3088" >r3088</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3093" >r3093</a>
				- The main new classes are mrpt::maps::COctoMap & mrpt::opengl::COctoMapVoxels
				- mrpt::maps::CMultiMetricMap now allows the seamless integration of octomaps in many MRPT map building or localization algorithms.
				- New example: samples/octomap_simple
		- Changes in classes:
			- [mrpt-base]
				- Eigen::MatrixBase<Derived>::loadFromTextFile(), and all MRPT derived matrix classes, are now much faster loading huge matrices from text files - <a href="http://code.google.com/p/mrpt/source/detail?r=2997" >r2997</a>
				- The typedef Eigen::MatrixBase<Derived>::typename of MRPT's plugin to Eigen classes has been REMOVED, to avoid conflicts with some part of Eigen's sparse classes. Use Matrix::Scalar instead - <a href="http://code.google.com/p/mrpt/source/detail?r=3065" >r3065</a>
				- New method mrpt::poses::CPose3DQuat::inverse()
				- New methods mrpt::poses::SE_traits::pseudo_exp()
				- mrpt::utils::CTimeLogger:
					- New method mrpt::utils::CTimeLogger::getStats() for programatic execution time stats analysis - <a href="http://code.google.com/p/mrpt/source/detail?r=2998" >r2998</a>
					- New method mrpt::utils::CTimeLogger::registerUserMeasure() for making stats of user-providen values - <a href="http://code.google.com/p/mrpt/source/detail?r=3005" >r3005</a>
				- mrpt::utils::map_as_vector<> can be now customized to use different underlying STL containers for storage - <a href="http://code.google.com/p/mrpt/source/detail?r=3001" >r3001</a>
				- mrpt::utils::CDynamicGrid::setSize() now also accepts a "fill_value" argument.
				- Added method mrpt::math::TPoint2D::norm() for consistency with mrpt::math::TPoint3D
				- Better support for saving (and not only loading) plain text configuration files, including commented files with default values of all existing parameters: - <a href="http://code.google.com/p/mrpt/source/detail?r=2954" >r2954</a>
					- All mrpt::utils::CConfigFileBase::write() now have an extended signature for formatting.
					- mrpt::utils::CLoadableOptions::dumpToTextStream() is no longer pure virtual: it now relies on mrpt::utils::CLoadableOptions::saveToConfigFile()
				- mrpt::utils::CStream::Seek() now supports files larger than 2GB by using uint64_t instead of long (still see issue report for another patch required for MSVC2010) - (Closes <a href="http://code.google.com/p/mrpt/issues/detail?id=39" >issue 39</a>, thanks Robert Schattschneider) - <a href="http://code.google.com/p/mrpt/source/detail?r=3042" >r3042</a>
				- mrpt::utils::TTypeName<> moved to its own header <mrpt/utils/TTypeName.h> while refactoring <mrpt/utils/CSerializable.h> - <a href="http://code.google.com/p/mrpt/source/detail?r=3044" >r3044</a>
				- mrpt::utils::CConfigFileBase::write() now has signatures for "uint32_t" and "uint64_t" in both 32 and 64bit builds, instead of relying of the "size_t" type. This was done to fix build errors in some GCC versions under 32bits.
				- mrpt::poses::CPose2D now caches the cos() and sin() of phi, with a huge performance improvement in most common operations.
			- [mrpt-bayes]
				- mrpt::bayes::CKalmanFilterCapable (and all EKF-SLAM methods based on it) are now much faster. The implementation now exploits the sparsity of the Jacobian (~25% faster in a test 6D EKF-SLAM dataset) - <a href="http://code.google.com/p/mrpt/source/detail?r=3059" >r3059</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3060" >r3060</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3061" >r3061</a>
				- mrpt::bayes::CParticleFilterCapable now makes use of the Curiously Recurring Template Pattern (CRTP) design instead of ugly #define macros - <a href="http://code.google.com/p/mrpt/source/detail?r=3182" >r3182</a>
			- [mrpt-graphs]
				- mrpt::graphs::CNetworkOfPoses2D, mrpt::graphs::CNetworkOfPoses3D,... and so on, are now all typedef's instead of classes, since serialization is now implemented as pure templatized code, thus avoiding the need to declare derived auxiliary classes  - <a href="http://code.google.com/p/mrpt/source/detail?r=3044" >r3044</a>
			- [mrpt-gui]
				- mrpt::gui::CDisplayWindow3D::addTextMessage() (and other opengl text routines) now allows drawing text with a shadow effect - <a href="http://code.google.com/p/mrpt/source/detail?r=3007" >r3007</a>
			- [mrpt-hwdrivers]
				- New method mrpt::hwdrivers::CActivMediaRobotBase::areMotorsEnabled()
				- mrpt::hwdrivers::CGenericSensor (and all derived classes) now allocate objects aligned in memory with MRPT_MAKE_ALIGNED_OPERATOR_NEW
				- New static method mrpt::hwdrivers::CGPSInterface::parse_NMEA()
			- [mrpt-maps]
				- Better integration of point cloud classes with PCL: - <a href="http://code.google.com/p/mrpt/source/detail?r=2943" >r2943</a>
					- mrpt::maps::CPointsMap::loadPCDFile()
					- mrpt::maps::CPointsMap::setFromPCLPointCloud()
					- mrpt::maps::CColouredPointsMap::setFromPCLPointCloudRGB()
				- Point cloud loading & saving in the standard ASPRS LiDAR LAS format (if liblas is installed in the system, see http://www.liblas.org/ ). See also the ready-to-use import menu in SceneViewer3D - <a href="http://code.google.com/p/mrpt/source/detail?r=3244" >r3244</a>
					- mrpt::maps::CPointsMap::loadLASFile()
					- mrpt::maps::CPointsMap::saveLASFile()
				- Integration of wind measurements in gas-concentration maps (by Javier G. Monroy) - <a href="http://code.google.com/p/mrpt/source/detail?r=3050" >r3050</a>
			- [mrpt-obs]
				- New method mrpt::obs::CObservationGPS::clear()
			- [mrpt-opengl]
				- Evaluation of bounding box of opengl objects. New methods: - <a href="http://code.google.com/p/mrpt/source/detail?r=3026" >r3026</a>
					- mrpt::opengl::CRenderizable::getBoundingBox()
					- mrpt::opengl::COpenGLScene::getBoundingBox()
					- mrpt::opengl::COpenGLViewport::getBoundingBox()
				- mrpt::opengl::COctreePointRenderer::octree_get_graphics_boundingboxes() has a new flag to draw solid boxes at each leaf node - <a href="http://code.google.com/p/mrpt/source/detail?r=3033" >r3033</a>
				- mrpt::opengl::COpenGLViewport has a new set of "global OpenGL switches" that affect the rendering of entire scenes - <a href="http://code.google.com/p/mrpt/source/detail?r=3185" >r3185</a>
				- Classes drawing lines now by default enable anti-aliasing (can be disabled by the programmer): - <a href="http://code.google.com/p/mrpt/source/detail?r=3185" >r3185</a>
					- mrpt::opengl::CGridPlaneXY, mrpt::opengl::CGridPlaneXZ
					- mrpt::opengl::CSimpleLine
					- mrpt::opengl::CSetOfLines
			- [mrpt-reactivenav]
				- Much code of mrpt::reactivenav classes have undergone a clean-up, slight optimizations and a translation of old Spanish names/comments to English - <a href="http://code.google.com/p/mrpt/source/detail?r=2939" >r2939</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=2942" >r2942</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=2958" >r2958</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3091" >r3091</a>
				- mrpt::reactivenav::CParameterizedTrajectoryGenerator::CColisionGrid now has a more maintainable binary serialization format - <a href="http://code.google.com/p/mrpt/source/detail?r=2939" >r2939</a>
				- mrpt::reactivenav::CParameterizedTrajectoryGenerator::debugDumpInFiles() now also saves text files which can be used to visualize PTGs from MATLAB (see scripts/viewPTG.m) - <a href="http://code.google.com/p/mrpt/source/detail?r=3009" >r3009</a>
				- mrpt::reactivenav::CHolonomicVFF and mrpt::reactivenav::CHolonomicND now have more configurable parameters, loadable from config files. See their documentation.
				- Repulsive forces from obstacles in mrpt::reactivenav::CHolonomicVFF are now automatically normalized wrt the density of the 360deg view of obstacles and forces follow a "1/range" law instead of the old "exp(-range)".
				- Solved a stability issue in C-S paths, in mrpt::reactivenav::CPTG5 (By Mariano Jaimez Tarifa) - <a href="http://code.google.com/p/mrpt/source/detail?r=3085" >r3085</a>
			- [mrpt-scanmatching]
				- mrpt::scanmatching::robustRigidTransformation():
					- Changed behavior not to allow features to appear in duplicated pairings.
					- Added a consistency test to avoid seeding RANSAC with an inconsistent initial model.
			- [mrpt-slam]
				- mrpt::slam::CMetricMapBuilderICP now does not integrate the small pose changes due to odometry and/or relocalization when considering the distance and angle thresholds. This means that fewer map updates are now done for the same ICP-SLAM parameters, which should lead to "less noisy" maps.
		- New functions:
			- [mrpt-base]
				- mrpt::utils::abs_diff()
				- mrpt::system::getMRPTLicense()
				- mrpt::system::getFileModificationTime()
				- mrpt::math::noncentralChi2PDF_CDF() is now exposed (was private)
				- mrpt::utils::sprintf_container()
				- mrpt::poses::operator -(mrpt::poses::CPose3DQuat)
				- max3() and min3() moved from the global namespace to mrpt::utils::max3() and mrpt::utils::min3()
		- New examples:
			- octomap_simple
			- ransac-data-association
		- Build system:
			- Update to nanoflann 1.1.4 - <a href="http://code.google.com/p/mrpt/source/detail?r=2937" >r2937</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3017" >r3017</a>
			- Update to Eigen 3.1.2 - <a href="http://code.google.com/p/mrpt/source/detail?r=3064" >r3064</a>
			- MRPT's root "CMakeLists.txt" has undergone a big refactoring and cleanup - <a href="http://code.google.com/p/mrpt/source/detail?r=2961" >r2961</a>
			- Backward compatible "mrpt-core" has been removed as a fake lib for which to search with CMake from user programs - <a href="http://code.google.com/p/mrpt/source/detail?r=2961" >r2961</a>
			- More system libs are detected in Linux (libclang-dev, lib3ds-dev), discarding embedded versions then - <a href="http://code.google.com/p/mrpt/source/detail?r=2963" >r2963</a> - <a href="http://code.google.com/p/mrpt/issues/detail?id=17" >Closes #17</a>
			- Automatic detection of supported SIMD extensions (SSE*) from CMake (only for Linux OS) - <a href="http://code.google.com/p/mrpt/source/detail?r=3013" >r3013</a>
			- Fixed building with Visual Studio 2012 (MSVC11) - <a href="http://code.google.com/p/mrpt/source/detail?r=3017" >r3017</a>
			- MRPT now allows defining header-only libraries with the define_mrpt_lib_header_only() macro - <a href="http://code.google.com/p/mrpt/source/detail?r=3034" >r3034</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=3035" >r3035</a>
			- More unit tests:
				- for all probability distribution functions in mrpt::math,
				- for the parser in mrpt::hwdrivers::CGPSInterface::parse_NMEA()
				- for the octomap map
				- for serialization/deserealization of many classes.
			- Added new documentation page: <a href="env-vars.html" >environment variables</a>.
			- Removed the build flag "MRPT_BACKCOMPATIB_08X".
			- Fixes for building under Mac OSX: <a href="http://code.google.com/p/mrpt/source/detail?r=3181" >r3181</a>
			- Enable some c++11 features if the compiler supports them - <a href="http://code.google.com/p/mrpt/source/detail?r=3273" >r3273</a>
		- BUG FIXES:
			- Build: Fixed detection of OpenCV 2.4.2+ installed in the system via CMake config file instead of pkg-config, which seems to be broken. - <a href="http://code.google.com/p/mrpt/source/detail?r=3019" >r3019</a>
			- [mrpt-base] The iterator returned by end() in all MRPT vectors and matrices (based on Eigen) pointed to the last element, not to the (now correct) next position after the last element - <a href="http://code.google.com/p/mrpt/source/detail?r=2941" >r2941</a>
			- [mrpt-base] mrpt::dynamicsize_vector::resize() performed a memory reallocation even if given the current size, due to an inherited behavior from Eigen. It is not the expected behavior, so it has been fixed. - <a href="http://code.google.com/p/mrpt/source/detail?r=3003" >r3003</a>
			- [mrpt-base] Wrong computation of normPDF() values for the multidimensional cases. Closes <a href="http://code.google.com/p/mrpt/issues/detail?id=46" >#46</a> - <a href="http://code.google.com/p/mrpt/source/detail?r=3068" >r3068</a>
			- [mrpt-base] mrpt::poses::CPoint::asString() confused the 2D and 3D cases (Thanks Cipri!)
			- [mrpt-base] Fixed errors in de-serialization of mrpt::utils::CPointPDFSOG and mrpt::maps::CReflectivityGridMap2D
			- [mrpt-base] mrpt::math::KDTreeCapable::kdTreeRadiusSearch2D() always returned 0 matched.
			- [mrpt-graphs] Fixed bug in RecursiveSpectralPartition (Thanks to Edu!) - <a href="http://code.google.com/p/mrpt/source/detail?r=3026" >r3026</a>
			- [mrpt-hwdrivers] Fixed potential SEGFAULT in mrpt::hwdrivers::CGPSInterface (Thanks K.Miyawaki for <a href="http://www.mrpt.org/node/2474" >reporting</a>)
			- [mrpt-hwdrivers] Fixed communications to LMS 1xx scanners (Thanks Henry! See http://code.google.com/p/mrpt/issues/detail?id=49 )
			- [mrpt-maps] mrpt::maps::COccupancyGridMap2D::getAs3DObject() returned cells with an occupancy of exactly "0" as transparent - <a href="http://code.google.com/p/mrpt/source/detail?r=2957" >r2957</a>
			- [mrpt-maps] Fixed saving the correct point colors in mrpt::maps::CColouredPointsMap::savePCDFile() (Thanks Mariano!) - <a href="http://code.google.com/p/mrpt/source/detail?r=3090" >r3090</a>
			- [mrpt-maps] In CPointsMap::computeMatchingWith3D. Fixed matching two 3D point clouds as each correspondence was inserted twice into the output vector. (By Paco) - <a href="http://code.google.com/p/mrpt/source/detail?r=3162" >r3162</a>
			- [mrpt-opengl] Fixed a potential bug: after deserializing an object based on a display-list (most of them), it won't update in the opengl view.
			- [mrpt-reactivenav] Class mrpt::reactivenav::CHolonomicVFF was not exported in Windows DLL's (Thanks Mariano for noticing!).
			- [mrpt-reactivenav] Fixed wrong computation of obstacles force fields in mrpt::reactivenav::CHolonomicVFF (Thanks Mariano for noticing!) - <a href="http://code.google.com/p/mrpt/source/detail?r=2953" >r2953</a>
			- [mrpt-reactivenav] Precomputed collision grids could be loaded in mrpt::reactivenav::CParameterizedTrajectoryGenerator even for different robot parameters/shape: now it correctly detects such situations and recompute when needed - <a href="http://code.google.com/p/mrpt/source/detail?r=2939" >r2939</a>  - Closes <a href="http://code.google.com/p/mrpt/issues/detail?id=33" >#33</a>
			- [mrpt-reactivenav] ND algorithm: Fixed bugs of "last gap is never evaluated" and wrong composition of representative direction for some gaps (By Mariano) - <a href="http://code.google.com/p/mrpt/source/detail?r=3056" >r3056</a>


 <br>
 <hr>
 <a name="0.9.6">
  <h2>Version 0.9.6 - (Version 1.0.0-Release_Candidate_4): Released 30-MAY-2012 (SVN 2930) </h2></a>
	- New applications:
		- <a href="http://www.mrpt.org/Application:kinect-stereo-calibrate" >kinect-stereo-calibrate</a>: A GUI tool for calibrating RGB+D and/or stereo cameras, including live Kinect capturing.
	- Removed applications:
		- stereo-calib-gui: it's now superseded by kinect-stereo-gui. The old command line tool is still useful, so it's still there as the example "stereo-calib-opencv".
	- Changes in applications:
		- <a href="http://www.mrpt.org/Application:icp-slam" >icp-slam</a>:
			- Added a new option (SHOW_LASER_SCANS_3D in config files) to draw laser scans in the live 3D view - <a href="http://code.google.com/p/mrpt/source/detail?r=2881" >r2881</a>
		- <a href="http://www.mrpt.org/Application:rawlog-edit" >rawlog-edit</a>:
			- Operation "--camera-params" now also handles stereo observations.
			- New operation "--stereo-rectify" for batch rectifying datasets with stereo images.
			- New operation "--rename-externals".
		- <a href="http://www.mrpt.org/Application:SceneViewer" >SceneViewer3D</a>:
			- New menu for generating high-resolution renders of any scene directly to imag files - <a href="http://code.google.com/p/mrpt/source/detail?r=2775" >r2775</a>
			- Many new menus for selective selecting objects and applying operations on them - <a href="http://code.google.com/p/mrpt/source/detail?r=2776" >r2776</a>
		- stereo-calib-gui: Now generates a report with detailed and clear results from stereo calibration and allows the user to change most parameters interactively - <a href="http://code.google.com/p/mrpt/source/detail?r=2801" >r2801</a>
		- <a href="http://www.mrpt.org/Application:kinect-3d-view" >kinect-3d-view</a>: New key command: press '9' to grab selected snapshots to disk  - <a href="http://code.google.com/p/mrpt/source/detail?r=2890" >r2890</a>
	- Kinect stuff:
		- [mrpt-hwdrivers]
			- mrpt::hwdrivers::CKinect now decodes Bayer color using OpenCV instead of default freenect - <a href="http://code.google.com/p/mrpt/source/detail?r=2721" >r2721</a>, <a href="http://code.google.com/p/mrpt/source/detail?r=2762" >r2762</a>
			- mrpt::hwdrivers::CKinect no longer forces a horizontal tilt at start up by default, what may be annoying (if required, set "initial_tilt_angle") - <a href="http://code.google.com/p/mrpt/source/detail?r=2722" >r2722</a>
			- mrpt::hwdrivers::CKinect now loads Kinect calibration files in a format compatible with stereo cameras. See http://www.mrpt.org/Kinect_calibration
		- [mrpt-obs]
			- New method mrpt::obs::CObservation3DRangeScan::convertTo2DScan() allows simulating a "fake 2D laser scanner" from a Kinect. See the example: http://www.mrpt.org/Example_Kinect_To_2D_laser_scan
		- [mrpt-vision]
			- New function mrpt::vision::checkerBoardStereoCalibration() to calibrate stereo and RGB+D cameras. See also the program <a href="http://www.mrpt.org/Application:kinect-stereo-calibrate" >kinect-stereo-calibrate</a>:
	- New classes:
		- [mrpt-gui]
			- New event generated by GUI windows: mrpt::gui::mrptEventWindowClosed
		- [mrpt-hwdrivers]
			- mrpt::hwdrivers::CRaePID: A new interface to PID gas sensing devices (by Emil Khatib, University of Malaga) - <a href="http://code.google.com/p/mrpt/source/detail?r=2841" >r2841</a>
		- [mrpt-opengl]
			- New classes for representing confidence intervals (ellipsoids) in transformed spaces - <a href="http://code.google.com/p/mrpt/source/detail?r=2783" >r2783</a>
				- mrpt::opengl::CGeneralizedEllipsoidTemplate<>
				- mrpt::opengl::CEllipsoidRangeBearing2D
				- mrpt::opengl::CEllipsoidInverseDepth2D
				- mrpt::opengl::CEllipsoidInverseDepth3D
			- mrpt::opengl::CFrustum to easily render these geometric figures
			- New struct mrpt::opengl::TFontParams result of a code refactoring
		- [mrpt-vision]
			- mrpt::vision::TSIFTDescriptorsKDTreeIndex, TSURFDescriptorsKDTreeIndex  - <a href="http://code.google.com/p/mrpt/source/detail?r=2799" >2799</a>
			- mrpt::vision::CStereoRectifyMap - See tutorial online: http://www.mrpt.org/Rectifying_stereo_

*/
