#include "signatureupdater.h"
#include <ctime>
#include <sstream>
#include <iomanip>

// Initialize virus signature updater
SignatureUpdater::SignatureUpdater() : isUpdateInProgress(false) {
   lastUpdateTime = "Never";
}

SignatureUpdater::~SignatureUpdater() {
   
}

// Update virus signatures from ClamAV servers
void SignatureUpdater::updateSignatures() {
   if (isUpdateInProgress) {
       std::cout << "Update already in progress!" << std::endl;
       return;
   }

   isUpdateInProgress = true;
   std::cout << "Starting signature update..." << std::endl;

   if (executeUpdate()) {
       saveUpdateTime();
       std::cout << "Signature update completed successfully." << std::endl;
   } else {
       std::cout << "Signature update failed!" << std::endl;
   }

   isUpdateInProgress = false;
}

// Run freshclam to download latest signatures
bool SignatureUpdater::executeUpdate() {
   int result = system("freshclam");
   return (result == 0);
}

// Save timestamp of successful update
void SignatureUpdater::saveUpdateTime() {
   lastUpdateTime = getCurrentTime();
}

// Get formatted current timestamp 
std::string SignatureUpdater::getCurrentTime() {
   auto now = std::chrono::system_clock::now();
   auto time = std::chrono::system_clock::to_time_t(now);
   std::stringstream ss;
   ss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
   return ss.str();
}

// Get last update timestamp
std::string SignatureUpdater::getLastUpdateTime() const {
   return lastUpdateTime;
}