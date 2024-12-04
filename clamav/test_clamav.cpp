#include <iostream>
#include <cstdlib>
#include <clamav.h>
#include <string>

class ClamAVTester {
private:
    cl_engine* engine;
    unsigned int sigs;
    struct cl_scan_options options;
    
public:
    ClamAVTester() : engine(nullptr), sigs(0) {
        // Initialize scan options
        memset(&options, 0, sizeof(struct cl_scan_options));
        options.parse = ~0;                        // Enable all parse options
        options.general = CL_SCAN_GENERAL_ALLMATCHES;
    }
    
    bool initialize() {
        cl_error_t ret;
        
        // Initialize ClamAV library
        ret = cl_init(CL_INIT_DEFAULT);
        if (ret != CL_SUCCESS) {
            std::cerr << "Failed to initialize libclamav: " << cl_strerror(ret) << std::endl;
            return false;
        }
        
        // Create new engine
        engine = cl_engine_new();
        if (engine == nullptr) {
            std::cerr << "Failed to create new engine" << std::endl;
            return false;
        }
        
        // Load virus database
        ret = cl_load(cl_retdbdir(), engine, &sigs, CL_DB_STDOPT);
        if (ret != CL_SUCCESS) {
            std::cerr << "Failed to load virus database: " << cl_strerror(ret) << std::endl;
            cl_engine_free(engine);
            return false;
        }
        
        // Compile engine
        ret = cl_engine_compile(engine);
        if (ret != CL_SUCCESS) {
            std::cerr << "Engine compilation failed: " << cl_strerror(ret) << std::endl;
            cl_engine_free(engine);
            return false;
        }
        
        return true;
    }
    
    bool scanFile(const std::string& filepath) {
        const char* virname = nullptr;
        unsigned long int scanned = 0;
        cl_error_t ret;
        
        ret = cl_scanfile(filepath.c_str(), &virname, &scanned, engine, &options);
        
        switch (ret) {
            case CL_CLEAN:
                std::cout << "File clean" << std::endl;
                return true;
                
            case CL_VIRUS:
                std::cout << "Virus detected: " << virname << std::endl;
                return false;
                
            default:
                std::cout << "Error scanning file: " << cl_strerror(ret) << std::endl;
                return false;
        }
    }
    
    ~ClamAVTester() {
        if (engine != nullptr) {
            cl_engine_free(engine);
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_to_scan>" << std::endl;
        return 1;
    }
    
    ClamAVTester tester;
    
    if (!tester.initialize()) {
        std::cerr << "Failed to initialize ClamAV" << std::endl;
        return 1;
    }
    
    std::cout << "ClamAV initialized successfully" << std::endl;
    std::cout << "Scanning file: " << argv[1] << std::endl;
    
    bool result = tester.scanFile(argv[1]);
    
    return result ? 0 : 1;
}
