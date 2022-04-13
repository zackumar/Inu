#ifndef KINEMATICS_H
#define KINEMATICS_H

#define UPPER_LEG_LENGTH 100
#define LOWER_LEG_LENGTH 100

#define SHOULDER_ANGLE_OFFSET 45
#define ELBOW_ANGLE_MAX 170

#define BODY_WIDTH 95  // mm from center (Half distance from origin to leg origin)

#define PI 3.1415926535897932384626433832795

class Kinematics {
   public:
    /**
     * @brief Calculate the inverse kinematics of single leg
     *
     * @param legAngles Int array to change
     * @param legPosition Coordinates of end effector in mm from leg origin (Shoulder zero position)
     * @param legRotation Roll, Pitch, Yaw axis from robot origin in degrees
     * @param xOff X offset of leg origin relative to body origin
     * @param yOff Y offset of leg origin relative to body origin
     * @param onLeft Is leg on left side of body. Used to inverse angles
     * @return Pointer of leg angles in degrees
     */
    int* singleLegIK(int legAngles[], float legPosition[], float legRotation[], float xOff, float yOff, bool onLeft);
};

#endif