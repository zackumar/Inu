#include "kinematics.h"

#include <Arduino.h>

int* Kinematics::single_leg_ik(int leg_angles[], float leg_coordinates[]) {
    float z = leg_coordinates[2];
    float x = leg_coordinates[0];

    float shoulder_angle_x_rad = atan(x / z);
    int shoulder_angle_x_deg = ((int)(shoulder_angle_x_rad * (180 / PI)));

    float newZ = z / cos(shoulder_angle_x_rad);

    float shoulder_angle_z_rad = acos((sq(UPPER_LEG_LENGTH) + sq(newZ) - sq(LOWER_LEG_LENGTH)) / (2 * UPPER_LEG_LENGTH * newZ));
    float elbow_angle_z_rad = PI - (shoulder_angle_z_rad * 2);

    int shoulder_angle_z_deg = 180 - ((int)(shoulder_angle_z_rad * (180 / PI)) + SHOULDER_ANGLE_OFFSET);
    int elbow_angle_z_deg = min((180 - (int)(elbow_angle_z_rad * (180 / PI))), 9999999);  // ELBOW_ANGLE_MAX);

    leg_angles[0] = 0;
    leg_angles[1] = shoulder_angle_z_deg - shoulder_angle_x_deg;
    leg_angles[2] = elbow_angle_z_deg;
}