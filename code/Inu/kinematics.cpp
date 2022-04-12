#include "kinematics.h"

#include <Arduino.h>

int* Kinematics::singleLegIK(int legAngles[], float legPosition[], float legRotation[], float xOff, float yOff, bool onLeft = false) {
    float abductionLegOffset = 53;

    float x = legPosition[0];
    float y = legPosition[1];
    float z = legPosition[2];

    // float roll = legRotation[0];
    // float pitch = legRotation[1];
    // float yaw = legRotation[2];

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
    if (!onLeft) {
        abductionLegOffset *= -1;
    }

    float lengthY = y + abductionLegOffset;
    float abductionAngleYRad = atan(lengthY / z);
    float abductionHyp = lengthY / sin(abductionAngleYRad);

    float abdLowerAngleRad = asin(abductionLegOffset / abductionHyp);
    float abdAngleTotalRad = (PI - (PI / 2) - abdLowerAngleRad) + abductionAngleYRad;
    int abdAngleDeg = abdAngleTotalRad * (180 / PI);

    float z2 = abductionLegOffset / tan(abdLowerAngleRad);

    // X Axis Translation
    float shoulderAngleXRad = atan(x / z2);
    int shoulderAngleXDeg = ((int)(shoulderAngleXRad * (180 / PI)));

    float z3 = z2 / cos(shoulderAngleXRad);

    // Z Axis Translation
    float shoulderAngleZRad = acos((sq(UPPER_LEG_LENGTH) + sq(z3) - sq(LOWER_LEG_LENGTH)) / (2 * UPPER_LEG_LENGTH * z3));
    float elbow_angle_z_rad = PI - (shoulderAngleZRad * 2);

    int shoulderAngleZDeg = ((int)(shoulderAngleZRad * (180 / PI)) + SHOULDER_ANGLE_OFFSET);
    int elbowAngleZDeg = (int)(elbow_angle_z_rad * (180 / PI));

    if (onLeft) {
        legAngles[0] = 180 - abdAngleDeg;
        legAngles[1] = 180 - shoulderAngleZDeg - shoulderAngleXDeg;
        legAngles[2] = 180 - elbowAngleZDeg;
    } else {
        legAngles[0] = 180 - abdAngleDeg;  // Dont need to inverse because it needs to match other
        legAngles[1] = shoulderAngleZDeg + shoulderAngleXDeg;
        legAngles[2] = elbowAngleZDeg;  // Inverse
    }

    return legAngles;
}