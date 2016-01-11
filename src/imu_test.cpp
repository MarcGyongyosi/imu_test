#include <RTIMULib.h>
#include <iostream>


int main(int argc, char **argv){
    std::cout << "IMU is opening" << std::endl; 
    RTIMUSettings *settings = new RTIMUSettings("~/imu_test/", "");
    RTIMU *imu = RTIMU::createIMU(settings);
	
    int sampleCount = 0;
    int sampleRate = 0;
    uint64_t rateTimer;
    uint64_t displayTimer;
    uint64_t now;

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)){
       std::cout << "Error, couldn't open IMU" << std::endl; 
       return -1;
    }
    // Initialise the imu object
    imu->IMUInit();

    // Set the Fusion coefficient
    imu->setSlerpPower(0.02);
    // Enable the sensors
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true); 
    while (1) {
        //  poll at the rate recommended by the IMU

        usleep(imu->IMUGetPollInterval() * 1000);

        while (imu->IMURead()) {
            RTIMU_DATA imuData = imu->getIMUData();
            sampleCount++;

            now = RTMath::currentUSecsSinceEpoch();

            //  display 10 times per second

            if ((now - displayTimer) > 100000) {
                printf("Sample rate %d: %s\r", sampleRate, RTMath::displayDegrees("", imuData.fusionPose));
                fflush(stdout);
                displayTimer = now;
            }

            //  update rate every second

            if ((now - rateTimer) > 1000000) {
                sampleRate = sampleCount;
                sampleCount = 0;
                rateTimer = now;
            }
        }
    }
}
