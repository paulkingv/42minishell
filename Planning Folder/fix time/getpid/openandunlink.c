// This is an example by Gemini for using this method

#include <fcntl.h>
#include <unistd.h>

int main() {
    // 1. Create a hardcoded file name
    // Even if another instance hits this code at the same time,
    // O_EXCL forces one instance to fail and retry a split second later.
    int fd = -1;
    while (fd == -1) {
        fd = open("shared_temp_gate", O_RDWR | O_CREAT | O_EXCL, 0600);
    }

    // 2. Immediately unlink it!
    // The name "shared_temp_gate" disappears from the folder instantly.
    // The next instance can now safely use the exact same name!
    unlink("shared_temp_gate");

    // 3. Use your file completely in private
    // This fd is 100% dedicated to this instance. No conflicts possible.
    write(fd, "Secret instance data\n", 21);
    
    // 4. Close it when done
    // The OS completely deletes the data automatically here.
    close(fd); 
    return 0;
}