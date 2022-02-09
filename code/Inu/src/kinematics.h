#ifndef KINEMATICS_H
#define KINEMATICS_H

#define UPPER_LEG_LENGTH 100
#define LOWER_LEG_LENGTH 100

#define SHOULDER_ANGLE_OFFSET 45
#define ELBOW_ANGLE_MAX 170

#define ABDUCTION_LEG_OFFSET 53  // 55

class Kinematics {
   public:
    /**
     * @brief Calculate the inverse kinematics of single leg
     *
     * @param leg_angles Int array to change
     * @param leg_coordinates Coordinates of end effector in mm from leg origin (Shoulder zero position)
     * @param x_off X offset of leg origin relative to body origin
     * @param y_off Y offset of leg origin relative to body origin
     * @param on_left Is leg on left side of body. Used to inverse angles
     * @return Pointer of leg angles in degrees
     */
    int* single_leg_ik(int leg_angles[], float leg_coordinates[], float x_off, float y_off, bool on_left);
};

#endif