#ifndef SIGNATURE_UPDATER_H
#define SIGNATURE_UPDATER_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

// Manages virus signature database updates from ClamAV servers
class SignatureUpdater {
private:
   bool isUpdateInProgress;
   std::string lastUpdateTime;

   // Core update logic and tracking
   bool executeUpdate();        // Runs freshclam to fetch latest sigs
   void saveUpdateTime();       // Records when update completed 
   std::string getCurrentTime();

public:
   SignatureUpdater();
   ~SignatureUpdater();
   void updateSignatures();     // Main update entry point
   std::string getLastUpdateTime() const;
};

#endif