#include "kinematics.h"

#include <math.h>

int* Kinematics::single_leg_ik(int leg_angles[], float leg_position[], float leg_rotation[], float x_off, float y_off, bool on_left = false) {
    float abduction_leg_offset = 53;

    float x = leg_position[0];
    float y = leg_position[1];
    float z = leg_position[2];

    float roll = leg_rotation[0];
    // float pitch = leg_rotation[1];
    // float yaw = leg_rotation[2];

    // Roll
    // float roll_angle_rad = roll * (PI / 180);
    // float roll_z_offset = BODY_WIDTH * sin(roll_angle_rad);
    // float roll_z_total = z + roll_z_offset;

    // float roll_body_offset = BODY_WIDTH * cos(roll_angle_rad);

    // float roll_foot_displacement = (BODY_WIDTH - roll_body_offset) - y;
    // float roll_foot_angle = atan(roll_foot_displacement / roll_z_offset);

    // if (isnan(roll_foot_angle)) {
    //     roll_foot_angle = 0.0;
    // }

    // float roll_foot_y_displacement = tan(roll_foot_angle) - roll_z_total;
    // float y1 = roll_foot_y_displacement - y;

    // Serial.println(roll_foot_angle);

    // Y Axis Translation
    if (!on_left) {
        abduction_leg_offset *= -1;
    }

    float length_y = y + abduction_leg_offset;
    float abduction_angle_y_rad = atan(length_y / z);
    float abduction_hyp = length_y / sin(abduction_angle_y_rad);

    float abd_lower_angle_rad = asin(abduction_leg_offset / abduction_hyp);
    float abd_angle_total_rad = (PI - (PI / 2) - abd_lower_angle_rad) + abduction_angle_y_rad;
    int abd_angle_deg = abd_angle_total_rad * (180 / PI);

    float z2 = abduction_leg_offset / tan(abd_lower_angle_rad);

    // X Axis Translation
    float shoulder_angle_x_rad = atan(x / z2);
    int shoulder_angle_x_deg = ((int)(shoulder_angle_x_rad * (180 / PI)));

    float z3 = z2 / cos(shoulder_angle_x_rad);

    // Z Axis Translation
    float shoulder_angle_z_rad = acos((pow(UPPER_LEG_LENGTH, 2) + pow(z3, 2) - pow(LOWER_LEG_LENGTH, 2)) / (2 * UPPER_LEG_LENGTH * z3));
    float elbow_angle_z_rad = PI - (shoulder_angle_z_rad * 2);

    int shoulder_angle_z_deg = ((int)(shoulder_angle_z_rad * (180 / PI)) + SHOULDER_ANGLE_OFFSET);
    int elbow_angle_z_deg = (int)(elbow_angle_z_rad * (180 / PI));

    if (on_left) {
        leg_angles[0] = 180 - abd_angle_deg;
        leg_angles[1] = 180 - shoulder_angle_z_deg - shoulder_angle_x_deg;
        leg_angles[2] = 180 - elbow_angle_z_deg;
    } else {
        leg_angles[0] = 180 - abd_angle_deg;  // Dont need to inverse because it needs to match other
        leg_angles[1] = shoulder_angle_z_deg + shoulder_angle_x_deg;
        leg_angles[2] = elbow_angle_z_deg;  // Inverse
    }

    return leg_angles;
}