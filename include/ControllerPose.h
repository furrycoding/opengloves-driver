#pragma once
#include <openvr_driver.h>
#include <memory>

#include "DeviceConfiguration.h"
#include "ControllerDiscovery.h"
#include "Calibration.h"
#include "Util/NamedPipe.h"

class ControllerPose {
 public:
  ControllerPose(vr::ETrackedControllerRole shadowDeviceOfRole, std::string thisDeviceManufacturer,
                 VRPoseConfiguration_t poseConfiguration);

  vr::DriverPose_t UpdatePose();

  void StartCalibration();

  void CompleteCalibration();

  void CancelCalibration();

  bool isCalibrating();

 private:
  uint32_t m_shadowControllerId = vr::k_unTrackedDeviceIndexInvalid;

  VRPoseConfiguration_t m_poseConfiguration;

  vr::ETrackedControllerRole m_shadowDeviceOfRole = vr::TrackedControllerRole_Invalid;

  std::string m_thisDeviceManufacturer;

  vr::TrackedDevicePose_t GetControllerPose();

  bool isRightHand();

  std::unique_ptr<ControllerDiscovery> m_controllerDiscoverer;
  std::unique_ptr<NamedPipeUtil> m_calibrationPipe;
  std::unique_ptr<Calibration> m_calibration;
};