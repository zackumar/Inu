#include "kinematics.h"

#include <Arduino.h>

int* Kinematics::single_leg_ik(int leg_angles[], float leg_coordinates[]) {
    float x = leg_coordinates[0];
    float y = leg_coordinates[1];
    float z = leg_coordinates[2];

    // Y Axis Translation
    float length_y = y + ABDUCTION_LEG_OFFSET;
    float abduction_angle_y_rad = atan(length_y / z);
    float abduction_hyp = length_y / sin(abduction_angle_y_rad);

    float abd_lower_angle_rad = asin(ABDUCTION_LEG_OFFSET / abduction_hyp);
    float abd_angle_total_rad = (PI - (PI / 2) - abd_lower_angle_rad) + abduction_angle_y_rad;
    int abd_angle_deg = abd_angle_total_rad * (180 / PI);

    float z2 = ABDUCTION_LEG_OFFSET / tan(abd_lower_angle_rad);

    // X Axis Translation
    float shoulder_angle_x_rad = atan(x / z2);
    int shoulder_angle_x_deg = ((int)(shoulder_angle_x_rad * (180 / PI)));

    float z3 = z2 / cos(shoulder_angle_x_rad);

    // Z Axis Translation
    float shoulder_angle_z_rad = acos((sq(UPPER_LEG_LENGTH) + sq(z3) - sq(LOWER_LEG_LENGTH)) / (2 * UPPER_LEG_LENGTH * z3));
    float elbow_angle_z_rad = PI - (shoulder_angle_z_rad * 2);

    int shoulder_angle_z_deg = 180 - ((int)(shoulder_angle_z_rad * (180 / PI)) + SHOULDER_ANGLE_OFFSET);
    int elbow_angle_z_deg = (180 - (int)(elbow_angle_z_rad * (180 / PI)));

    leg_angles[0] = 180 - abd_angle_deg;
    leg_angles[1] = shoulder_angle_z_deg - shoulder_angle_x_deg;
    leg_angles[2] = elbow_angle_z_deg;
}